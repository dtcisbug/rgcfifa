#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "lua_tinker.h"

typedef lua_tinker::table Table;

namespace Script
{

class Script
{
public:
	Script();
    virtual ~Script();
	virtual void init() {}
	virtual void postInit() {}
	void runScript(const char *);
	void doFile(const char *);
	void reload();

private:
	void addPackagePath();

protected:
	lua_State * _L;
	std::string _scriptName;

public:
	Table getTable();
	Table getTable(int index);
	Table getTable(const char * name);

	template<typename T>
	void set(const char* name, T object);

	template<typename T>
	T get(const char* name);

	template<typename F>
	void def(const char * name, F func);

	template<typename T>
	void decl(const char* name, T object);

	template<typename RVal>
	RVal call(const char* name);
	template<typename RVal, typename T1>
	RVal call(const char* name, T1 arg1);
	template<typename RVal, typename T1, typename T2>
	RVal call(const char* name, T1 arg1, T2 arg2);
	template<typename RVal, typename T1, typename T2, typename T3>
	RVal call(const char* name, T1 arg1, T2 arg2, T3 arg3);
	template<typename RVal, typename T1, typename T2, typename T3, typename T4>
	RVal call(const char* name, T1 arg1, T2 arg2, T3 arg3, T4 arg4);
	template<typename RVal, typename T1, typename T2, typename T3, typename T4, typename T5>
	RVal call(const char* name, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5);
	template<typename RVal, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	RVal call(const char* name, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6);

	template<typename T>
	void class_add(const char * name);

	template<typename T, typename P>
	void class_inh();

	template<typename T, typename F>
	void class_con(F func);

	template<typename T, typename F>
	void class_def(const char * name, F func);

	template<typename T, typename BASE, typename VAR>
	void class_mem(const char* name, VAR BASE::*val);
};

template<typename T>
T Script::get( const char* name )
{
	return lua_tinker::get<T>(_L, name);
}

template<typename T>
void Script::set( const char* name, T object )
{
	lua_tinker::set(_L, name, object);
}

template<typename RVal>
RVal Script::call( const char* name )
{
	return lua_tinker::call<RVal>(_L, name);
}

template<typename RVal, typename T1>
RVal Script::call(const char* name, T1 arg1)
{
	return lua_tinker::call<RVal>(_L, name, arg1);
}

template<typename RVal, typename T1, typename T2>
RVal Script::call(const char* name, T1 arg1, T2 arg2)
{
	return lua_tinker::call<RVal>(_L, name, arg1, arg2);
}

template<typename RVal, typename T1, typename T2, typename T3>
RVal Script::call(const char* name, T1 arg1, T2 arg2, T3 arg3)
{
	return lua_tinker::call<RVal>(_L, name, arg1, arg2, arg3);
}

template<typename RVal, typename T1, typename T2, typename T3, typename T4>
RVal Script::call(const char* name, T1 arg1, T2 arg2, T3 arg3, T4 arg4)
{
	return lua_tinker::call<RVal>(_L, name, arg1, arg2, arg3, arg4);
}

template<typename RVal, typename T1, typename T2, typename T3, typename T4, typename T5>
RVal Script::call(const char* name, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
{
	return lua_tinker::call<RVal>(_L, name, arg1, arg2, arg3, arg4, arg5);
}

template<typename RVal, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
RVal Script::call(const char* name, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
{
	return lua_tinker::call<RVal>(_L, name, arg1, arg2, arg3, arg4, arg5, arg6);
}

template<typename T>
void Script::decl( const char* name, T object )
{
	return lua_tinker::decl(_L, name, object);
}

template<typename F>
void Script::def( const char * name, F func )
{
	lua_tinker::def(_L, name, func);
}

template<typename T, typename F>
void Script::class_def( const char * name, F func )
{
	lua_tinker::class_def<T>(_L, name, func);
}

template<typename T, typename F>
void Script::class_con( F func )
{
	lua_tinker::class_con<T>(_L, func);
}

template<typename T, typename P>
void Script::class_inh()
{
	lua_tinker::class_inh<T, P>(_L);
}

template<typename T>
void Script::class_add( const char * name )
{
	lua_tinker::class_add<T>(_L, name);
}

template<typename T, typename BASE, typename VAR>
void Script::class_mem( const char* name, VAR BASE::*val )
{
	lua_tinker::class_mem<T>(_L, name, val);
}

}

#endif // _SCRIPT_H_
