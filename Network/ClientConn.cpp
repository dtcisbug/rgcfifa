#ifdef _WIN32
#define _WSPIAPI_H_
#define _WINSOCKAPI_
#endif

#include "Common/Config.h"
#include "ClientConn.h"
#include "TcpServer.h"
#include "./Server/GlobalObject.h"
#include "Common/Stream.h"

#include <event2/buffer.h>
#include <event2/bufferevent.h>

namespace Network
{

ClientConn::ClientConn( int fd, Network::TcpSlaveServer * s, int id, int ss,ServerCommonConfig cfg) : 
	TcpConduit(fd, s, id) , _ss(ss), _server_cfg(cfg) 
{
}

bool ClientConn::enabled()
{
	return 8888 > 0;
}

void ClientConn::initConnection()
{
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(ResolveAddress(_server_cfg.GetIpFromConnectMap(_ss).c_str()));
	addr.sin_port = htons(_server_cfg.GetPortFromConnectMap(_ss));
    int n = bufferevent_socket_connect(_bev, (struct sockaddr *)&addr, sizeof(addr));
	if(n < 0)
		throw std::bad_exception();
    // connect reg msg
	Stream st(static_cast<UInt16>(0x111),
            (static_cast<UInt16>(1) << 8) + static_cast<UInt16>(1),
            (static_cast<UInt16>(_server_cfg.m_ServerType) << 8) + static_cast<UInt16>(_server_cfg.m_ServerUID)
            );
    st << "asdadsadsdsa";
    st << Stream::eos;
	send(&st[0], st.size());
}

// server packet header 8bytes(len + cmd_id + target + source)
int ClientConn::parsePacket( struct evbuffer * buf, int &off, int &len, int& target, int& source)
{
	size_t l = evbuffer_get_length(buf);
	if(l < 8)
	{
		off = 0;
		len = 0;
		return 0;
	}
	UInt8 * buf_ = static_cast<UInt8 *>(evbuffer_pullup(buf, 8));
	UInt32 len2 = *reinterpret_cast<UInt16 *>(buf_);
	if(len2 + 8 > l)
	{
		off = 0;
		len = 0;
		return 0;
	}

	off = 8;
	len = len2 + 8;

    target = (static_cast<UInt16>(buf_[4]))<<8 + static_cast<UInt16>(buf_[5]);
    source = (static_cast<UInt16>(buf_[6]))<<8 + static_cast<UInt16>(buf_[7]);

	switch(buf_[2])
	{
	default:
		return ((static_cast<UInt16>(buf_[2]))<<8)+static_cast<UInt16>(buf_[3]);
	}
	return 0;
}

void ClientConn::onRecv(int cmd, int len, void * buf,int target, int source)
{
	ProxyMsgHdr hdr( cmd, 1, id(), len ,target,source);
	//printf("mssssssssssssssssssssssssssssssssg is %c !!!!\n", (char*)((char*)buf));
	GLOBAL().PushMsg( hdr, buf );
}

void ClientConn::onDisconnected()
{
	_host->lostConnection(_ss);
}

}
