#ifndef MSGPOPHANDLER_INC
#define MSGPOPHANDLER_INC

#include "Server/GlobalObject.h"

//only pop msg out to call c# func
class MsgPopHandler
{
public:
	MsgPopHandler(UInt8 worker = 0) : m_Worker(worker), m_RunnerShutdown(false)
	 {
		 
	 }

	 virtual ~MsgPopHandler()
	 {
	 }

public:
	 void DeregisterAllMsg();

	 bool ProcessMsg();

     inline void setRunnerShutdown(bool v) { m_RunnerShutdown = v; }
     inline bool isRunnerShutdown() const { return m_RunnerShutdown; }

private:
	 UInt8	 m_Worker;
     bool m_RunnerShutdown;
};
#endif 
