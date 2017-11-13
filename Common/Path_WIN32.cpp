#include "Path_WIN32.h"
#include "Exception.h"
#include "Environment_WIN32.h"






std::string PathImpl::currentImpl()
{
	char buffer[_MAX_PATH];
	DWORD n = GetCurrentDirectoryA(sizeof(buffer), buffer);
	if (n > 0 && n < sizeof(buffer))
	{
		std::string result(buffer, n);
		if (result[n - 1] != '\\')
			result.append("\\");
		return result;
	}
	else throw SystemException("Cannot get current directory");
}


std::string PathImpl::homeImpl()
{
	std::string result = EnvironmentImpl::getImpl("HOMEDRIVE");
	result.append(EnvironmentImpl::getImpl("HOMEPATH"));
	std::string::size_type n = result.size();
	if (n > 0 && result[n - 1] != '\\')
		result.append("\\");
	return result;
}


std::string PathImpl::tempImpl()
{
	char buffer[_MAX_PATH];
	DWORD n = GetTempPathA(sizeof(buffer), buffer);
	if (n > 0 && n < sizeof(buffer))
	{
		std::string result(buffer, n);
		if (result[n - 1] != '\\')
			result.append("\\");
		return result;
	}
	else throw SystemException("Cannot get current directory");
}


std::string PathImpl::nullImpl()
{
	return "NUL:";
}


std::string PathImpl::expandImpl(const std::string& path)
{
	char buffer[_MAX_PATH];
	DWORD n = ExpandEnvironmentStringsA(path.c_str(), buffer, sizeof(buffer));
	if (n > 0 && n < sizeof(buffer))
		return std::string(buffer, n - 1);
	else
		return path;
}


void PathImpl::listRootsImpl(std::vector<std::string>& roots)
{
	roots.clear();
	char buffer[128];
	DWORD n = GetLogicalDriveStrings(sizeof(buffer) - 1, buffer);
	char* it = buffer;
	char* end = buffer + (n > sizeof(buffer) ? sizeof(buffer) : n);
	while (it < end)
	{
		std::string dev;
		while (it < end && *it) dev += *it++;
		roots.push_back(dev);
		++it;
	}
}



