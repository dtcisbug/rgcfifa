
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
            static MonoString* TestFunc();
            static void TestFunc1(int sessionID);
            void ProcessLogic(UInt32 cmd_id,char* msgBody,UInt32 len,int sessionID);
            void ProcessProxyLogic(UInt32 cmd_id,char* msgBody,UInt32 len,UInt8 target_type,UInt8 target_id,UInt8 source_type,UInt8 source_id);
            static void SendMsg(int sessionID,const void * buffer,int size);
        private:
            static void Logic_Test(Logic* logic);
            static void Tick(Logic* logic);
            
    };
}
#endif // LOGIC_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

