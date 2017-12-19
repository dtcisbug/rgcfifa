#include "Common/Config.h"
#include "Logic.h"
#include "Common/TimeUtil.h"
#include "Server/WorldServer.h"
#include "Network/TcpServerWrapper.h"


namespace GObject
{
    UInt8 time = 0;
    
    const char* managed_binary_path = "./CommonNetWork.dll";
    MonoDomain* domain;
    MonoAssembly* assembly;
    MonoImage* image;
	MonoClass * main_class;

    bool Logic::Init()
    {
        domain = mono_jit_init("CommonNetWork.dll");
        //加载程序集ManagedLibrary.dll
        assembly = mono_domain_assembly_open(domain, managed_binary_path);
        image = mono_assembly_get_image(assembly);
        
        mono_add_internal_call("CommonNetWork.CCommonNetwork::Testmethod", reinterpret_cast<void*>(TestFunc));
        mono_add_internal_call("CommonNetWork.CCommonNetwork::SendMsg", reinterpret_cast<void*>(SendMsg));

        //AddTimer(86400 * 1000, Logic_Test,this,10*1000);
        //AddTimer(30, Tick,this,10*1000);
        return true; 
    }


    void Logic::UnInit() 
    {
        mono_jit_cleanup(domain);
    }

    std::string Logic::GetLogName()
    {
        return "log/" + cfg.serverLogName + "/"; 
    }
            
    MonoString* Logic::TestFunc()
    {
        return mono_string_new (mono_domain_get (), "Hello, world");
    }
    
    void Logic::TestFunc1(int sessionID)
    {
        printf("SessionID is %d \n",sessionID);

    }

    void Logic::Logic_Test(Logic* logic)
    {
        // =====================================================准备调用
        //获取MonoClass,类似于反射
		main_class = mono_class_from_name(image, "CommonNetWork", "CCommonNetwork");

        //获取要调用的MonoMethodDesc,主要调用过程
        MonoMethodDesc* entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:PrintMono()", true);
        MonoMethod* entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, main_class);
        mono_method_desc_free(entry_point_method_desc);
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, NULL, NULL);
        
        return;
    }

    void Logic::Tick(Logic* logic)
    {
        // =====================================================准备调用
        //获取MonoClass,类似于反射
		main_class = mono_class_from_name(image, "CommonNetWork", "CCommonNetwork");

        //获取要调用的MonoMethodDesc,主要调用过程
        MonoMethodDesc* entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:Tick(int)", false);
        MonoMethod* entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, main_class);
        mono_method_desc_free(entry_point_method_desc);
		void* args[1];
		UInt64 now_tick = TimeUtil::GetTick();
		args[0] = &now_tick;
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, args, NULL);
        
        return;
    }

    void Logic::ProcessLogic(UInt32 cmd_id,char* msgBody,UInt32 len,int sessionID)
    {
        /*
        INFO_LOG("ProcessLogic: %u, sessionID :%u", cmd_id,sessionID);
        //Logic_Test(this);
        Stream st(static_cast<UInt16>(0x111),
            (static_cast<UInt16>(1) << 8) + static_cast<UInt16>(1),
            (static_cast<UInt16>(0xFF) << 8) + static_cast<UInt16>(1)
            );
        st << "asdadadasdasd";
        st << Stream::eos;
        SendMsg(sessionID,&st[0],st.size());
        */

        //获取MonoClass,类似于反射
		main_class = mono_class_from_name(image, "CommonNetWork", "CCommonNetwork");

        //获取要调用的MonoMethodDesc,主要调用过程
        MonoMethodDesc* entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:ProcessMsg", true);
        MonoMethod* entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, main_class);
        mono_method_desc_free(entry_point_method_desc);
        if (entry_point_method == NULL)
        {
            printf("method is null!!!\n");
            return;
        }
		if (len <= 2)
			return;
        char length[2];
        memcpy(length,msgBody,2);
        char* body = new char[len-2];
        memcpy(body,msgBody+2,len-2);
        //MonoString* str = mono_string_new (mono_domain_get (), (char*)body);
        MonoArray* array = mono_array_new(mono_domain_get (),mono_get_byte_class (),len-2);
        memcpy (mono_array_addr (array, char, 0), body, len-2);
        UInt32 packet_len = *((UInt16*)length);
        void* args[] = { &sessionID,&cmd_id,array,&packet_len};
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, args, NULL);
		delete body;
    }

    //转发消息
    void Logic::ProcessProxyLogic(UInt32 cmd_id,char* msgBody,UInt32 len,UInt8 target_type,UInt8 target_id,UInt8 source_type,UInt8 source_id)
    {
        printf("ProcessProxyLogic: %u,target type id is %u : %u,source type id is %u : %u\n", cmd_id,target_type,target_id,source_type,source_id);

    }

    void Logic::SendMsg(int sessionID,int cmdid,const void * buffer,int size)
    {
        Stream st(static_cast<UInt32>(cmdid),
            (static_cast<UInt16>(1) << 8) + static_cast<UInt16>(1), // target 
            (static_cast<UInt16>(0xFF) << 8) + static_cast<UInt16>(1) // source
            );
        st << (char*)buffer;
        st << Stream::eos;

        NETWORK()->SendMsgToClient(sessionID,&st[0],size);
    }


}
