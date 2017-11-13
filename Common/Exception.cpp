#include "Config.h"

#include "Exception.h"
#include <typeinfo>


Exception::Exception(int code): _pNested(0), _code(code)
{
}


Exception::Exception(const std::string& msg, int code): _msg(msg), _pNested(0), _code(code)
{
}


Exception::Exception(const std::string& msg, const std::string& arg, int code): _msg(msg), _pNested(0), _code(code)
{
	if (!arg.empty())
	{
		_msg.append(": ");
		_msg.append(arg);
	}
}


Exception::Exception(const std::string& msg, const Exception& nested, int code): _msg(msg), _pNested(nested.clone()), _code(code)
{
}


Exception::Exception(const Exception& exc):
	std::exception(exc),
	_msg(exc._msg),
	_code(exc._code)
{
	_pNested = exc._pNested ? exc._pNested->clone() : 0;
}


Exception::~Exception() throw()
{
	delete _pNested;
}


Exception& Exception::operator = (const Exception& exc)
{
	if (&exc != this)
	{
		delete _pNested;
		_msg     = exc._msg;
		_pNested = exc._pNested ? exc._pNested->clone() : 0;
		_code    = exc._code;
	}
	return *this;
}


const char* Exception::name() const throw()
{
	return "Exception";
}


const char* Exception::className() const throw()
{
	return typeid(*this).name();
}


const char* Exception::what() const throw()
{
	return name();
}


std::string Exception::displayText() const
{
	std::string txt = name();
	if (!_msg.empty())
	{
		txt.append(": ");
		txt.append(_msg);
	}
	return txt;
}


void Exception::extendedMessage(const std::string& arg)
{
	if (!arg.empty())
	{
		if (!_msg.empty()) _msg.append(": ");
		_msg.append(arg);
	}
}


Exception* Exception::clone() const
{
	return new Exception(*this);
}


void Exception::rethrow() const
{
	throw *this;
}


_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")


_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")
