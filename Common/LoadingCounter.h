#ifndef _LOADINGCOUNTER_H_
#define _LOADINGCOUNTER_H_

#include "TimeUtil.h"

class LoadingCounter
{
public:
	LoadingCounter(const char * title): _clock(0), _count(0) { prepare(title); }
	inline void prepare(const char * title)
	{
		fprintf(stdout, "%s", title);
		fflush(stdout);
	}
	inline void reset(UInt32 step)
	{
		_clock = TimeUtil::GetTick();
		_count = 0;
	}
	inline void advance()
	{
		++ _count;
	}
	inline void finalize()
	{
		UInt64 curclock = TimeUtil::GetTick();
		fprintf(stdout, "    %u records in %.2f secs (%.2f secs in total)\r\n", _count, (float)(curclock - _clock) / 1000000, (float)(curclock - _firstClock) / 1000000);
		_clock = 0;
		_count = 0;
		fflush(stdout);
	}
private:
	static UInt64 _firstClock;
	UInt64 _clock;
	UInt32 _count;
};


#endif // _LOADINGCOUNTER_H_
