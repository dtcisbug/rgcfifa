#include "Config.h"

#include "Mutex.h"


#if defined(_OS_FAMILY_WINDOWS)
#include "Mutex_WIN32.cpp"
#else
#include "Mutex_POSIX.cpp"
#endif



Mutex::Mutex()
{
}


Mutex::~Mutex()
{
}


FastMutex::FastMutex()
{
}


FastMutex::~FastMutex()
{
}

