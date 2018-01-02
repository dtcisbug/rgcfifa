#include "Common/Config.h"
#include "ConfigScript.h"

#include "Server/Cfg.h"

namespace Script
{

ConfigScript::ConfigScript( Cfg * cfg )
{
	class_add<Cfg>("Cfg");
	class_def<Cfg>("setServerType", &Cfg::setServerType);
	class_def<Cfg>("setServerUID", &Cfg::setServerUID);
	class_def<Cfg>("setServerLogName", &Cfg::setServerLogName);
	class_def<Cfg>("setServerDllName", &Cfg::setServerDllName);
	class_def<Cfg>("setTcpPort", &Cfg::setTcpPort);
	class_def<Cfg>("addConnectList", &Cfg::addConnectList);
	class_def<Cfg>("setDatabase", &Cfg::setDatabase);

	class_def<Cfg>("setIfName", &Cfg::setIfName);
	class_def<Cfg>("setScriptPath", &Cfg::setScriptPath);
	class_def<Cfg>("setArenaServer", &Cfg::setArenaServer);
	set("cfg", cfg);
}

}
