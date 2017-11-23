#ifndef _GAMECLIENT_H_
#define _GAMECLIENT_H_

#include "Common/AtomicVal.h"
#include "TcpConduit.h"

namespace Network
{

class GameClient:
	public TcpConduit
{
    const static UInt32 VERIFY_TIMEOUT = 120;  //2分钟验证超时
    const static UInt32 HEARTBEAT_TIMEOUT = 180; //3分钟心跳超时

public:
    enum GameClientStatus
    {
        UNVERIFIED,  //未验证
        NORMAL,      //一般状态
    };

public:
	GameClient(int fd, Network::TcpSlaveServer * s, int id);

protected:
	virtual int	parsePacket(struct evbuffer * buf, int &off, int &len);
	virtual void onRecv(int cmd, int len, void * buf);

	virtual void onDisconnected();

public:
	inline UInt32	GetClientIP() const { return m_RemoteIP; }
	inline UInt16	GetClientPort() const { return m_RemotePort; }

	void SetClientAddr(const struct sockaddr *);

    void setChk(UInt8);

	virtual bool active();

    void OnTick(UInt32 now);

    GameClientStatus GetStatus() const { return m_Status; }
    void SetStatus(GameClientStatus status){ m_Status = status; }

private:
	UInt32	m_RemoteIP;
	UInt16	m_RemotePort;
    UInt8 _chk;
    UInt8 m_Chk;
    UInt8 m_OldChk;
    UInt32 m_ChkOver;

    UInt32 m_Now;     //当前时间
    GameClientStatus m_Status; //当前状态

    UInt32 m_CreateTime;  //连接建立时间
    UInt32 m_RecvTime;    //上次收到消息包时间
};

}

#endif // _GAMECLIENT_H_
