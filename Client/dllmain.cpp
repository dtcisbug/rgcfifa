// 导出函数
#include "Client.h"
#include "Network/TcpServerWrapper.h"
#include "GlobalObject.h"
#include <stdint.h>

extern"C" _declspec(dllexport) void init_Client();
void init_Client()
{
	GLOBAL().Init();
    CLIENT().Init();
	//CLIENT_NETWORK()->AddConnectServer(65281, "172.104.81.33", 8100);
	for (size_t i = 1; i <= 0xFF; i++)
	{
		CLIENT_NETWORK()->AddConnectServer(0xFF00 + i, "27.109.126.143", 8100);
		//CLIENT_NETWORK()->AddConnectServer(65281+i, "127.0.0.1", 8100);
	}
	//CLIENT_NETWORK()->AddConnectServer(0xFF00 + 1, "27.109.126.143", 8100);
	//CLIENT_NETWORK()->AddConnectServer(0xFF00 + 2, "27.109.126.143", 8100);
    CLIENT().Run();
}

extern"C" _declspec(dllexport) void uninit_Client();
void uninit_Client()
{
	GLOBAL().UnInit(); //放在最后处理
}

extern"C" _declspec(dllexport) void sendMsg(int sessionID,int cmdid, char* buffer, uint16_t size);
void sendMsg(int sessionID,int cmdid, char* buffer,uint16_t size)
{
	
	Stream st(static_cast<UInt16>(cmdid),
		            (static_cast<UInt16>(1) << 8) + static_cast<UInt16>(1), // target 
		            (static_cast<UInt16>(0xFF) << 8) + static_cast<UInt16>(1) // source
		);
	//st << buffer;
	st << size;
	st.append((uint8_t*)buffer, size);
	st << Stream::eos;

    CLIENT_NETWORK()->SendMsgToClient(sessionID,&st[0], st.size());
}

extern"C" _declspec(dllexport) int getLoginSession();
int getLoginSession()
{
	return CLIENT_NETWORK()->GetLoginSession();
}

typedef void(__stdcall * ProgressCallback)(short msg_id, const char* msgbody);
extern"C" _declspec(dllexport) void GetMsg(ProgressCallback cb);
void GetMsg(ProgressCallback cb)
{
	MsgQueue msgQueue;
	if (!GLOBAL().GetMsgQueue(0, msgQueue))
		return;
	MsgHdr* hdr = NULL;
	do
	{
		hdr = msgQueue.Pop();
		printf("have msg type is %d !!!!\n", hdr->msgType);
		switch (hdr->msgType)
		{
		case SERVER_MSGTYPE:
		{
			//char* msgBody = new(std::nothrow) char[hdr->bodyLen];;
			//memcpy(msgBody,(char*)(hdr) + sizeof(ProxyMsgHdr) + 2,hdr->bodyLen-2);
			//printf("msg is %s, msg len is %d !!!!\n", (msgBody), hdr->bodyLen); 
			char* msgBody = (char*)(hdr)+sizeof(ProxyMsgHdr) + 2;
			cb(hdr->cmdID,msgBody);
			//delete[] msgBody;
		}
			break;
		default:
			break;
		}
		//char* msgBody = (char*)((MsgHdr*)hdr + 1);

		GLOBAL().FreeMsgBlock((char *)hdr);
	} while (!msgQueue.Empty());

}

extern"C" _declspec(dllexport) void add_connect(uint16_t uid, std::string ip, uint16_t port);
void add_connect(uint16_t uid,std::string ip,uint16_t port)
{
    CLIENT_NETWORK()->AddConnectServer(uid,ip,port);
}

extern"C" _declspec(dllexport) void close_connect(int id);
void close_connect(int id)
{
    CLIENT_NETWORK()->Close(id);
}

extern"C" _declspec(dllexport) bool get_connect_status(int id);
bool get_connect_status(int id)
{
	return CLIENT_NETWORK()->GetConnStatus(id);
}


