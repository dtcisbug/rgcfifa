#ifndef _ATOMICVAL_H_
#define _ATOMICVAL_H_
#include "Config.h"

template<typename T>
class AtomicVal
{
public:
	AtomicVal(): _val(0) {}
	explicit AtomicVal(T val):
#ifdef _WIN32
		_val((Int32)val)
#else
		_val((size_t)val)
#endif
		{}
	AtomicVal(const AtomicVal<T>& other): _val(other._val) {}
	inline operator T() const
	{
#ifdef _WIN32
		return (const T)_val;
#else
		return (const T)__sync_fetch_and_xor((volatile size_t *)&_val, 0);
#endif
	}
	inline T value() const { return *this; }
	inline AtomicVal<T>& operator=(T val)
	{
#ifdef _WIN32
		InterlockedExchange((volatile LONG *)&_val, (LONG)val);
#else
		size_t oldval;
		do {
			oldval = __sync_fetch_and_xor((volatile size_t *)&_val, 0);
		} while(!__sync_bool_compare_and_swap(&_val, oldval, val));
#endif
		return *this;
	}
	inline AtomicVal<T>& operator=(const AtomicVal<T>& other)
	{
		return (*this) = other.value();
	}
	inline T operator ++ ()
	{
#ifdef _WIN32
		return (T)InterlockedIncrement(&_val);
#else
		return (T)__sync_add_and_fetch(&_val, 1);
#endif
	}
	inline T operator ++ (int)
	{
#ifdef _WIN32
		T result = _val;
		InterlockedIncrement(&_val);
		return result;
#else
		return (T)__sync_fetch_and_add(&_val, 1);
#endif
	}
	inline T operator -- ()
	{
#ifdef _WIN32
		return (T)InterlockedDecrement(&_val);
#else
		return (T)__sync_sub_and_fetch(&_val, 1);
#endif
	}
	inline T operator -- (int)
	{
#ifdef _WIN32
		T result = _val;
		InterlockedDecrement(&_val);
		return result;
#else
		return (T)__sync_fetch_and_sub(&_val, 1);
#endif
	}
	inline T operator += (T n)
	{
#ifdef _WIN32
		InterlockedExchangeAdd(&_val, n);
		return _val;
#else
		return (T)__sync_fetch_and_add(&_val, n);
#endif
	}
	inline T operator -= (T n)
	{
#ifdef _WIN32
		InterlockedExchangeAdd(&_val, -n);
		return _val;
#else
		return (T)__sync_fetch_and_sub(&_val, n);
#endif
	}

private:
#ifdef _WIN32
	volatile LONG _val;
#else
	volatile size_t _val;
#endif
};

#endif // _ATOMICVAL_H_
