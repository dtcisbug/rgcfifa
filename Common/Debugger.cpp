#include "Config.h"

#include "Debugger.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>
#if defined(_OS_FAMILY_UNIX)
	#include <unistd.h>
	#include <signal.h>
#endif


// NOTE: In this module, we use the C library functions (fputs) for,
// output since, at the time we're called, the C++ iostream objects //COUT, etc.
// might not have been initialized yet.


bool Debugger::isAvailable()
{
#if defined(_DEBUG)
	#if defined(_OS_FAMILY_WINDOWS)
		#if defined(_WIN32_WCE)
			#if (_WIN32_WCE >= 600)
			    BOOL isDebuggerPresent;
			    if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &isDebuggerPresent))
			    {
					return isDebuggerPresent ? true : false;
				}
				return false;
			#else
				return false;
			#endif
		#else
			return IsDebuggerPresent() ? true : false;
		#endif
	#elif defined(_VXWORKS)
		return false;
	#elif defined(_OS_FAMILY_UNIX)
		return std::getenv("_ENABLE_DEBUGGER") ? true : false;
	#elif defined(_OS_FAMILY_VMS)
		return true;
	#endif
#else
	return false;
#endif
}


void Debugger::message(const std::string& msg)
{
#if defined(_DEBUG)
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	std::fputs(msg.c_str(), stderr);
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	#if defined(_OS_FAMILY_WINDOWS)
	if (isAvailable())
	{
#if defined(_WIN32_UTF8) && !defined(_NO_WSTRING)
		std::wstring umsg;
		UnicodeConverter::toUTF16(msg, umsg);
		umsg += '\n';
		OutputDebugStringW(umsg.c_str());
#else
		OutputDebugStringA(msg.c_str());
		OutputDebugStringA("\n");
#endif
	}
	#elif defined(_OS_FAMILY_UNIX)
	#elif defined(_OS_FAMILY_VMS)
	#endif
#endif
}


void Debugger::message(const std::string& msg, const char* file, int line)
{
#if defined(_DEBUG)
	std::ostringstream str;
	str << msg << " [in file \"" << file << "\", line " << line << "]";
	message(str.str());
#endif
}


void Debugger::enter()
{
#if defined(_DEBUG)
	#if defined(_OS_FAMILY_WINDOWS)
	if (isAvailable())
	{
		DebugBreak();
	}
	#elif defined(_VXWORKS)
	{
		// not supported
	}
	#elif defined(_OS_FAMILY_UNIX)
	if (isAvailable())
	{
		kill(getpid(), SIGINT);
	}
	#elif defined(_OS_FAMILY_VMS)
	{
		const char* cmd = "\012SHOW CALLS";
		lib$signal(SS$_DEBUG, 1, cmd);
	}
	#endif
#endif
}


void Debugger::enter(const std::string& msg)
{
#if defined(_DEBUG)
	message(msg);
	enter();
#endif
}


void Debugger::enter(const std::string& msg, const char* file, int line)
{
#if defined(_DEBUG)
	message(msg, file, line);
	enter();
#endif
}


void Debugger::enter(const char* file, int line)
{
#if defined(_DEBUG)
	message("BREAK", file, line);
	enter();
#endif
}
