// 导出函数
#include "Client.h"
#include "Network/TcpServerWrapper.h"
#include "GlobalObject.h"
#include <stdint.h>

#   if defined (__GNUC__) && defined(__unix__)
#    define EXPORT_API  
#   elif defined WIN32
#    define EXPORT_API __declspec(dllexport) 
#   endif

//#    define EXPORT_API __attribute__((__stdcall__))

//extern"C" _declspec(dllexport) void init_Client();
extern"C" EXPORT_API void init_Client();
void init_Client()
{
	GLOBAL().Init();
    CLIENT().Init();
	//CLIENT_NETWORK()->AddConnectServer(65281, "172.104.81.33", 8100);
	//CLIENT_NETWORK()->AddConnectServer(65282, "172.104.81.33", 8103);
	CLIENT_NETWORK()->AddConnectServer(65281, "27.109.126.143", 8100);
	CLIENT_NETWORK()->AddConnectServer(65282, "27.109.126.143", 8103);
	
    CLIENT().Run();
    return;
}

extern"C" EXPORT_API void uninit_Client();
void uninit_Client()
{
	GLOBAL().UnInit(); //放在最后处理
}

extern"C" EXPORT_API void sendMsg(int sessionID,int cmdid, char* buffer, uint16_t size);
void sendMsg(int sessionID,int cmdid, char* buffer,uint16_t size)
{
	
	Stream st(static_cast<UInt32>(cmdid),
		            (static_cast<UInt16>(1) << 8) + static_cast<UInt16>(1), // target 
		            (static_cast<UInt16>(0xFF) << 8) + static_cast<UInt16>(1) // source
		);
	//st << buffer;
	st << size;
	st.append((uint8_t*)buffer, size);
	st << Stream::eos;

    CLIENT_NETWORK()->SendMsgToClient(sessionID,&st[0], st.size());
}

extern"C" EXPORT_API int getLoginSession();
int getLoginSession()
{
	return CLIENT_NETWORK()->GetLoginSession();
}

//typedef bool(__stdcall__ * ProgressCallback)(uint32_t session_id ,uint16_t size);
typedef bool(* ProgressCallback)(uint32_t session_id ,uint16_t size);
extern"C" EXPORT_API void GetMsg(char* buffer,ProgressCallback cb);
void GetMsg(char* buffer,ProgressCallback cb)
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
			char length[2]; 
			memcpy(length, (char*)(hdr)+sizeof(ProxyMsgHdr), 2);
			UInt16 packet_len = *((UInt16*)length);
			char* msgBody = (char*)(hdr)+sizeof(ProxyMsgHdr) + 2;

			memcpy(buffer, msgBody, packet_len);

			cb(hdr->sessionID, packet_len);
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

extern"C" EXPORT_API void add_connect(uint16_t uid, char* ip, uint16_t port);
void add_connect(uint16_t uid,char* ip,uint16_t port)
{
    CLIENT_NETWORK()->AddConnectServer(uid, "172.104.81.33",port);
}

extern"C" EXPORT_API void close_connect(int id);
void close_connect(int id)
{
    CLIENT_NETWORK()->Close(id);
}

extern"C" EXPORT_API bool get_connect_status(int id);
bool get_connect_status(int id)
{
	return CLIENT_NETWORK()->GetConnStatus(id);
}


