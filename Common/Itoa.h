#ifndef _ITOA_H_
#define _ITOA_H_

template <typename Type>
std::string Itoa(Type n, int dec = 10)
{
	char buffer[256] = {0};
	char* p = buffer;

	do
	{
		*p++ = "0123456789"[n % dec];
		n /= dec;
		if (static_cast<size_t>(p - buffer) > sizeof(buffer)) return "";
	} while (n);

	buffer[p - buffer] = 0;

	int i, j;
	for (i = 0, j = (int)strlen(buffer) - 1; i < j; i++, j--)
	{
		buffer[j] = buffer[i] + buffer[j];
		buffer[i] = buffer[j] - buffer[i];
		buffer[j] = buffer[j] - buffer[i];
	}

	return buffer;
}

#endif // _ITOA_H_
