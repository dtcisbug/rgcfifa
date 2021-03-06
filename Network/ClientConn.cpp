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

ClientConn::ClientConn( int fd_, Network::TcpSlaveServer * s, int id_, int ss,ServerCommonConfig& cfg) : 
	TcpConduit(fd_, s, id_), _ss(ss), _server_cfg(cfg) 
{
}

bool ClientConn::enabled()
{
	return 8888 > 0;
}

void ClientConn::initConnection()
{
	struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(ResolveAddress(_server_cfg.GetIpFromConnectMap(_ss).c_str()));
	addr.sin_port = htons(_server_cfg.GetPortFromConnectMap(_ss));
    int n = bufferevent_socket_connect(_bev, (struct sockaddr *)&addr, sizeof(addr));
	if(n < 0)
		throw std::bad_exception();
    // connect reg msg
	Stream st(static_cast<UInt32>(0x1),
            (static_cast<UInt16>(_ss) << 8) + (static_cast<UInt16>(_ss) & 0xFF),
            (static_cast<UInt16>(_server_cfg.m_ServerType) << 8) + static_cast<UInt16>(_server_cfg.m_ServerUID)
            );
    st << "register_protocol!";
    st << Stream::eos;
	send(&st[0], st.size());
}

// server packet header 10bytes(len2 + cmd_id4 + target2 + source2)
int ClientConn::parsePacket( struct evbuffer * buf, int &off, int &len, int& target, int& source)
{
	size_t l = evbuffer_get_length(buf);
	if(l < 10)
	{
		off = 0;
		len = 0;
		return 0;
	}
	UInt8 * buf_ = static_cast<UInt8 *>(evbuffer_pullup(buf, 8));
	UInt32 len2 = *reinterpret_cast<UInt16 *>(buf_);
	if(len2 + 10 > l)
	{
		off = 0;
		len = 0;
		return 0;
	}

	off = 10;
	len = len2 + 10;

    target = ((static_cast<UInt16>(buf_[6]))<<8) + static_cast<UInt16>(buf_[7]);
    source = ((static_cast<UInt16>(buf_[8]))<<8) + static_cast<UInt16>(buf_[9]);

    //cmdid 4byte idx 2,3,4,5
    return ((static_cast<UInt32>(buf_[2]))<<24) + ((static_cast<UInt32>(buf_[3]))<<16) + (static_cast<UInt32>(buf_[4]) << 8) + static_cast<UInt32>(buf_[5]);
	return 0;
}

void ClientConn::onRecv(int cmd, int len, void * buf,int target, int source)
{
	ProxyMsgHdr hdr( cmd, SERVER_MSGTYPE,len,id(),target,source);
	//printf("mssssssssssssssssssssssssssssssssg is %c !!!!\n", (char*)((char*)buf));
	GLOBAL().PushMsg( hdr, buf );
}

void ClientConn::onDisconnected()
{
	_host->lostConnection(_ss);
}

}
