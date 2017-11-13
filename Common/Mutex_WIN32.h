#ifndef Foundation_Mutex_WIN32_INCLUDED
#define Foundation_Mutex_WIN32_INCLUDED


#include "Platform.h"
#include "Exception.h"


class MutexImpl
{
protected:
	MutexImpl();
	~MutexImpl();
	void lockImpl();
	bool tryLockImpl();
	bool tryLockImpl(long milliseconds);
	void unlockImpl();

private:
	CRITICAL_SECTION _cs;
};


typedef MutexImpl FastMutexImpl;


//
// inlines
//
inline void MutexImpl::lockImpl()
{
	try
	{
		EnterCriticalSection(&_cs);
	}
	catch (...)
	{
		throw SystemException("cannot lock mutex");
	}
}


inline bool MutexImpl::tryLockImpl()
{
	try
	{
		return TryEnterCriticalSection(&_cs) != 0;
	}
	catch (...)
	{
	}
	throw SystemException("cannot lock mutex");
}


inline void MutexImpl::unlockImpl()
{
	LeaveCriticalSection(&_cs);
}


#endif // Foundation_Mutex_WIN32_INCLUDED
