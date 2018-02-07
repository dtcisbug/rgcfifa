#ifndef	SERVER_INC
#define SERVER_INC

#include "Common/Singleton.h"
#include "Network/TcpServerWrapper.h"
#include "WorkerThread.h"

extern const char* s_HelpInfo;

namespace GObject{
    class Logic;
}

class BaseThread;
class WorldServer : public Singleton<WorldServer>
{
public:
	void Run();
	bool ParseCommandInfor(Int32 argc, char * argv[]);

protected:
	WorldServer();
	virtual ~WorldServer();
	friend class Singleton<WorldServer>;

public:
	bool Init(const char * = NULL, const char * = NULL, int num = 0);
	void Shutdown();
	void UnInit();
	void SetActive(bool active);
	bool IsActive() const;

public:
	inline Network::TcpServerWrapper* GetTcpService() {return m_TcpService;}
    GObject::Logic& GetLogic();

protected:
	template <typename WorkerType>
	inline WorkerType& Worker()
	{
		return (dynamic_cast<WorkerThread<WorkerType>*>(m_LogicWorker))->Worker();
	}

private:
	bool	m_IsActive;

	//////////////////////////////////////////////////////////////////////////
public:
	BaseThread*	m_LogicWorker;
	Network::TcpServerWrapper* m_TcpService;

};

#define SERVER()		WorldServer::Instance()
#define NETWORK()		SERVER().GetTcpService()
#define LOGIC()			SERVER().GetLogic()

#define CURRENT_THREAD_ID() WorkerThread<WorkerRunner<> >::LocalWorker().GetThreadID()
inline  bool  IsMainThread()
{
    return Thread::current() == 0;
}
#endif

