#include "Config.h"

#include "Event.h"


#if defined(_OS_FAMILY_WINDOWS)
#include "Event_WIN32.cpp"
#else
#include "Event_POSIX.cpp"
#endif



Event::Event(bool autoReset): EventImpl(autoReset)
{
}


Event::~Event()
{
}

