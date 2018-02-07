#ifndef	CLIENT_INC
#define CLIENT_INC

#include "Common/Singleton.h"
#include "Network/TcpServerWrapper.h"
//#include "WorkerThread.h"

namespace GObject{
    class Logic;
}

class BaseThread;
class Client: public Singleton<Client>
{
public:
	void Run();

protected:
	Client();
	virtual ~Client();
	friend class Singleton<Client>;

public:
	bool Init();
	void Shutdown();
	void UnInit();
	void SetActive(bool active);
	bool IsActive() const;

public:
	inline Network::TcpClientWrapper* GetTcpService() {return m_TcpService;}

private:
	bool	m_IsActive;

	//////////////////////////////////////////////////////////////////////////
public:
	Network::TcpClientWrapper* m_TcpService;

};

#define CLIENT()		Client::Instance()
#define CLIENT_NETWORK()		CLIENT().GetTcpService()

#endif

