#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Platform.h"

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#define atoll(STR) _atoi64(STR)
#define strtoll(STR, END, BASE) _strtoi64(STR, END, BASE)

typedef _int32 int32_t;

#define __PRETTY_FUNCTION__ __FUNCSIG__
#define __func__ __FUNCTION__

#endif

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <queue>
#include <set>
#include <list>
#include <memory>
#include <algorithm>
#include <functional>

#undef __STRICT_ANSI__
#include <cstring>
#define __STRICT_ANSI__

#if defined(_MSC_VER)
#define I64_FMT "I64"
#if _MSC_VER < 1600
namespace std
{
	using namespace std::tr1;
}
#define unique_ptr auto_ptr
#endif
#elif defined(__APPLE__)
#define I64_FMT "q"
#else
#if defined(__LP64__)
#define I64_FMT "l"
#else
#define I64_FMT "ll"
#endif
#endif

#if defined(_MSC_VER)
#define ATTR_PACKED()
#else
#define ATTR_PACKED() __attribute__((packed))
#endif

#if defined (_WIN32)

#define snprintf				           _snprintf
#define vsnprintf                          _vsnprintf

#include <io.h>

#else

#include <unistd.h>

#endif

#define SAFE_DELETE(obj) do { delete(obj); obj = NULL; } while(0)
#define NO_ATTAINMENT
#endif // _CONFIG_H_
