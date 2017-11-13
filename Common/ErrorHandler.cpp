#include "Config.h"

#include "ErrorHandler.h"
#include "SingletonHolder.h"


ErrorHandler* ErrorHandler::_pHandler = ErrorHandler::defaultHandler();
FastMutex ErrorHandler::_mutex;


ErrorHandler::ErrorHandler()
{
}


ErrorHandler::~ErrorHandler()
{
}


void ErrorHandler::exception(const Exception& exc)
{
	common_debugger_msg(exc.what());
}


void ErrorHandler::exception(const std::exception& exc)
{
	common_debugger_msg(exc.what());
}


void ErrorHandler::exception()
{
	common_debugger_msg("unknown exception");
}


void ErrorHandler::handle(const Exception& exc)
{
	FastMutex::ScopedLock lock(_mutex);
	try
	{
		_pHandler->exception(exc);
	}
	catch (...)
	{
	}
}


void ErrorHandler::handle(const std::exception& exc)
{
	FastMutex::ScopedLock lock(_mutex);
	try
	{
		_pHandler->exception(exc);
	}
	catch (...)
	{
	}
}


void ErrorHandler::handle()
{
	FastMutex::ScopedLock lock(_mutex);
	try
	{
		_pHandler->exception();
	}
	catch (...)
	{
	}
}


ErrorHandler* ErrorHandler::set(ErrorHandler* pHandler)
{
	common_check_ptr(pHandler);

	FastMutex::ScopedLock lock(_mutex);
	ErrorHandler* pOld = _pHandler;
	_pHandler = pHandler;
	return pOld;
}


ErrorHandler* ErrorHandler::defaultHandler()
{
	// NOTE: Since this is called to initialize the static _pHandler
	// variable, sh has to be a local static, otherwise we run
	// into static initialization order issues.
	static SingletonHolder<ErrorHandler> sh;
	return sh.get();
}

