#ifndef Foundation_Bugcheck_INCLUDED
#define Foundation_Bugcheck_INCLUDED


#include "Platform.h"
#include <string>
#if defined(_DEBUG)
#	include <iostream>
#endif


namespace Common {


	class  Bugcheck
		/// This class provides some static methods that are
		/// used by the
		/// common_assert_dbg(), common_assert(), common_check_ptr()
		/// and common_bugcheck() macros.
		/// You should not invoke these methods
		/// directly. Use the macros instead, as they
		/// automatically provide useful context information.
	{
	public:
		static void assertion(const char* cond, const char* file, int line);
		/// An assertion failed. Break into the debugger, if
		/// possible, then throw an AssertionViolationException.

		static void nullPointer(const char* ptr, const char* file, int line);
		/// An null pointer was encountered. Break into the debugger, if
		/// possible, then throw an NullPointerException.

		static void bugcheck(const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible, then throw an BugcheckException.

		static void bugcheck(const char* msg, const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible, then throw an BugcheckException.

		static void debugger(const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible.

		static void debugger(const char* msg, const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible.

	protected:
		static std::string what(const char* msg, const char* file, int line);
	};


}

#if defined(_DEBUG)
#define common_assert_dbg(cond) \
	if (!(cond)) Common::Bugcheck::assertion(#cond, __FILE__, __LINE__); else (void) 0
#else
#define common_assert_dbg(cond)
#endif


#define common_assert(cond) \
	if (!(cond)) Common::Bugcheck::assertion(#cond, __FILE__, __LINE__); else (void) 0


#define common_check_ptr(ptr) \
	if (!(ptr)) Common::Bugcheck::nullPointer(#ptr, __FILE__, __LINE__); else (void) 0


#define common_bugcheck() \
	Common::Bugcheck::bugcheck(__FILE__, __LINE__)


#define common_bugcheck_msg(msg) \
	Common::Bugcheck::bugcheck(msg, __FILE__, __LINE__)


#define common_debugger() \
	Common::Bugcheck::debugger(__FILE__, __LINE__)


#define common_debugger_msg(msg) \
	Common::Bugcheck::debugger(msg, __FILE__, __LINE__)


#if defined(_DEBUG)
#	define common_stdout_dbg(outstr) \
	//COUT << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#	define common_stdout_dbg(outstr)
#endif


#if defined(_DEBUG)
#	define common_stderr_dbg(outstr) \
	std::cerr << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#	define common_stderr_dbg(outstr)
#endif


//
// common_static_assert
//
// The following was ported from <boost/static_assert.hpp>
//


template <bool x>
struct COMMON_STATIC_ASSERTION_FAILURE;


template <>
struct COMMON_STATIC_ASSERTION_FAILURE<true>
{
	enum
	{
		value = 1
	};
};


template <int x>
struct common_static_assert_test
{
};


#if defined(__GNUC__) && (__GNUC__ == 3) && ((__GNUC_MINOR__ == 3) || (__GNUC_MINOR__ == 4))
#define common_static_assert(B) \
	typedef char COMMON_JOIN(common_static_assert_typedef_, __LINE__) \
	[COMMON_STATIC_ASSERTION_FAILURE<(bool) (B)>::value]
#else
#define common_static_assert(B) \
	typedef common_static_assert_test<sizeof(COMMON_STATIC_ASSERTION_FAILURE<(bool) (B)>)> \
	COMMON_JOIN(common_static_assert_typedef_, __LINE__)
#endif


#ifndef assert
#define assert common_assert
#endif

#endif // Foundation_Bugcheck_INCLUDED
