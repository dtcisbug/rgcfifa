#include "Common/Config.h"
#include "ConfigScript.h"

#include "Server/Cfg.h"

namespace Script
{

ConfigScript::ConfigScript( Cfg * cfg )
{
	class_add<Cfg>("Cfg");
	class_def<Cfg>("setTcpPort", &Cfg::setTcpPort);
	class_def<Cfg>("setIfName", &Cfg::setIfName);
	class_def<Cfg>("setScriptPath", &Cfg::setScriptPath);
	class_def<Cfg>("setCryptKeys", &Cfg::setCryptKeys);
	class_def<Cfg>("setGMCryptKeys", &Cfg::setGMCryptKeys);
	class_def<Cfg>("setArenaServer", &Cfg::setArenaServer);
	set("cfg", cfg);
}

}
