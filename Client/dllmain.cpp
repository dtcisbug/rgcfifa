// 导出函数
#include "Client.h"
#include "Network/TcpServerWrapper.h"

extern"C" _declspec(dllexport) void init_Client();
void init_Client()
{
    GLOBAL().Init();
    CLIENT().INIT();
    CLIENT().RUN();
}

extern"C" _declspec(dllexport) void uninit_Client();
void uninit_Client()
{
	GLOBAL().UnInit(); //放在最后处理
}

extern"C" _declspec(dllexport) void sendMsg();
void sendMsg(uint32_t sessionID,char* buffer,uint16_t size)
{
    CLIENT_NETWORK()->SendMsgToClient(sessionID,buffer,size);
}

extern"C" _declspec(dllexport) void tick();
void tick()
{

}

extern"C" _declspec(dllexport) void add_connect();
void add_connect(uint16_t uid,std::string ip,uint16_t port)
{
    CLIENT_NETWORK()->AddConnectServer(uid,ip,port);
}

extern"C" _declspec(dllexport) void close_connect();
void close_connect(int id)
{
    CLIENT_NETWORK()->closeConn(id);
}




