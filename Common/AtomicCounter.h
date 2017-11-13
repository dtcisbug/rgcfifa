#ifndef Foundation_AtomicCounter_INCLUDED
#define Foundation_AtomicCounter_INCLUDED


#include "Platform.h"
#if _OS == _OS_MAC_OS_X
#include <libkern/OSAtomic.h>
#else
#include "Mutex.h"
#endif // _OS



class AtomicCounter
	/// This class implements a simple counter, which
	/// provides atomic operations that are safe to
	/// use in a multithreaded environment.
	///
	/// Typical usage of AtomicCounter is for implementing
	/// reference counting and similar things.
	///
	/// On some platforms, the implementation of AtomicCounter
	/// is based on atomic primitives specific to the platform
	/// (such as InterlockedIncrement, etc. on Windows), and
	/// thus very efficient. On platforms that do not support
	/// atomic primitives, operations are guarded by a FastMutex.
	///
	/// The following platforms currently have atomic
	/// primitives:
	///   - Windows
	///   - Mac OS X
{
public:
	typedef int ValueType; /// The underlying integer type.

	AtomicCounter();
		/// Creates a new AtomicCounter and initializes it to zero.

	explicit AtomicCounter(ValueType initialValue);
		/// Creates a new AtomicCounter and initializes it with
		/// the given value.

	AtomicCounter(const AtomicCounter& counter);
		/// Creates the counter by copying another one.

	~AtomicCounter();
		/// Destroys the AtomicCounter.

	AtomicCounter& operator = (const AtomicCounter& counter);
		/// Assigns the value of another AtomicCounter.

	AtomicCounter& operator = (ValueType value);
		/// Assigns a value to the counter.

	operator ValueType () const;
		/// Returns the value of the counter.

	ValueType value() const;
		/// Returns the value of the counter.

	ValueType operator ++ (); // prefix
		/// Increments the counter and returns the result.

	ValueType operator ++ (int); // postfix
		/// Increments the counter and returns the previous value.

	ValueType operator -- (); // prefix
		/// Decrements the counter and returns the result.

	ValueType operator -- (int); // postfix
		/// Decrements the counter and returns the previous value.

	bool operator ! () const;
		/// Returns true if the counter is zero, false otherwise.

private:
#if _OS == _OS_WINDOWS_NT
	typedef volatile LONG ImplType;
#elif _OS == _OS_MAC_OS_X
	typedef int32_t ImplType;
#else // generic implementation based on FastMutex
	struct ImplType
	{
		mutable FastMutex mutex;
		volatile int      value;
	};
#endif // _OS

	ImplType _counter;
};


//
// inlines
//


#if _OS == _OS_WINDOWS_NT
//
// Windows
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	return _counter;
}


inline AtomicCounter::ValueType AtomicCounter::value() const
{
	return _counter;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	return InterlockedIncrement(&_counter);
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	ValueType result(_counter);
	InterlockedIncrement(&_counter);
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	return InterlockedDecrement(&_counter);
}


inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	ValueType result(_counter);
	InterlockedDecrement(&_counter);
	return result;
}


inline bool AtomicCounter::operator ! () const
{
	return _counter == 0;
}


#elif _OS == _OS_MAC_OS_X
//
// Mac OS X
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	return _counter;
}


inline AtomicCounter::ValueType AtomicCounter::value() const
{
	return _counter;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	return OSAtomicIncrement32(&_counter);
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	ValueType result(_counter);
	OSAtomicIncrement32(&_counter);
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	return OSAtomicDecrement32(&_counter);
}


inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	ValueType result(_counter);
	OSAtomicDecrement32(&_counter);
	return result;
}


inline bool AtomicCounter::operator ! () const
{
	return _counter == 0;
}


#else
//
// Generic implementation based on FastMutex
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::value() const
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = ++_counter.value;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value++;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = --_counter.value;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value--;
	}
	return result;
}


inline bool AtomicCounter::operator ! () const
{
	bool result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value == 0;
	}
	return result;
}


#endif // _OS


#endif // Foundation_AtomicCounter_INCLUDED
