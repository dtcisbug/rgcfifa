#ifndef Foundation_Exception_INCLUDED
#define Foundation_Exception_INCLUDED


#include "Platform.h"
#include <stdexcept>



class  Exception: public std::exception
	/// This is the base class for all exceptions defined
	/// in the class library.
{
public:
	Exception(const std::string& msg, int code = 0);
		/// Creates an exception.

	Exception(const std::string& msg, const std::string& arg, int code = 0);
		/// Creates an exception.

	Exception(const std::string& msg, const Exception& nested, int code = 0);
		/// Creates an exception and stores a clone
		/// of the nested exception.

	Exception(const Exception& exc);
		/// Copy constructor.

	~Exception() throw();
		/// Destroys the exception and deletes the nested exception.

	Exception& operator = (const Exception& exc);
		/// Assignment operator.

	virtual const char* name() const throw();
		/// Returns a static string describing the exception.

	virtual const char* className() const throw();
		/// Returns the name of the exception class.

	virtual const char* what() const throw();
		/// Returns a static string describing the exception.
		///
		/// Same as name(), but for compatibility with std::exception.

	const Exception* nested() const;
		/// Returns a pointer to the nested exception, or
		/// null if no nested exception exists.

	const std::string& message() const;
		/// Returns the message text.

	int code() const;
		/// Returns the exception code if defined.

	std::string displayText() const;
		/// Returns a string consisting of the
		/// message name and the message text.

	virtual Exception* clone() const;
		/// Creates an exact copy of the exception.
		///
		/// The copy can later be thrown again by
		/// invoking rethrow() on it.

	virtual void rethrow() const;
		/// (Re)Throws the exception.
		///
		/// This is useful for temporarily storing a
		/// copy of an exception (see clone()), then
		/// throwing it again.

protected:
	Exception(int code = 0);
		/// Standard constructor.

	void message(const std::string& msg);
		/// Sets the message for the exception.

	void extendedMessage(const std::string& arg);
		/// Sets the extended message for the exception.

private:
	std::string _msg;
	Exception*  _pNested;
	int			_code;
};


//
// inlines
//
inline const Exception* Exception::nested() const
{
	return _pNested;
}


inline const std::string& Exception::message() const
{
	return _msg;
}


inline void Exception::message(const std::string& msg)
{
	_msg = msg;
}


inline int Exception::code() const
{
	return _code;
}


//
// Macros for quickly declaring and implementing exception classes.
// Unfortunately, we cannot use a template here because character
// pointers (which we need for specifying the exception name)
// are not allowed as template arguments.
//
#define _DECLARE_EXCEPTION(API, CLS, BASE) \
	class API CLS: public BASE														\
	{																				\
	public:																			\
		CLS(int code = 0);															\
		CLS(const std::string& msg, int code = 0);									\
		CLS(const std::string& msg, const std::string& arg, int code = 0);			\
		CLS(const std::string& msg, const Exception& exc, int code = 0);		\
		CLS(const CLS& exc);														\
		~CLS() throw();																\
		CLS& operator = (const CLS& exc);											\
		const char* name() const throw();											\
		const char* className() const throw();										\
		Exception* clone() const;												\
		void rethrow() const;														\
	};


#define _IMPLEMENT_EXCEPTION(CLS, BASE, NAME)													\
	CLS::CLS(int code): BASE(code)																	\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, int code): BASE(msg, code)										\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, const std::string& arg, int code): BASE(msg, arg, code)		\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, const Exception& exc, int code): BASE(msg, exc, code)	\
	{																								\
	}																								\
	CLS::CLS(const CLS& exc): BASE(exc)																\
	{																								\
	}																								\
	CLS::~CLS() throw()																				\
	{																								\
	}																								\
	CLS& CLS::operator = (const CLS& exc)															\
	{																								\
		BASE::operator = (exc);																		\
		return *this;																				\
	}																								\
	const char* CLS::name() const throw()															\
	{																								\
		return NAME;																				\
	}																								\
	const char* CLS::className() const throw()														\
	{																								\
		return typeid(*this).name();																\
	}																								\
	Exception* CLS::clone() const																\
	{																								\
		return new CLS(*this);																		\
	}																								\
	void CLS::rethrow() const																		\
	{																								\
		throw *this;																				\
	}


//
// Standard exception classes
//
_DECLARE_EXCEPTION(, LogicException, Exception)
_DECLARE_EXCEPTION(, AssertionViolationException, LogicException)
_DECLARE_EXCEPTION(, NullPointerException, LogicException)
_DECLARE_EXCEPTION(, NullValueException, LogicException)
_DECLARE_EXCEPTION(, BugcheckException, LogicException)
_DECLARE_EXCEPTION(, InvalidArgumentException, LogicException)
_DECLARE_EXCEPTION(, NotImplementedException, LogicException)
_DECLARE_EXCEPTION(, RangeException, LogicException)
_DECLARE_EXCEPTION(, IllegalStateException, LogicException)
_DECLARE_EXCEPTION(, InvalidAccessException, LogicException)
_DECLARE_EXCEPTION(, SignalException, LogicException)
_DECLARE_EXCEPTION(, UnhandledException, LogicException)

_DECLARE_EXCEPTION(, RuntimeException, Exception)
_DECLARE_EXCEPTION(, NotFoundException, RuntimeException)
_DECLARE_EXCEPTION(, ExistsException, RuntimeException)
_DECLARE_EXCEPTION(, TimeoutException, RuntimeException)
_DECLARE_EXCEPTION(, SystemException, RuntimeException)
_DECLARE_EXCEPTION(, RegularExpressionException, RuntimeException)
_DECLARE_EXCEPTION(, LibraryLoadException, RuntimeException)
_DECLARE_EXCEPTION(, LibraryAlreadyLoadedException, RuntimeException)
_DECLARE_EXCEPTION(, NoThreadAvailableException, RuntimeException)
_DECLARE_EXCEPTION(, PropertyNotSupportedException, RuntimeException)
_DECLARE_EXCEPTION(, PoolOverflowException, RuntimeException)
_DECLARE_EXCEPTION(, NoPermissionException, RuntimeException)
_DECLARE_EXCEPTION(, OutOfMemoryException, RuntimeException)
_DECLARE_EXCEPTION(, DataException, RuntimeException)

_DECLARE_EXCEPTION(, DataFormatException, DataException)
_DECLARE_EXCEPTION(, SyntaxException, DataException)
_DECLARE_EXCEPTION(, CircularReferenceException, DataException)
_DECLARE_EXCEPTION(, PathSyntaxException, SyntaxException)
_DECLARE_EXCEPTION(, IOException, RuntimeException)
_DECLARE_EXCEPTION(, ProtocolException, IOException)
_DECLARE_EXCEPTION(, FileException, IOException)
_DECLARE_EXCEPTION(, FileExistsException, FileException)
_DECLARE_EXCEPTION(, FileNotFoundException, FileException)
_DECLARE_EXCEPTION(, PathNotFoundException, FileException)
_DECLARE_EXCEPTION(, FileReadOnlyException, FileException)
_DECLARE_EXCEPTION(, FileAccessDeniedException, FileException)
_DECLARE_EXCEPTION(, CreateFileException, FileException)
_DECLARE_EXCEPTION(, OpenFileException, FileException)
_DECLARE_EXCEPTION(, WriteFileException, FileException)
_DECLARE_EXCEPTION(, ReadFileException, FileException)
_DECLARE_EXCEPTION(, UnknownURISchemeException, RuntimeException)

_DECLARE_EXCEPTION(, ApplicationException, Exception)
_DECLARE_EXCEPTION(, BadCastException, RuntimeException)



#endif // Foundation_Exception_INCLUDED
