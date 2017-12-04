#include "Common/Config.h"
#include "Log.h"

#include <stdarg.h>
#include "Common/File.h"

#ifdef _WIN32
#ifdef _MSC_VER
#define localtime_r(t,m)                   localtime_s(m,t)
#else
#define localtime_r(t,m)                   *m = *localtime(t)
#endif
#endif

Log::Log( UInt8 lev, const std::string& dir ) : m_LogLev(lev), m_LogDir(dir), m_ErrorFile(NULL), m_WarnFile(NULL), m_DebugFile(NULL),
                                                m_InfoFile(NULL), m_TraceFile(NULL)
{
	time_t t = time(NULL);
	for(int i = 0; i < 16; ++ i)
		localtime_r(&t, &m_aTm[i]);
	File rfile(dir);
	rfile.createDirectories();
}

Log::~Log()
{
	if (m_ErrorFile != NULL)
		fclose(m_ErrorFile);
	if (m_WarnFile != NULL)
		fclose(m_WarnFile);
	if (m_DebugFile != NULL)
		fclose(m_DebugFile);
	if (m_InfoFile != NULL)
		fclose(m_InfoFile);
	if (m_TraceFile != NULL)
		fclose(m_TraceFile);
}

void Log::OutError(const char * fmt, ...)
{
	time_t	t = time(NULL);
	tm aTm;
	localtime_r(&t, &aTm);
	FILE* file = GetFileHandler(APP_ERROR, aTm);
	if (file == NULL)
	{
		return ;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] : ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	va_list ap;
	va_start(ap, fmt);
	fputs(buffer, file);
	vfprintf(file, fmt, ap);
	va_end(ap);
	fflush(file);
}

void Log::OutWarn(const char * fmt, ...)
{
	time_t	t = time(NULL);
	tm aTm;
	localtime_r(&t, &aTm);
	FILE* file = GetFileHandler(APP_WARN, aTm);
	if (file == NULL)
	{
		return ;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] : ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	fputs(buffer, file);
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	va_end(ap);
	fflush(file);
}

void Log::OutDebug(const char * fmt, ...)
{
	time_t	t = time(NULL);
	tm aTm;
	localtime_r(&t, &aTm);
	FILE* file = GetFileHandler(APP_DEBUG, aTm);
	if (file == NULL)
	{
		return ;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] : ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	fputs(buffer, file);
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	va_end(ap);
	fflush(file);
}

void Log::OutInfo(const char * fmt, ...)
{
	time_t	t = time(NULL);
	tm aTm;
	localtime_r(&t, &aTm);
	FILE* file = GetFileHandler(APP_INFO, aTm);
	if (file == NULL)
	{
		return ;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] : ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	fputs(buffer, file);
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	va_end(ap);
	fflush(file);
}

void Log::OutTrace(const char * fmt, ...)
{
	time_t	t = time(NULL);
	tm aTm;
	localtime_r(&t, &aTm);
	FILE* file = GetFileHandler(APP_TRACE, aTm);
	if (file == NULL)
	{
		return ;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] : ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	fputs(buffer, file);
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	va_end(ap);
	fflush(file);
}

void Log::OutLog(UInt8 lev, const char * fmt, ...)
{
	time_t	t = time(NULL);
	tm aTm;
	localtime_r(&t, &aTm);
	FILE* file = GetFileHandler(lev, aTm);

	if (file == NULL)
	{
		return ;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] : ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	fputs(buffer, file);
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	va_end(ap);
	fflush(file);
}


//buffer, terminated with '\0' !
void Log::FlushLog(UInt8 lev, tm& aTm, const char* buffer)
{
	//Only called by log thread
	FILE* file = GetFileHandler(lev, aTm);

	if (file == NULL)
	{
		return ;
	}

	//char tmp[32];
	//tm*	 aTm = localtime(&time);
	//snprintf(tmp, sizeof(tmp), "[%02d:%02d:%02d]", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
	fprintf(file, "%s", buffer);
	fflush(file);
}

FILE* Log::GetFileHandler(UInt8 lev, tm& aTm)
{
	if (lev < APP_ERROR || lev > APP_TRACE)
	{
		return NULL;
	}

	FILE** fileHandler[APP_TRACE + 1] = { NULL, &m_ErrorFile, &m_WarnFile, &m_DebugFile, &m_InfoFile, &m_TraceFile };

	if (aTm.tm_mday != m_aTm[lev].tm_mday || aTm.tm_mon != m_aTm[lev].tm_mon || aTm.tm_year != m_aTm[lev].tm_year || *fileHandler[lev] == NULL)
	{
		if(*fileHandler[lev] != NULL)
		{
			fclose(*fileHandler[lev]);
			*fileHandler[lev] = NULL;
		}

		char buffer[32];
		m_aTm[lev] = aTm;
		snprintf(buffer, sizeof(buffer), "%04d%02d%02d", aTm.tm_year+1900, aTm.tm_mon+1, aTm.tm_mday);

		static const std::string PreName[APP_TRACE + 1] = { "", "ERROR", "WARN", "DEBUG", "INFO", "TRACE"};
		std::string fileName = m_LogDir + PreName[lev] + buffer;

		*fileHandler[lev] = fopen( fileName.c_str(), "a+" );
	}

	return *fileHandler[lev];
}
