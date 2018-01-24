#ifndef _SERVERTYPES_H_
#define _SERVERTYPES_H_

struct ServerInfor
{
	std::string m_Ip;		//服务器绑定的IP
	UInt16		m_Port;		//服务器监听的端口
	std::string m_DBIp;
	UInt16		m_DBPort;
	//some other ...
};

enum
{
	WORKER_THREAD_LOGIC = 0,	
	MAX_THREAD_NUM
};


#define COUNTRY_EMEI WORKER_THREAD_COUNTRY_1
#define COUNTRY_NEUTRAL WORKER_THREAD_NEUTRAL

#endif // _SERVERTYPES_H_
