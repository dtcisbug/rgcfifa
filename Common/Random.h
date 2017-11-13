#ifndef Foundation_Random_INCLUDED
#define Foundation_Random_INCLUDED


#include "Platform.h"



class Random
	/// A better random number generator.
	/// Random implements a pseudo random number generator
	/// (PRNG). The PRNG is a nonlinear additive
	/// feedback random number generator using 256 bytes
	/// of state information and a period of up to 2^69.
{
public:
	enum Type
	{
		RND_STATE_0   =   8,  /// linear congruential
		RND_STATE_32  =  32,  /// x**7 + x**3 + 1
		RND_STATE_64  =  64,  /// x**15 + x + 1
		RND_STATE_128 = 128,  /// x**31 + x**3 + 1
		RND_STATE_256 = 256   /// x**63 + x + 1
	};

	Random(int stateSize = 256);
		/// Creates and initializes the PRNG.
		/// Specify either a state buffer size
		/// (8 to 256 bytes) or one of the Type values.

	~Random();
		/// Destroys the PRNG.

	void seed(UInt32 seed);
		/// Seeds the pseudo random generator with the given seed.

	void seed();
		/// Seeds the pseudo random generator with a random seed
		/// obtained from a RandomInputStream.

	UInt32 next();
		/// Returns the next 31-bit pseudo random number.

	UInt32 next(UInt32 n);
		/// Returns the next 31-bit pseudo random number modulo n.

	char nextChar();
		/// Returns the next pseudo random character.

	bool nextBool();
		/// Returns the next boolean pseudo random value.

	float nextFloat();
		/// Returns the next float pseudo random number between 0.0 and 1.0.

	double nextDouble();
		/// Returns the next double pseudo random number between 0.0 and 1.0.

protected:
	void initState(UInt32 seed, char* arg_state, Int32 n);
	static UInt32 goodRand(Int32 x);

	enum
	{
		MAX_TYPES = 5,
		NSHUFF    = 50
	};

	UInt32* _fptr;
	UInt32* _rptr;
	UInt32* _state;
	int     _randType;
	int     _randDeg;
	int     _randSep;
	UInt32* _endPtr;
	char*  _pBuffer;
};


//
// inlines
//
inline UInt32 Random::next(UInt32 n)
{
	return next() % n;
}


inline char Random::nextChar()
{
	return char((next() >> 3) & 0xFF);
}


inline bool Random::nextBool()
{
	return (next() & 0x1000) != 0;
}


inline float Random::nextFloat()
{
	return float(next()) / 0x7FFFFFFF;
}


inline double Random::nextDouble()
{
	return double(next()) / 0x7FFFFFFF;
}



#endif // Foundation_Random_INCLUDED
