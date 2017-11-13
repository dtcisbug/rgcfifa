#include "Config.h"

#include "Platform.h"
#include "Debugger.h"
#include "Exception.h"
#include <sstream>


namespace Common {

void Bugcheck::assertion(const char* cond, const char* file, int line)
{
	Debugger::enter(std::string("Assertion violation: ") + cond, file, line);
	throw AssertionViolationException(what(cond, file, line));
}


void Bugcheck::nullPointer(const char* ptr, const char* file, int line)
{
	Debugger::enter(std::string("NULL pointer: ") + ptr, file, line);
	throw NullPointerException(what(ptr, file, line));
}


void Bugcheck::bugcheck(const char* file, int line)
{
	Debugger::enter("Bugcheck", file, line);
	throw BugcheckException(what(0, file, line));
}


void Bugcheck::bugcheck(const char* msg, const char* file, int line)
{
	std::string m("Bugcheck");
	if (msg)
	{
		m.append(": ");
		m.append(msg);
	}
	Debugger::enter(m, file, line);
	throw BugcheckException(what(msg, file, line));
}


void Bugcheck::debugger(const char* file, int line)
{
	Debugger::enter(file, line);
}


void Bugcheck::debugger(const char* msg, const char* file, int line)
{
	Debugger::enter(msg, file, line);
}


std::string Bugcheck::what(const char* msg, const char* file, int line)
{
	std::ostringstream str;
	if (msg) str << msg << " ";
	str << "in file \"" << file << "\", line " << line;
	return str.str();
}

}
