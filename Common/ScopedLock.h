#ifndef Foundation_ScopedLocker_INCLUDED
#define Foundation_ScopedLocker_INCLUDED


#include "Platform.h"


template <class M>
class ScopedLocker
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex and locks it.
	/// The destructor unlocks the mutex.
{
public:
	ScopedLocker(M& mutex): _mutex(mutex)
	{
		_mutex.lock();
	}

	~ScopedLocker()
	{
		_mutex.unlock();
	}

private:
	M& _mutex;

	ScopedLocker();
	ScopedLocker(const ScopedLocker&);
	ScopedLocker& operator = (const ScopedLocker&);
};


template <class M>
class ScopedLockerWithUnlock
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex and locks it.
	/// The destructor unlocks the mutex.
	/// The unlock() member function allows for manual
	/// unlocking of the mutex.
{
public:
	ScopedLockerWithUnlock(M& mutex): _pMutex(&mutex)
	{
		_pMutex->lock();
	}

	~ScopedLockerWithUnlock()
	{
		unlock();
	}

	void unlock()
	{
		if (_pMutex)
		{
			_pMutex->unlock();
			_pMutex = 0;
		}
	}

private:
	M* _pMutex;

	ScopedLockerWithUnlock();
	ScopedLockerWithUnlock(const ScopedLockerWithUnlock&);
	ScopedLockerWithUnlock& operator = (const ScopedLockerWithUnlock&);
};


#endif // Foundation_ScopedLocker_INCLUDED
