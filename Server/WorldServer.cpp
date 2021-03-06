﻿#include "Common/Config.h"

#include "WorldServer.h"
#include "WorkerThread.h"
#include "Logic.h"
#include "Cfg.h"
#include "Common/TimeUtil.h"
#include "Common/StringTokenizer.h"

const char* s_HelpInfo = "";
//////////////////////////////////////////////////////////////////////////
WorldServer::WorldServer() : m_IsActive(false)
{
	m_LogicWorker = NULL;
	m_TcpService = NULL;
}

WorldServer::~WorldServer()
{
	delete m_LogicWorker;
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

    m_LogicWorker = new WorkerThread<GObject::Logic>(new GObject::Logic());
	
    return true;
}

void WorldServer::UnInit()
{
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
    m_LogicWorker->Run();

    ServerCommonConfig server_cfg(cfg.serverType,cfg.serverUID,cfg.tcpPort);
    for (auto& iter: cfg.serverConnectList)
    {
        server_cfg.AddConnectList(std::get<0>(iter),std::get<1>(iter),std::get<2>(iter),std::get<3>(iter));
    }

	m_TcpService = new Network::TcpServerWrapper(server_cfg);
	m_TcpService->Start();

    m_LogicWorker->join();
	m_TcpService->Join();

	delete m_TcpService;
}

void WorldServer::Shutdown()
{
	//关闭网络线程
	m_TcpService->UnInit();

    // XXX: erase all event
	Thread::sleep(2000);

    m_LogicWorker->Shutdown();
	
    Thread::sleep(2000);
}
    
GObject::Logic& WorldServer::GetLogic()
{
    return Worker<GObject::Logic>();
}

