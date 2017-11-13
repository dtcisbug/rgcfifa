#include "Config.h"
#include "URandom.h"
#include "BaseThread.h"

#ifdef _WIN32

inline int rand_r(unsigned int* seed)
{
	return rand();
}

#endif

URandom::URandom()
{
	seed();
}

URandom::URandom( UInt32 rseed )
{
	seed(rseed);
}

UInt32 URandom::operator()()
{
	return next();
}

UInt32 URandom::operator()( UInt32 modulo )
{
    if (!modulo)
        return 0;
	return next() % modulo;
}

UInt32 URandom::operator()(UInt32 min, UInt32 max)
{
    if(min==max)
        return min;
    else if (min > max)
        return max + (int) (((double) min - (double)max + 1.0) * rand_r(_fptr) / (RAND_MAX + 1.0));
    else
        return min + (int) (((double) max - (double)min + 1.0) * rand_r(_fptr) / (RAND_MAX + 1.0));
    return 0;
}

UInt32 uRand()
{
	return static_cast<BaseThread *>(Thread::current())->uRandom();
}

UInt32 uRand(UInt32 modulo)
{
	return static_cast<BaseThread *>(Thread::current())->uRandom(modulo);
}

extern "C" unsigned int uRandom(unsigned int modulo)
{
	return uRand(modulo);
}

URandom& URandom::current()
{
    return static_cast<BaseThread *>(Thread::current())->uRandom;
}

