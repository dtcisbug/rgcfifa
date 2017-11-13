#include "Config.h"

#include "ThreadLocal.h"
#include "SingletonHolder.h"
#include "Thread.h"



TLSAbstractSlot::TLSAbstractSlot()
{
}


TLSAbstractSlot::~TLSAbstractSlot()
{
}


ThreadLocalStorage::ThreadLocalStorage()
{
}


ThreadLocalStorage::~ThreadLocalStorage()
{
	for (TLSMap::iterator it = _map.begin(); it != _map.end(); ++it)
	{
		delete it->second;
	}
}


TLSAbstractSlot*& ThreadLocalStorage::get(const void* key)
{
	TLSMap::iterator it = _map.find(key);
	if (it == _map.end())
		return _map.insert(TLSMap::value_type(key, reinterpret_cast<TLSAbstractSlot*>(0))).first->second;
	else
		return it->second;
}


namespace
{
	static SingletonHolder<ThreadLocalStorage> sh;
}


ThreadLocalStorage& ThreadLocalStorage::current()
{
	Thread* pThread = Thread::current();
	if (pThread)
	{
		return pThread->tls();
	}
	else
	{
		return *sh.get();
	}
}


void ThreadLocalStorage::clear()
{
	Thread* pThread = Thread::current();
	if (pThread)
		pThread->clearTLS();
}
