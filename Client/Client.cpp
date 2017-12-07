#include "Common/Config.h"

#include "Client.h"
#include "Cfg.h"
#include "Common/TimeUtil.h"
#include "Common/StringTokenizer.h"

//////////////////////////////////////////////////////////////////////////
Client::Client() : m_IsActive(false)
{
	m_TcpService = NULL;
}

Client::~Client()
{
	delete m_TcpService;
}

bool Client::Init()
{
    Network::Initialize();
	//读取配置文件
	TimeUtil::Init();

	m_TcpService = new Network::TcpClientWrapper();

    return true;
}

void Client::UnInit()
{
	Network::Uninitialize();
}

void Client::SetActive(bool active)
{
	m_IsActive = active;
}

bool Client::IsActive() const
{
	return m_IsActive;
}

void Client::Run()
{	
	m_TcpService->Start();

	//m_TcpService->Join();

	//delete m_TcpService;
}

void Client::Shutdown()
{
	//关闭网络线程
	m_TcpService->UnInit();

    // XXX: erase all event
	Thread::sleep(2000);
}

