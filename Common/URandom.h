#ifndef _URANDOM_H_
#define _URANDOM_H_

#include "Random.h"

class URandom:
	public Random
{
public:
	URandom();
	URandom(UInt32);
	UInt32 operator()();
	UInt32 operator()(UInt32 modulo);
	UInt32 operator()(UInt32 min, UInt32 max);
    static URandom& current();
};

UInt32 uRand();
UInt32 uRand(UInt32 modulo);

#endif // _URANDOM_H_
