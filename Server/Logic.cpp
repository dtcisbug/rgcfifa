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

    bool Logic::Init()
    {
        domain = mono_jit_init("CommonNetWork.dll");
        //加载程序集ManagedLibrary.dll
        assembly = mono_domain_assembly_open(domain, managed_binary_path);
        image = mono_assembly_get_image(assembly);
        
        mono_add_internal_call("CommonNetWork.CCommonNetwork::Testmethod", reinterpret_cast<void*>(TestFunc));
        mono_add_internal_call("CommonNetWork.CCommonNetwork::SendMsg", reinterpret_cast<void*>(SendMsg));

        AddTimer(86400 * 1000, Logic_Test,this,10*1000);
        AddTimer(30, Tick,this,10*1000);
        return true; 
    }


    void Logic::UnInit() 
    {
        mono_jit_cleanup(domain);
    }

    std::string Logic::GetLogName()
    {
        return "log/World/"; 
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
        MonoClass* main_class = mono_class_from_name(image,"CommonNetWork", "CCommonNetwork");

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
        MonoClass* main_class = mono_class_from_name(image,"CommonNetWork", "CCommonNetwork");

        //获取要调用的MonoMethodDesc,主要调用过程
        MonoMethodDesc* entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:Tick()", true);
        MonoMethod* entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, main_class);
        mono_method_desc_free(entry_point_method_desc);
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, NULL, NULL);
        
        return;
    }

    void Logic::ProcessLogic(UInt32 cmd_id,char* msgBody,UInt32 len,int sessionID)
    {
        Logic_Test(this);
    }

    void Logic::SendMsg(int sessionID,const void * buffer,int size)
    {
        NETWORK()->SendMsgToClient(sessionID,buffer,size);

    }


}
