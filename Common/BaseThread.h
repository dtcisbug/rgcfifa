#ifndef BASETHREAD_INC
#define BASETHREAD_INC

#include "Thread.h"
#include "URandom.h"

class BaseThread:
	public Thread
{
public:
	BaseThread(): Thread() {};
	/// Creates a named thread. Call start() to start it.
	virtual ~BaseThread() {};

public:
	virtual void Start() = 0;		//开启线程
	virtual void Run() = 0;
	virtual void Stop() = 0;		//暂停线程执行
	virtual void Shutdown() = 0;	//终止线程执行
	virtual void Wait() = 0;		//等待线程结束

public:
	URandom uRandom;
};


//////////////////////////////////////////////////////////////////////////


#endif
