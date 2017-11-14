#ifndef MSGHANDLER_INC
#define MSGHANDLER_INC

#include "Server/GlobalObject.h"

#define MAX_MSG_NUM 0x500
#define MIN_INNER_CHECK_MSG 0x200

namespace GObject
{
	class Player;
}

//general message handler
class MsgHandler
{
public:
	MsgHandler(UInt8 worker = 0xFF) : m_Worker(worker), m_RunnerShutdown(false)
	 {
		 for (int i = 0; i < MAX_MSG_NUM; i++)
		 {
			 m_HandlerList[i] = NULL;
		 }
	 }

	 virtual ~MsgHandler()
	 {
	 }

public:
	 void DeregisterAllMsg();

	 bool ProcessMsg();

	 template <typename HdrType, typename MsgType>
	 inline void RegisterMsgHandler( void (*handlerfunc)(HdrType&, MsgType&) )
	 {
		 Handler *handler = new Handler();
		 assert( handler != NULL );
		 handler->m_Func = (char*)handlerfunc;	//save function pointer
		 handler->m_Wrapper = &HandlerWrapper<HdrType, MsgType>;
		 UInt32 msgId = MsgType::s_MsgId;
		 assert( msgId < MAX_MSG_NUM );
		 assert( !m_HandlerList[msgId] );
		 m_HandlerList[msgId] = handler;
	 }

	 template <typename HdrType, int MsgId, typename StructType>
	 inline void RegisterMsgHandler( void (*handlerfunc)(HdrType&, StructType *) )
	 {
		 Handler *handler = new Handler();
		 assert( handler != NULL );
		 handler->m_Func = (char*)handlerfunc;	//save function pointer
		 handler->m_Wrapper = &HandlerWrapper2<HdrType, StructType>;
		 UInt32 msgId = MsgId;
		 assert( msgId < MAX_MSG_NUM );
		 assert( !m_HandlerList[msgId] );
         if(m_HandlerList[msgId])
             printf("%d\n", msgId);
		 m_HandlerList[msgId] = handler;
	 }

     inline void setRunnerShutdown(bool v) { m_RunnerShutdown = v; }
     inline bool isRunnerShutdown() const { return m_RunnerShutdown; }

protected:
	 template <typename HdrType, typename MsgType>
	 static bool HandlerWrapper(char* func, const MsgHdr* hdr)
	 {
		 MsgType msg1;
		 char* msgBody = (char*)((HdrType*)hdr + 1);

		 // 返回-1表示代码解析有问题，通常是数据包长度和需要的字段不匹配
		 if(msg1.Unserialize( msgBody, ((HdrType*)hdr)->msgHdr.bodyLen ) != static_cast<UInt32>(-1))
		 	((void (*)(HdrType&, MsgType&))func)(*(HdrType*)hdr, msg1);
		 return true;
	 }

	 template <typename HdrType, typename StructType>
	 static bool HandlerWrapper2(char* func, const MsgHdr* hdr)
	 {
		 StructType* msgBody = (StructType *)((HdrType*)hdr + 1);

		 ((void (*)(HdrType&, StructType *))func)(*(HdrType*)hdr, msgBody);
		 return true;
	 }

private:
	 struct Handler
	 {
		 bool (*m_Wrapper)(char*, const MsgHdr*);
		 char	*m_Func;
	 };

	 Handler* m_HandlerList[MAX_MSG_NUM];
	 UInt8	 m_Worker;
     bool m_RunnerShutdown;
};

#define MSG_HANDLER_DEFINE(cls) \
class cls: public MsgHandler \
{ \
public: \
	cls(UInt8 worker = 0xFF); \
}; \

#define MSG_HANDLER_DECLARE(cls) \
	cls::cls(UInt8 worker): MsgHandler(worker) \
{ \

#define MSG_HANDLER_END() \
} \

#define MSG_REG_2(H, T, F) \
	RegisterMsgHandler<H, T, const void>(&F)

#define MSG_REG_3(H, T, S, F) \
	RegisterMsgHandler<H, T, S>(&F)

#define MSG_REG(H, F) \
	RegisterMsgHandler<H>(&F)

#endif
