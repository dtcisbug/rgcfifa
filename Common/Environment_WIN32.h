#ifndef Foundation_Environment_WIN32_INCLUDED
#define Foundation_Environment_WIN32_INCLUDED


#include "Platform.h"



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
};


#endif // Foundation_Environment_WIN32_INCLUDED
