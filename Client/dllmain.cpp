// 导出函数
#include "Client.h"
#include "Network/TcpServerWrapper.h"
#include "GlobalObject.h"

extern"C" _declspec(dllexport) void init_Client();
void init_Client()
{
	GLOBAL().Init();
    CLIENT().Init();
	CLIENT_NETWORK()->AddConnectServer(65281, "172.104.81.33", 8100);
    CLIENT().Run();
}

extern"C" _declspec(dllexport) void uninit_Client();
void uninit_Client()
{
	GLOBAL().UnInit(); //放在最后处理
}

extern"C" _declspec(dllexport) void sendMsg(uint32_t sessionID, char* buffer, uint16_t size);
void sendMsg(uint32_t sessionID,char* buffer,uint16_t size)
{
    CLIENT_NETWORK()->SendMsgToClient(sessionID,buffer,size);
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
		//printf("have msg type is %d !!!!\n", hdr->msgType);
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




