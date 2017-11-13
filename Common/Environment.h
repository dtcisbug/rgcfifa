#ifndef Foundation_Environment_INCLUDED
#define Foundation_Environment_INCLUDED


#include "Platform.h"



class  Environment
	/// This class provides access to environment variables
	/// and some general system information.
{
public:
	typedef UInt8 NodeId[6]; /// Ethernet address.

	static std::string get(const std::string& name);
		/// Returns the value of the environment variable
		/// with the given name. Throws a NotFoundException
		/// if the variable does not exist.

	static std::string get(const std::string& name, const std::string& defaultValue);
		/// Returns the value of the environment variable
		/// with the given name. If the environment variable
		/// is undefined, returns defaultValue instead.

	static bool has(const std::string& name);
		/// Returns true iff an environment variable
		/// with the given name is defined.

	static void set(const std::string& name, const std::string& value);
		/// Sets the environment variable with the given name
		/// to the given value.

	static std::string osName();
		/// Returns the operating system name.

	static std::string osVersion();
		/// Returns the operating system version.

	static std::string osArchitecture();
		/// Returns the operating system architecture.

	static std::string nodeName();
		/// Returns the node (or host) name.

	static void nodeId(NodeId& id);
		/// Returns the Ethernet address of the first Ethernet
		/// adapter found on the system.
		///
		/// Throws a SystemException if no Ethernet adapter is available.

	static std::string nodeId();
		/// Returns the Ethernet address (format "xx:xx:xx:xx:xx:xx")
		/// of the first Ethernet adapter found on the system.
		///
		/// Throws a SystemException if no Ethernet adapter is available.

	static unsigned processorCount();
		/// Returns the number of processors installed in the system.
		///
		/// If the number of processors cannot be determined, returns 1.
};



#endif // Foundation_Environment_INCLUDED
