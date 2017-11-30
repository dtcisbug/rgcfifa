#ifndef _CLIENTCONN_H_
#define _CLIENTCONN_H_

#include "TcpConduit.h"
#include "Common/ServerCommon.h"

namespace Network
{

class ClientConn:
	public TcpConduit
{
public:
	ClientConn(int fd, Network::TcpSlaveServer * s, int id, int ss, ServerCommonConfig cfg);
	static bool enabled();
    virtual void initConnection();

protected:
	virtual int	parsePacket(struct evbuffer * buf, int &off, int &len,int &target,int& source);
    virtual void onRecv(int cmd, int len, void * buf,int target, int source); 

	virtual void onDisconnected();

public:
	virtual bool active() { return false; }
private:
    int _ss;
    std::string _ip;
    UInt16 _port;
    ServerCommonConfig _server_cfg;
};

}

#endif // _ARENACONN_H_
