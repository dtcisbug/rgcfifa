#include "./GameClient.h"

//#include "./Server/WorldServer.h"
//#include "./MsgHandler/MsgTypes.h"
#include "./Server/GlobalObject.h"
//#include "./Server/Cfg.h"
//#include "./MsgID.h"
#include <event2/buffer.h>
//#include "./MsgHandler/JsonParser.h"
//#include "MsgHandler/GMHandler.h"

namespace Network
{

GameClient::GameClient( int fd, Network::TcpSlaveServer * s, int id ):
	TcpConduit(fd, s, id), _chk(0xff), m_Chk(0xff), m_OldChk(0xff)
{
	struct sockaddr_in peerAddr;
	getAddr(&peerAddr);
	m_RemoteIP = ntohl(peerAddr.sin_addr.s_addr);
	m_RemotePort = ntohs(peerAddr.sin_port);
    setChk(0xff);

    m_Now = (UInt32)time(NULL);
    m_CreateTime = m_RecvTime = m_Now;
    srand(m_Now);

    m_Status = UNVERIFIED;
}

void GameClient::setChk(UInt8 chk)
{
    m_OldChk = m_Chk;
    m_Chk = chk;
    //m_ChkOver = time(NULL) + 10*60;
    m_ChkOver = time(NULL) + 2*60;
}

int GameClient::parsePacket( struct evbuffer * buf, int &off, int &len )
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
    //_chk = buf_[2];

	switch(buf_[2])
	{
	default:
		return ((static_cast<UInt16>(buf_[2]))<<8)+static_cast<UInt16>(buf_[3]);
	}
	return 0;
}

void GameClient::onRecv( int cmd, int len, void * buf )
{
    ClientMsgHdr hdr( cmd,0, len ,id());
    GLOBAL().PushMsg( hdr,  buf );
}

void GameClient::onDisconnected()
{
	
}

bool GameClient::active()
{
}

void GameClient::OnTick(UInt32 now)
{
    TcpConduit::OnTick(now);

    m_Now = now;

    if(m_Status == UNVERIFIED)
    {
        if(m_Now > m_CreateTime + VERIFY_TIMEOUT)
        {
            //验证超时
            //closeConn(); 暂时屏蔽
            return;
        }
    }
    else if(m_Now > m_RecvTime + HEARTBEAT_TIMEOUT)
    {
        //心跳超时
        //closeConn(); 暂时屏蔽
        return;
    }
}

void GameClient::SetClientAddr( const struct sockaddr * addr )
{
	const struct sockaddr_in * peerAddr = reinterpret_cast<const struct sockaddr_in *>(addr);
	m_RemoteIP = ntohl(peerAddr->sin_addr.s_addr);
	m_RemotePort = ntohs(peerAddr->sin_port);
}

}
