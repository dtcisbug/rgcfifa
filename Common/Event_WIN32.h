#ifndef Foundation_Event_WIN32_INCLUDED
#define Foundation_Event_WIN32_INCLUDED


#include "Platform.h"
#include "Exception.h"



class EventImpl
{
protected:
	EventImpl(bool autoReset);
	~EventImpl();
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	void resetImpl();

private:
	HANDLE _event;
};


//
// inlines
//
inline void EventImpl::setImpl()
{
	if (!SetEvent(_event))
	{
		throw SystemException("cannot signal event");
	}
}


inline void EventImpl::resetImpl()
{
	if (!ResetEvent(_event))
	{
		throw SystemException("cannot reset event");
	}
}


#endif // Foundation_Event_WIN32_INCLUDED
