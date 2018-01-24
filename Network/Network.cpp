#include "Common/Config.h"
#include "Network.h"
//#include "Common/TInf.h"
#include <event2/thread.h>

namespace Network
{
	void Initialize()
	{
#ifdef _WIN32
		WSADATA wsadata;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		evthread_use_windows_threads();
#else
		//evthread_use_pthreads();
#endif
		//tinf_init();
	}
	void Uninitialize()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}
	UInt32 ResolveAddress( const char * domain )
	{
		struct hostent * remoteHost;
		if (isalpha(domain[0])) {
			remoteHost = gethostbyname(domain);
			if(remoteHost == NULL)
				return (UInt32)-1;
			return ntohl(*(UInt32 *)remoteHost->h_addr_list[0]);
		} else {
			return ntohl(inet_addr(domain));
		}
	}
}
