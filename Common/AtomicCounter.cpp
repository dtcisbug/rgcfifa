#include "Config.h"

#include "AtomicCounter.h"


#if _OS == _OS_WINDOWS_NT
//
// Windows
//
AtomicCounter::AtomicCounter():
	_counter(0)
{
}


AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue):
	_counter(initialValue)
{
}


AtomicCounter::AtomicCounter(const AtomicCounter& counter):
	_counter(counter.value())
{
}


AtomicCounter::~AtomicCounter()
{
}


AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
{
	InterlockedExchange(&_counter, counter.value());
	return *this;
}


AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
{
	InterlockedExchange(&_counter, value);
	return *this;
}


#elif _OS == _OS_MAC_OS_X
//
// Mac OS X
//
AtomicCounter::AtomicCounter():
	_counter(0)
{
}


AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue):
	_counter(initialValue)
{
}


AtomicCounter::AtomicCounter(const AtomicCounter& counter):
	_counter(counter.value())
{
}


AtomicCounter::~AtomicCounter()
{
}


AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
{
	_counter = counter.value();
	return *this;
}


AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
{
	_counter = value;
	return *this;
}


#else
//
// Generic implementation based on FastMutex
//
AtomicCounter::AtomicCounter()
{
	_counter.value = 0;
}


AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue)
{
	_counter.value = initialValue;
}


AtomicCounter::AtomicCounter(const AtomicCounter& counter)
{
	_counter.value = counter.value();
}


AtomicCounter::~AtomicCounter()
{
}


AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
{
	FastMutex::ScopedLock lock(_counter.mutex);
	_counter.value = counter.value();
	return *this;
}


AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
{
	FastMutex::ScopedLock lock(_counter.mutex);
	_counter.value = value;
	return *this;
}

#endif
