#ifndef _CLIENTCONN_H_
#define _CLIENTCONN_H_

#include "TcpConduit.h"

namespace Network
{

class ClientConn:
	public TcpConduit
{
public:
	ClientConn(int fd, Network::TcpSlaveServer * s, int id);
	static bool enabled();
    virtual void initConnection();

protected:
	virtual int	parsePacket(struct evbuffer * buf, int &off, int &len);
	virtual void onRecv(int cmd, int len, void * buf);

	virtual void onDisconnected();

public:
	virtual bool active() { return false; }
};

}

#endif // _ARENACONN_H_
