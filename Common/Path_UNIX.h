#ifndef Foundation_Path_UNIX_INCLUDED
#define Foundation_Path_UNIX_INCLUDED


#include "Platform.h"
#include <vector>



class PathImpl
{
public:
	static std::string currentImpl();
	static std::string homeImpl();
	static std::string tempImpl();
	static std::string nullImpl();
	static std::string expandImpl(const std::string& path);
	static void listRootsImpl(std::vector<std::string>& roots);
};




#endif // Foundation_Path_UNIX_INCLUDED
