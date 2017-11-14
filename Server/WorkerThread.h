#ifndef SERVERTHREAD_INC
#define SERVERTHREAD_INC

#include "Common/BaseThread.h"
#include "WorkerRunner.h"

template <typename WorkerType>
class WorkerThread:
	public BaseThread
{
public:
	WorkerThread(WorkerType* worker) : m_Worker(worker)
	{
	};
	virtual ~WorkerThread()
	{
		delete m_Worker;
	}

public:
	virtual void Start();
	virtual void Stop();
	virtual void Run();
	virtual void Shutdown();
	virtual void Wait();

public:
	inline WorkerType& Worker() { return *m_Worker; }


	inline static WorkerType& LocalWorker() {return static_cast<WorkerThread<WorkerType> *>(current())->Worker();}

private:
	static void WorkerProcess(void *);
private:
	WorkerType*	m_Worker;
};


//////////////////////////////////////////////////////////////////////////
template <typename WorkerType>
inline void WorkerThread<WorkerType>::WorkerProcess(void * param)
{
	WorkerType * pWorker = reinterpret_cast<WorkerType*>(param);

	pWorker->RunnerProc();
}

//////////////////////////////////////////////////////////////////////////
template <typename WorkerType>
inline void WorkerThread<WorkerType>::Start()
{
	// TODO
}

template <typename WorkerType>
inline void WorkerThread<WorkerType>::Run()
{
	assert(m_Worker != NULL);
	start(WorkerProcess, m_Worker);
}

template <typename WorkerType>
inline void WorkerThread<WorkerType>::Stop()
{
	// TODO
}

template <typename WorkerType>
inline void WorkerThread<WorkerType>::Shutdown()
{
	//FIXME---
	assert(m_Worker != NULL);
	m_Worker->Shutdown();
}

template <typename WorkerType>
inline void WorkerThread<WorkerType>::Wait()
{
	join();
}

#endif
