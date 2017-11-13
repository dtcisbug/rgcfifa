#ifndef Foundation_Buffer_INCLUDED
#define Foundation_Buffer_INCLUDED


#include "Platform.h"
#include <cstddef>


template <class T>
class Buffer
	/// A very simple buffer class that allocates a buffer of
	/// a given type and size in the constructor and
	/// deallocates the buffer in the destructor.
	///
	/// This class is useful everywhere where a temporary buffer
	/// is needed.
{
public:
	Buffer(std::size_t size):
		_size(size),
		_ptr(new T[size])
		/// Creates and allocates the Buffer.
	{
	}

	~Buffer()
		/// Destroys the Buffer.
	{
		delete [] _ptr;
	}

	std::size_t size() const
		/// Returns the size of the buffer.
	{
		return _size;
	}

	T* begin()
		/// Returns a pointer to the beginning of the buffer.
	{
		return _ptr;
	}

	const T* begin() const
		/// Returns a pointer to the beginning of the buffer.
	{
		return _ptr;
	}

	T* end()
		/// Returns a pointer to end of the buffer.
	{
		return _ptr + _size;
	}

	const T* end() const
		/// Returns a pointer to the end of the buffer.
	{
		return _ptr + _size;
	}

	T& operator [] (std::size_t index)
	{
		common_assert (index < _size);

		return _ptr[index];
	}

	const T& operator [] (std::size_t index) const
	{
		common_assert (index < _size);

		return _ptr[index];
	}

private:
	Buffer();
	Buffer(const Buffer&);
	Buffer& operator = (const Buffer&);

	std::size_t _size;
	T* _ptr;
};


#endif // Foundation_Buffer_INCLUDED
