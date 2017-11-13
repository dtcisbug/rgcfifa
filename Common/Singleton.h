#ifndef SINGLETON_INC
#define SINGLETON_INC

#include <stdlib.h>


// Singleton object MUST BE initialized manually.
template <typename Type>
class Singleton
{
public:
	static Type& Instance() // Unique point of access
	{
		if (s_Instance == 0)
		{
			s_Instance = new(Type)();
			atexit(Destroy);
		}
		return *s_Instance;
	}
protected:
	Singleton() {}
	virtual ~Singleton() {}
private:
	static void Destroy() // Destroy the only instance
	{
		if (s_Instance != 0)
		{
			delete(s_Instance);
			s_Instance = 0;
		}
	}
	static Type* volatile s_Instance; // The one and oly instance
};

template <typename Type>
Type* volatile Singleton<Type >::s_Instance = 0;


#endif

