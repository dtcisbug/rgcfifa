#include "Mutex_POSIX.h"
#include "Timestamp.h"
#include <sys/select.h>
#include <unistd.h>
#include <sys/time.h>


#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS - 200112L) >= 0L
#if defined(_POSIX_THREADS) && (_POSIX_THREADS - 200112L) >= 0L
#define POCO_HAVE_MUTEX_TIMEOUT
#endif
#endif


MutexImpl::MutexImpl()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
#if defined(PTHREAD_MUTEX_RECURSIVE_NP)
	pthread_mutexattr_settype_np(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#elif !defined(POCO_VXWORKS)
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#endif
	if (pthread_mutex_init(&_mutex, &attr))
	{
		pthread_mutexattr_destroy(&attr);
		throw SystemException("cannot create mutex");
	}
	pthread_mutexattr_destroy(&attr);
}


MutexImpl::MutexImpl(bool fast)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
#if defined(PTHREAD_MUTEX_RECURSIVE_NP)
	pthread_mutexattr_settype_np(&attr, fast ? PTHREAD_MUTEX_NORMAL_NP : PTHREAD_MUTEX_RECURSIVE_NP);
#elif !defined(POCO_VXWORKS)
	pthread_mutexattr_settype(&attr, fast ? PTHREAD_MUTEX_NORMAL : PTHREAD_MUTEX_RECURSIVE);
#endif
	if (pthread_mutex_init(&_mutex, &attr))
	{
		pthread_mutexattr_destroy(&attr);
		throw SystemException("cannot create mutex");
	}
	pthread_mutexattr_destroy(&attr);
}


MutexImpl::~MutexImpl()
{
	pthread_mutex_destroy(&_mutex);
}


bool MutexImpl::tryLockImpl(long milliseconds)
{
#if defined(POCO_HAVE_MUTEX_TIMEOUT)
	struct timespec abstime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	abstime.tv_sec  = tv.tv_sec + milliseconds / 1000;
	abstime.tv_nsec = tv.tv_usec*1000 + (milliseconds % 1000)*1000000;
	if (abstime.tv_nsec >= 1000000000)
	{
		abstime.tv_nsec -= 1000000000;
		abstime.tv_sec++;
	}
	int rc = pthread_mutex_timedlock(&_mutex, &abstime);
	if (rc == 0)
		return true;
	else if (rc == ETIMEDOUT)
		return false;
	else
		throw SystemException("cannot lock mutex");
#else
	const int sleepMillis = 5;
	Timestamp now;
	Timestamp::TimeDiff diff(Timestamp::TimeDiff(milliseconds)*1000);
	do
	{
		int rc = pthread_mutex_trylock(&_mutex);
		if (rc == 0)
			return true;
		else if (rc != EBUSY)
			throw SystemException("cannot lock mutex");
#if defined(POCO_VXWORKS)
		struct timespec ts;
		ts.tv_sec = 0;
		ts.tv_nsec = sleepMillis*1000000;
		nanosleep(&ts, NULL);

#else
		struct timeval tv;
		tv.tv_sec  = 0;
		tv.tv_usec = sleepMillis * 1000;
		select(0, NULL, NULL, NULL, &tv);
#endif
	}
	while (!now.isElapsed(diff));
	return false;
#endif
}


FastMutexImpl::FastMutexImpl(): MutexImpl(true)
{
}


FastMutexImpl::~FastMutexImpl()
{
}