#ifndef Foundation_Environment_UNIX_INCLUDED
#define Foundation_Environment_UNIX_INCLUDED


#include "Platform.h"
#include "Mutex.h"
#include <map>


class  EnvironmentImpl
{
public:
	typedef UInt8 NodeId[6]; /// Ethernet address.

	static std::string getImpl(const std::string& name);
	static bool hasImpl(const std::string& name);
	static void setImpl(const std::string& name, const std::string& value);
	static std::string osNameImpl();
	static std::string osVersionImpl();
	static std::string osArchitectureImpl();
	static std::string nodeNameImpl();
	static void nodeIdImpl(NodeId& id);
	static unsigned processorCountImpl();

private:
	typedef std::map<std::string, std::string> StringMap;

	static StringMap _map;
	static FastMutex _mutex;
};



#endif // Foundation_Environment_UNIX_INCLUDED
