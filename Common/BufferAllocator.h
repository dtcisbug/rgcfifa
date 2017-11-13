#ifndef Foundation_BufferAllocator_INCLUDED
#define Foundation_BufferAllocator_INCLUDED


#include "Platform.h"
#include <ios>
#include <cstddef>


template <typename ch>
class BufferAllocator
	/// The BufferAllocator used if no specific
	/// BufferAllocator has been specified.
{
public:
	typedef ch char_type;

	static char_type* allocate(std::streamsize size)
	{
		return new char_type[static_cast<std::size_t>(size)];
	}

	static void deallocate(char_type* ptr, std::streamsize size)
	{
		delete [] ptr;
	}
};



#endif // Foundation_BufferAllocator_INCLUDED
