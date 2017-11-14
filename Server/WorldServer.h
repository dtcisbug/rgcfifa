#ifndef	SERVER_INC
#define SERVER_INC

#include "Common/Singleton.h"
#include "Network/TcpServerWrapper.h"
#include "ServerTypes.h"
#include "WorkerThread.h"

extern const char* s_HelpInfo;

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

protected:
	template <typename WorkerType>
	inline WorkerType& Worker(UInt8 worker)
	{
		return (dynamic_cast<WorkerThread<WorkerType>*>(m_AllWorker[worker]))->Worker();
	}

private:
	bool	m_IsActive;
	ServerInfor m_ServerInfor;

	//////////////////////////////////////////////////////////////////////////
public:
	BaseThread*	m_AllWorker[MAX_THREAD_NUM];
	Network::TcpServerWrapper* m_TcpService;

public:
    void Up();
    void Down();
    void State(const char* action, int serverNum);

    void updateState(const char* action);

};

#define SERVER()		WorldServer::Instance()
#define NETWORK()		SERVER().GetTcpService()
#define WORLD()			SERVER().GetWorld()

#define CURRENT_THREAD_ID() WorkerThread<WorkerRunner<> >::LocalWorker().GetThreadID()
inline  bool  IsMainThread()
{
    return Thread::current() == 0;
}
#endif

