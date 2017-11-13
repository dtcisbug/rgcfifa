#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define _THREAD_STACK_SIZE 0

#define _OS_FREE_BSD      0x0001
#define _OS_LINUX         0x0005
#define _OS_MAC_OS_X      0x0006
#define _OS_NET_BSD       0x0007
#define _OS_OPEN_BSD      0x0008
#define _OS_CYGWIN        0x000d
#define _OS_UNKNOWN_UNIX  0x00ff
#define _OS_WINDOWS_NT    0x1001


#if defined(__FreeBSD__)
	#define _OS_FAMILY_UNIX 1
	#define _OS_FAMILY_BSD 1
	#define _OS _OS_FREE_BSD
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
	#define _OS_FAMILY_UNIX 1
	#define _OS _OS_LINUX
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
	#define _OS_FAMILY_UNIX 1
	#define _OS_FAMILY_BSD 1
	#define _OS _OS_MAC_OS_X
#elif defined(__NetBSD__)
	#define _OS_FAMILY_UNIX 1
	#define _OS_FAMILY_BSD 1
	#define _OS _OS_NET_BSD
#elif defined(__OpenBSD__)
	#define _OS_FAMILY_UNIX 1
	#define _OS_FAMILY_BSD 1
	#define _OS _OS_OPEN_BSD
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define _OS_FAMILY_UNIX 1
	#define _OS _OS_UNKNOWN_UNIX
#elif defined(_WIN32) || defined(_WIN64)
	#define _OS_FAMILY_WINDOWS 1
	#define _OS _OS_WINDOWS_NT
#elif defined(__CYGWIN__)
	#define _OS_FAMILY_UNIX 1
	#define _OS _OS_CYGWIN
#endif


//
// Hardware Architecture and Byte Order
//
#define _ARCH_ALPHA   0x01
#define _ARCH_IA32    0x02
#define _ARCH_IA64    0x03
#define _ARCH_MIPS    0x04
#define _ARCH_HPPA    0x05
#define _ARCH_PPC     0x06
#define _ARCH_POWER   0x07
#define _ARCH_SPARC   0x08
#define _ARCH_AMD64   0x09
#define _ARCH_ARM     0x0a
#define _ARCH_M68K    0x0b
#define _ARCH_S390    0x0c
#define _ARCH_SH      0x0d


#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
	#define _ARCH _ARCH_ALPHA
	#define _ARCH_LITTLE_ENDIAN 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
	#define _ARCH _ARCH_IA32
	#define _ARCH_LITTLE_ENDIAN 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define _ARCH _ARCH_IA64
	#if defined(hpux) || defined(_hpux)
		#define _ARCH_BIG_ENDIAN 1
	#else
		#define _ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__x86_64__) || defined(_M_X64)
	#define _ARCH _ARCH_AMD64
	#define _ARCH_LITTLE_ENDIAN 1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
	#define _ARCH _ARCH_MIPS
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__hppa) || defined(__hppa__)
	#define _ARCH _ARCH_HPPA
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
      defined(__powerpc__) || defined(__ppc__) || defined(__ppc) || defined(_ARCH_PPC) || defined(_M_PPC)
	#define _ARCH _ARCH_PPC
	#define _ARCH_BIG_ENDIAN 1
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4) || defined(__THW_RS6000)
	#define _ARCH _ARCH_POWER
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
	#define _ARCH _ARCH_SPARC
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
	#define _ARCH _ARCH_ARM
	#if defined(__ARMEB__)
		#define _ARCH_BIG_ENDIAN 1
	#else
		#define _ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__m68k__)
	#define _ARCH _ARCH_M68K
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__s390__)
	#define _ARCH _ARCH_S390
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__sh__) || defined(__sh)
	#define _ARCH _ARCH_SH
	#if defined(__LITTLE_ENDIAN__)
		#define _ARCH_LITTLE_ENDIAN 1
	#else
		#define _ARCH_BIG_ENDIAN 1
	#endif
#endif

#if defined(_WIN32)

#if defined(_MSC_VER) && !defined(_MT)
	#error Must compile with /MD, /MDd, /MT or /MTd
#endif


// Check debug/release settings consistency
#if defined(NDEBUG) && defined(_DEBUG)
	#error Inconsistent build settings (check for /MD[d])
#endif


// Reduce bloat imported by "/UnWindows.h"
#if defined(_WIN32)
	#if !defined(_WIN32_WINNT)
		#define _WIN32_WINNT 0x0500
	#endif
	#if !defined(WIN32_LEAN_AND_MEAN) && !defined(_BLOATED_WIN32)
		#define WIN32_LEAN_AND_MEAN
	#endif
#endif


// Turn off some annoying warnings
#if defined(_MSC_VER)
	#pragma warning(disable:4018) // signed/unsigned comparison
	#pragma warning(disable:4251) // ... needs to have dll-interface warning
	#pragma warning(disable:4355) // 'this' : used in base member initializer list
	#pragma warning(disable:4996) // VC++ 8.0 deprecation warnings
	#pragma warning(disable:4351) // new behavior: elements of array '...' will be default initialized
	#pragma warning(disable:4675) // resolved overload was found by argument-dependent lookup
	#pragma warning(disable:4275) // non dll-interface class 'std::exception' used as base for dll-interface class '::Exception'
#endif


#if defined(__INTEL_COMPILER)
	#pragma warning(disable:1738) // base class dllexport/dllimport specification differs from that of the derived class
	#pragma warning(disable:1478) // function ... was declared "deprecated"
	#pragma warning(disable:1744) // field of class type without a DLL interface used in a class with a DLL interface
#endif

#endif

#define COMMON_JOIN(X, Y) COMMON_DO_JOIN(X, Y)
#define COMMON_DO_JOIN(X, Y) COMMON_DO_JOIN2(X, Y)
#define COMMON_DO_JOIN2(X, Y) X##Y

#include "Bugcheck.h"

#if defined(_MSC_VER)
	//
	// Windows/Visual C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed __int64         Int64;
	typedef unsigned __int64       UInt64;
	#if defined(_WIN64)
		#define _PTR_IS_64_BIT 1
		typedef signed __int64     IntPtr;
		typedef unsigned __int64   UIntPtr;
	#else
		typedef signed long        IntPtr;
		typedef unsigned long      UIntPtr;
	#endif
	#define _HAVE_INT64 1
#elif defined(__GNUC__) || defined(__clang__)
	//
	// Unix/GCC
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if defined(__LP64__)
		#define _PTR_IS_64_BIT 1
		#define _LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define _HAVE_INT64 1
#elif defined(__DECCXX)
	//
	// Compaq C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed __int64         Int64;
	typedef unsigned __int64       UInt64;
	#if defined(__VMS)
		#if defined(__32BITS)
			typedef signed long    IntPtr;
			typedef unsigned long  UIntPtr;
		#else
			typedef Int64          IntPtr;
			typedef UInt64         UIntPtr;
			#define _PTR_IS_64_BIT 1
		#endif
	#else
		typedef signed long        IntPtr;
		typedef unsigned long      UIntPtr;
		#define _PTR_IS_64_BIT 1
		#define _LONG_IS_64_BIT 1
	#endif
	#define _HAVE_INT64 1
#elif defined(__IBMCPP__)
	//
	// IBM XL C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if defined(__64BIT__)
		#define _PTR_IS_64_BIT 1
		#define _LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define _HAVE_INT64 1
#endif

#include <string.h>

#ifdef _WIN32

#undef GetBinaryType
#undef GetShortPathName
#undef GetLongPathName
#undef GetEnvironmentStrings
#undef SetEnvironmentStrings
#undef FreeEnvironmentStrings
#undef FormatMessage
#undef EncryptFile
#undef DecryptFile
#undef CreateMutex
#undef OpenMutex
#undef CreateEvent
#undef OpenEvent
#undef CreateSemaphore
#undef OpenSemaphore
#undef LoadLibrary
#undef GetModuleFileName
#undef CreateProcess
#undef GetCommandLine
#undef GetEnvironmentVariable
#undef SetEnvironmentVariable
#undef ExpandEnvironmentStrings
#undef OutputDebugString
#undef FindResource
#undef UpdateResource
#undef FindAtom
#undef AddAtom
#undef GetSystemDirector
#undef GetTempPath
#undef GetTempFileName
#undef SetCurrentDirectory
#undef GetCurrentDirectory
#undef CreateDirectory
#undef RemoveDirectory
#undef CreateFile
#undef DeleteFile
#undef SearchPath
#undef CopyFile
#undef MoveFile
#undef ReplaceFile
#undef GetComputerName
#undef SetComputerName
#undef GetUserName
#undef LogonUser
#undef GetVersion
#undef GetObject

#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#endif


#endif // _PLATFORM_H_
