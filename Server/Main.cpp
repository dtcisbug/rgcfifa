#include "Common/Config.h"
#include "WorldServer.h"
#include <iostream>
#include <signal.h>
#include <math.h>
#ifdef __GNUC__
#ifndef _WIN32
#include <sys/resource.h>
#include <fcntl.h>
extern "C" __attribute__((constructor)) void __serverInit()
{
	struct rlimit rlsrc = {RLIM_INFINITY, RLIM_INFINITY};
	struct rlimit rlsrc2 = {131072, 262144};
	setrlimit(RLIMIT_CORE, &rlsrc);
	setrlimit(RLIMIT_NOFILE, &rlsrc2);
	int f = open("/proc/sys/kernel/core_uses_pid", O_WRONLY);
	if(f < 0)
		return;
	write(f, "1", 1);
	close(f);
}
#endif
#endif

extern "C" void sigbreak(int sig)
{
	SERVER().Shutdown();
}

int main(int argc, char* argv[])
{
	if (!SERVER().ParseCommandInfor(argc, argv))
	{
		fprintf(stdout, "%s\n", s_HelpInfo);
		exit(-1);
	}
#ifndef SIGBREAK
#define SIGBREAK 21
#endif
	signal(SIGABRT, &sigbreak);
	signal(SIGINT, &sigbreak);
	signal(SIGTERM, &sigbreak);
	signal(SIGBREAK, &sigbreak);

	GLOBAL().Init();

	const char * scriptStr = NULL;
	const char * serverName = NULL;
	if(argc > 2)
	{
		scriptStr = argv[1];
		serverName = argv[2];
	}
	else if(argc > 1)
	{
		serverName = argv[1];
	}

    int num = 0;
    char* s = strstr(argv[0], ".");
    if (s)
    {
        s += 1;
        num = atoi(s);
    }

	if (!SERVER().Init(scriptStr, serverName, num))
	{
		fprintf(stdout, "Server Initialize fail !\n");
		exit(-1);
	}

	SERVER().Run();

	SERVER().UnInit();

	GLOBAL().UnInit(); //放在最后处理

	return 0;
}
