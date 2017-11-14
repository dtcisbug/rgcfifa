#include "Common/Config.h"

#include "WorldServer.h"
#include "WorkerThread.h"
#include "Cfg.h"
#include "Common/TimeUtil.h"
#include "Common/StringTokenizer.h"
const char* s_HelpInfo = "";
//////////////////////////////////////////////////////////////////////////
WorldServer::WorldServer() : m_IsActive(false)
{
	memset(m_AllWorker, 0x00, sizeof(m_AllWorker));
	m_TcpService = NULL;
}

WorldServer::~WorldServer()
{
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		delete m_AllWorker[i];
	}
	//delete m_TcpService;
}

bool WorldServer::ParseCommandInfor(Int32 argc, char * argv[])
{
	int status = 0;
	for(int i = 1; i < argc; ++ i)
	{
		switch(status)
		{
		case 1:
			cfg.setFilename(argv[i]);
			break;
		default:
			if(strcmp(argv[i], "--config") == 0)
			{
				status = 1;
			}
			break;
		}
	}
	return true;
}

bool WorldServer::Init(const char * scriptStr, const char * serverName, int num)
{
	if(serverName != NULL)
	{
		const char * p = strstr(serverName, "_s");
		if(p != NULL)
		{
			cfg.channelName = std::string(serverName, p);
			cfg.serverNum = atoi(p + 2);
			cfg.slugName = cfg.channelName;
		}
	}
    Network::Initialize();
	//读取配置文件
	TimeUtil::Init();
	cfg.load(scriptStr);

    if (!num)
    {
        srand(static_cast<UInt32>(time(NULL)));
        cfg.serverNum = cfg.tcpPort+rand()%1000;
    }
    else
        cfg.serverNum = num;

    cfg.serverLogId = cfg.serverNum;
	
    return true;
}

void WorldServer::UnInit()
{
    Down();

	Network::Uninitialize();
}

void WorldServer::SetActive(bool active)
{
	m_IsActive = active;
}

bool WorldServer::IsActive() const
{
	return m_IsActive;
}

void WorldServer::Run()
{
	m_TcpService = new Network::TcpServerWrapper(cfg.tcpPort);
	m_TcpService->Start();

    //Up();

	m_TcpService->Join();

	delete m_TcpService;
}

void WorldServer::Shutdown()
{
    //Down();

	//关闭网络线程
	m_TcpService->UnInit();

    // XXX: erase all event
	Thread::sleep(2000);
}

#define MAX_RET_LEN 1024

static int recvret(char* data, size_t size, size_t nmemb, char* buf)
{
    size_t nsize = size * nmemb;
    if (nsize > MAX_RET_LEN) {
        //bcopy(data, buf, MAX_RET_LEN);
		memcpy(buf, data, MAX_RET_LEN);
        return MAX_RET_LEN;
    }

	memcpy(buf, data, nsize);
    //bcopy(data, buf, nsize);
    return static_cast<int>(nsize);
}

void WorldServer::State(const char* action, int serverNum)
{
    if (!action || !serverNum)
        return;
    char url[4096] = {0};
    snprintf(url, sizeof(url), "%s&state=%s&server=s%d", cfg.stateUrl.c_str(), action, serverNum);

    updateState(action);
}


void WorldServer::updateState(const char* action)
{
#ifdef _DEBUG
    if (true)
        return ;
    if (!action)
        return;
    char url[4096] = {0};

    char serverIp[20];
    in_addr iaddr;
    iaddr.s_addr = cfg.serverIp;
    strcpy(serverIp, inet_ntoa(iaddr));
    snprintf(url, sizeof(url), "http://192.168.88.250/serverstate.php?ip=%s&port=%d&state=%s", serverIp, cfg.tcpPort, action);
#endif
}

void WorldServer::Up()
{
    State("open", cfg.serverNum);
}

void WorldServer::Down()
{
    State("close", cfg.serverNum);
}

