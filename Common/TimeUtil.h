#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

#include "Platform.h"
#ifndef _WIN32
#include <sys/time.h>
#else
#include <Winbase.h>
#include <time.h>
#define localtime_r(t, tm) localtime_s(tm, t)
#endif

class TimeUtil
{
    public:
        static UInt32 _timeAdd;
public:
	static inline void Init() { tzset(); }
    static void TimeAdd(UInt32 timeAdd){ _timeAdd = timeAdd;}

    static inline UInt32 MkTime(UInt32 y, UInt32 m, UInt32 d, UInt32 hh = 0, UInt32 mm = 0, UInt32 ss = 0)
    {
        struct tm t_tm;
        if (y < 1900)
            t_tm.tm_year = 0;
        else
            t_tm.tm_year = y - 1900;
        if (m % 13)
            t_tm.tm_mon = m % 13 - 1;
        else
            t_tm.tm_mon = 0;
        if (d % 32)
            t_tm.tm_mday = d % 32;
        else
            t_tm.tm_mday = 1;
        if (hh % 25)
            t_tm.tm_hour = hh % 24 - 1;
        else
            t_tm.tm_hour = 0;
        if (mm % 61)
            t_tm.tm_min = mm % 61 - 1;
        else
            t_tm.tm_min = 0;
        if (ss % 61)
            t_tm.tm_sec = ss % 61 - 1;
        else
            t_tm.tm_sec = 0;

        time_t t2 = mktime(&t_tm);
        return t2;
    }

	static inline UInt32 Now() { return static_cast<UInt32>(time(NULL)) + _timeAdd; }
	static inline UInt8 Day(UInt32 now = Now())
	{
		time_t now2 = static_cast<time_t>(now);
		struct tm local;
        localtime_r(&now2,&local);
		return static_cast<UInt8>(local.tm_wday);
	}
	static inline UInt8 MonthDay(UInt32 now = Now())
	{
		time_t now2 = static_cast<time_t>(now);
		struct tm local;
        localtime_r(&now2,&local);
		return static_cast<UInt8>(local.tm_mday);
	}
    static inline UInt8 Month(UInt32 now = Now())
    {
		time_t now2 = static_cast<time_t>(now);
		struct tm local;
        localtime_r(&now2,&local);
		return static_cast<UInt8>(local.tm_mon + 1);
    }

	static inline UInt32 SharpDayT(int c = 0, UInt32 cur = Now())
    {
        time_t t = cur;
        struct tm t_tm;
        localtime_r(&t,&t_tm);
        t_tm.tm_hour = 0;
        t_tm.tm_min = 0;
        t_tm.tm_sec = 0;
        time_t t2 = mktime(&t_tm);
		return t2 + c * 24 * 60 * 60;
    }
    static inline bool SameDay(UInt32 a, UInt32 b)
    {
        time_t t1 = a;
        time_t t2 = b;
        struct tm t_tm1, t_tm2;
        localtime_r(&t1,&t_tm1);
        localtime_r(&t2,&t_tm2);
        return t_tm1.tm_yday == t_tm2.tm_yday;
    }
    static inline int GetYYMMDD(UInt32 now = Now())
    {
        struct tm t_tm;
        time_t _now = now;
        localtime_r(&_now,&t_tm);
        char _today[32] = {0};
        snprintf(_today, 32, "%d%d%d", t_tm.tm_year+1900, t_tm.tm_mon+1, t_tm.tm_mday);
        return atoi(_today);
    }
    static inline UInt32 SharpWeek(int c = 0, UInt32 cur = Now())
    {
        time_t t = cur;
        struct tm t_tm;
        localtime_r(&t,&t_tm);
        if(t_tm.tm_wday == 0) t_tm.tm_wday = 7;
        t = t + (7 * c + 1 - t_tm.tm_wday) * 86400;
        return SharpDayT(0,t);
    }
    static inline UInt32 GetWeekDay(UInt32 time)
    {
        time_t t = time;
        struct tm t_tm;
        localtime_r(&t,&t_tm);
        if(t_tm.tm_wday == 0) t_tm.tm_wday = 7;
        return t_tm.tm_wday;
    }
    static inline UInt32 SharpMonth(int c = 0, UInt32 cur = Now())
    {
        time_t t = cur;
        struct tm t_tm;
        localtime_r(&t,&t_tm);
        t_tm.tm_mon = t_tm.tm_mon + c;
        t_tm.tm_year = t_tm.tm_year + t_tm.tm_mon / 12;
        t_tm.tm_mon = t_tm.tm_mon % 12;
        t_tm.tm_mday = 1;
        t_tm.tm_hour = 0;
        t_tm.tm_min = 0;
        t_tm.tm_sec = 0;
        return  mktime(&t_tm);
    }
    static inline UInt32 SharpYear(int c = 0, UInt32 cur = Now())
    {
        time_t t = cur;
        struct tm t_tm;
        localtime_r(&t,&t_tm);
        t_tm.tm_year = t_tm.tm_year + c;
        t_tm.tm_mon = 0;
        t_tm.tm_mday = 1;
        t_tm.tm_hour = 0;
        t_tm.tm_min = 0;
        t_tm.tm_sec = 0;
        return mktime(&t_tm);
    }
	static inline UInt32 SharpDay(int c = 0, UInt32 cur = Now())
	{
		UInt32 tmptm = (cur + timezone) / 86400 * 86400 + timezone;
        if(tmptm > cur)
			tmptm -= 86400;
		else if(tmptm + 86400 <= cur)
			tmptm += 86400;
		return tmptm + c * 86400;
	}
	static inline UInt32 SharpHour(int c, UInt32 tm = Now())
	{
		return (tm + c * 3600) / 3600 * 3600;
	}
	static inline UInt32 SharpFourtyMin(int c, UInt32 tm = Now())
	{
		return (tm + c * 2400) / 2400 * 2400;
	}
	static inline UInt32 SharpMinute(int c, UInt32 tm = Now())
	{
		return (tm + c * 60) / 60 * 60;
	}
	static inline UInt64 GetTick()
	{
#ifdef _WIN32
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
		epoch.LowPart  = 0xD53E8000;
		epoch.HighPart = 0x019DB1DE;

		ULARGE_INTEGER ts;
		ts.LowPart  = ft.dwLowDateTime;
		ts.HighPart = ft.dwHighDateTime;
		ts.QuadPart -= epoch.QuadPart;
		return ts.QuadPart / 10;
#else
		struct timeval tv;
		if(gettimeofday(&tv, NULL))
			return 0;
		return tv.tv_sec * 1000000 + tv.tv_usec;
#endif
	}
    static inline void GetDMY(UInt32* pDay = NULL, UInt32* pM = NULL, UInt32* pY = NULL)
    {
        time_t now = static_cast<time_t>( Now());
        struct tm local;
        localtime_r(&now,&local);
        if(pDay)
            *pDay = local.tm_mday;
        if(pM)
            *pM = local.tm_mon + 1;
        if(pY)
            *pY = local.tm_year + 1900;
    }
    static inline void GetNextMY(UInt32& m, UInt32* pY)
    {
        if(m>=1 && m<12)
        {
            ++m;
        }
        else
        {
            m = 1;
            if(pY)
               ++ (*pY) ;
        }
    }
    static inline UInt8 GetOneMonthDays(UInt32 nowTime = Now())
    {
        time_t now = static_cast<time_t>(nowTime);
        struct tm local;
        localtime_r(&now,&local);
        UInt32 mon = local.tm_mon + 1;
        UInt32 year = local.tm_year + 1900;
        bool leapYear = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? true : false;
        switch(mon)
        {
            case 2:
                if(leapYear)
                    return 29;
                return 28;
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return 31;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            default:
                return 30;
                break;
        }
    }
};


#endif // _TIMEUTIL_H_
