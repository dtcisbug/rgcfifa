#ifndef COMPAT_INC
#define COMPAT_INC

#ifndef _WIN32
inline char* strlwr( char* str )
{
	char* orig = str;
	for ( ; *str != '\0'; str++ )
		*str = tolower(*str);
	return orig;
}
#endif

#endif
