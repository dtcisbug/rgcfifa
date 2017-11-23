#include "Common/Config.h"
#include "Script.h"
#include "Server/Cfg.h"

namespace Script
{

Script::Script()
{
	_L = lua_open();
	luaL_openlibs(_L);
	addPackagePath();
}

Script::~Script()
{
    lua_close(_L);
}

void Script::doFile(const char * fn)
{
	init();
	lua_tinker::dofile(_L, fn);
	_scriptName = fn;
	postInit();
}

void Script::runScript(const char * str)
{
	init();
	lua_tinker::dostring(_L, str);
	postInit();
}

Table Script::getTable()
{
	return Table(_L);
}

Table Script::getTable( int index )
{
	return Table(_L, index);
}

Table Script::getTable( const char * name )
{
	return Table(_L, name);
}

void Script::reload()
{
	lua_close(_L);
	_L = lua_open();
	luaL_openlibs(_L);
	addPackagePath();

	init();
	lua_tinker::dofile(_L, _scriptName.c_str());
	postInit();
}

void Script::addPackagePath()
{
	if(!cfg.scriptPath.empty())
	{
		lua_tinker::table pkg = lua_tinker::get<lua_tinker::table>(_L, "package");
		const char * path = pkg.get<const char *>("path");
		std::string newpath = path;
		newpath = newpath + ";" + cfg.scriptPath + "?.lua" + ";" + cfg.scriptPath + "?/init.lua";
		pkg.set("path", newpath.c_str());
	}
}

}
