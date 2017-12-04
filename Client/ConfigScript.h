#ifndef _CONFIGSCRIPT_H_
#define _CONFIGSCRIPT_H_

#include "script/Script.h"

class Cfg;

namespace Script
{

class ConfigScript:
	public Script
{
public:
	ConfigScript(Cfg * cfg);
};

}

#endif // _CONFIGSCRIPT_H_
