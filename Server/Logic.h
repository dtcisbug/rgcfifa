
#ifndef LOGIC_H_
#define LOGIC_H_

#include "MsgHandler/MsgHandler.h"
#include "MsgHandler/MsgPopHandler.h"
#include "Server/WorkerThread.h"
#include "Common/Stream.h"
#include "Server/Cfg.h"
#include "Common/TimeUtil.h"
#include "Network/GameClient.h"
#include "MsgHandler/MsgTypes.h"
#include <map>

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/class.h"
#include "mono/metadata/debug-helpers.h"
#include "mono/metadata/mono-config.h"

namespace GObject
{
    class Logic 
        :public WorkerRunner<MsgPopHandler>
    {
        public:
            inline UInt8 TID() const { return WORKER_THREAD_LOGIC; }
            bool Init();
            void UnInit();
            std::string GetLogName();
            void ProcessLogic(UInt32 cmd_id,char* msgBody,UInt32 len,int sessionID);
            void ProcessRegisteredProtocol(int sessionID);
            void ProcessProxyLogic(UInt32 cmd_id,char* msgBody,UInt32 len,UInt8 target_type,UInt8 target_id,UInt8 source_type,UInt8 source_id,int sessionID);
            //export static method
        public:
            static MonoString* TestFunc();
            static void TestFunc1(int sessionID);
            static void SendMsg(int sessionID,int cmdid,MonoArray * buffer,int size);
            static void SendMsg2Server(int sessionID,int cmdid,MonoArray* buffer,int size,int target);
            static void ProxyMsg2Server(int sessionID,int cmdid,const void * buffer,int size,int target,int source);
            static void GetDBStrcut(MonoString** ip,MonoString** user,MonoString** passwd,MonoString** db,int* port);
        private:
            static void Logic_Test(Logic* logic);
            static void Tick(Logic* logic);

        private:
            std::map<UInt32,UInt32> m_mLinkedServer;
            
    };
}
#endif // LOGIC_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

