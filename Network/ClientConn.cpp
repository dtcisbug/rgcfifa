#include "Common/Config.h"
#include "ClientConn.h"

#include "TcpServer.h"

//#include "Server/WorldServer.h"
//#include "Server/Cfg.h"
#include "Common/Stream.h"
//#include "MsgID.h"
#include <event2/buffer.h>
#include <event2/bufferevent.h>

namespace Network
{

ClientConn::ClientConn( int fd, Network::TcpSlaveServer * s, int id ) :
	TcpConduit(fd, s, id)
{
}

bool ClientConn::enabled()
{
	return 8888 > 0;
	//return cfg.arenaPort > 0;
}

void ClientConn::initConnection()
{
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(ResolveAddress("127.0.0.1"));
	addr.sin_port = htons(8888);
    int n = bufferevent_socket_connect(_bev, (struct sockaddr *)&addr, sizeof(addr));
	//if(bufferevent_socket_connect(_bev, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	if(n < 0)
		throw std::bad_exception();
	Stream st(0x111, 0xEF);
    st << Stream::eos;
	send(&st[0], st.size());
}

int ClientConn::parsePacket( struct evbuffer * buf, int &off, int &len )
{
	size_t l = evbuffer_get_length(buf);
	if(l < 4)
	{
		off = 0;
		len = 0;
		return 0;
	}
	UInt8 * buf_ = static_cast<UInt8 *>(evbuffer_pullup(buf, 4));
	UInt32 len2 = *reinterpret_cast<UInt16 *>(buf_);
	if(len2 + 4 > l)
	{
		off = 0;
		len = 0;
		return 0;
	}

	off = 4;
	len = len2 + 4;

	switch(buf_[2])
	{
	case 0xEF:
		return 0x100 + buf_[3];
	default:
		return 0;
	}
	return 0;
}

void ClientConn::onRecv( int cmd, int len, void * buf )
{
	//ArenaMsgHdr hdr( cmd, 1, id(), len );
	//GLOBAL().PushMsg( hdr, buf );
}

void ClientConn::onDisconnected()
{
	//ArenaMsgHdr hdr( 0x101, 1, id(), 1 );
	//UInt8 r = 1;
	//GLOBAL().PushMsg( hdr, &r );
	_host->lostConnection(1);
}

}
