#ifndef Foundation_DirectoryIterator_WIN32_INCLUDED
#define Foundation_DirectoryIterator_WIN32_INCLUDED


#include "Platform.h"


class  DirectoryIteratorImpl
{
public:
	DirectoryIteratorImpl(const std::string& path);
	~DirectoryIteratorImpl();

	void duplicate();
	void release();

	const std::string& get() const;
	const std::string& next();

private:
	HANDLE          _fh;
	WIN32_FIND_DATA _fd;
	std::string     _current;
	int _rc;
};


//
// inlines
//
const std::string& DirectoryIteratorImpl::get() const
{
	return _current;
}


inline void DirectoryIteratorImpl::duplicate()
{
	++_rc;
}


inline void DirectoryIteratorImpl::release()
{
	if (--_rc == 0)
		delete this;
}


#endif // Foundation_DirectoryIterator_WIN32_INCLUDED
