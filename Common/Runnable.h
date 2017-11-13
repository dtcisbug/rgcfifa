#ifndef Foundation_Runnable_INCLUDED
#define Foundation_Runnable_INCLUDED


#include "Platform.h"


class Runnable
	/// The Runnable interface with the run() method
	/// must be implemented by classes that provide
	/// an entry point for a thread.
{
public:
	Runnable();
	virtual ~Runnable();

	virtual void run() = 0;
		/// Do whatever the thread needs to do. Must
		/// be overridden by subclasses.
};


#endif // Foundation_Runnable_INCLUDED
