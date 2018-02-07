#include "Common/Config.h"
#include "Logic.h"
#include "Common/TimeUtil.h"
#include "Server/WorldServer.h"
#include "Network/TcpServerWrapper.h"

#define SPLIT_ID(type,id) (static_cast<UInt16>(type) << 8) + static_cast<UInt16>(id) 

namespace GObject
{
    //const char* managed_binary_path = "./CommonNetWork.dll";
    std::string managed_binary_path;
    MonoDomain* domain;
    MonoAssembly* assembly;
    MonoImage* image;
	MonoClass * main_class;
    std::map<UInt8,MonoMethod*> m_mInvokeMethods;

    enum MONOMETHOD
    {
        MM_PRINTMONO = 0x01,
        MM_TICK = 0x02,
        MM_PROCESSMSG = 0x03,
        MM_SETPROXY = 0x04,
        MM_SETSERVICECONFIG = 0x05,
    };

    bool Logic::Init()
    {
        managed_binary_path = "./" + cfg.serverDllName;
        domain = mono_jit_init(cfg.serverDllName.c_str());
        mono_domain_set_config(domain, "./", "machine.config");
        //加载程序集ManagedLibrary.dll
        assembly = mono_domain_assembly_open(domain, managed_binary_path.c_str());
        image = mono_assembly_get_image(assembly);
        
        mono_add_internal_call("CommonNetWork.CCommonNetwork::Testmethod", reinterpret_cast<void*>(TestFunc));
        mono_add_internal_call("CommonNetWork.CCommonNetwork::SendMsg", reinterpret_cast<void*>(SendMsg));
        mono_add_internal_call("CommonNetWork.CCommonNetwork::SendMsg2Server", reinterpret_cast<void*>(SendMsg2Server));
        mono_add_internal_call("CommonNetWork.CCommonNetwork::GetDBStrcut", reinterpret_cast<void*>(GetDBStrcut));
		
        //获取MonoClass,类似于反射
        main_class = mono_class_from_name(image, "CommonNetWork", "CCommonNetwork");

        //AddTimer(86400 * 1000, Logic_Test,this,10*1000);
        AddTimer(5 * 100, Logic::Tick,this,10*1000);
        return true; 
    }


    void Logic::UnInit() 
    {
        mono_jit_cleanup(domain);
        m_mInvokeMethods.clear();
    }

    std::string Logic::GetLogName()
    {
        return "log/" + cfg.serverLogName + "/"; 
    }
            
    MonoString* Logic::TestFunc()
    {
        return mono_string_new (mono_domain_get (), "Hello, world");
    }

    MonoMethod* Logic::GetInvokeMethod(UInt8 name)
    {
        if (m_mInvokeMethods.find(name) != m_mInvokeMethods.end() && m_mInvokeMethods[name] != NULL)
            return m_mInvokeMethods[name];
        MonoMethodDesc* entry_point_method_desc = NULL;
        MonoMethod* entry_point_method = NULL;
        switch(name)
        {
            case MM_PRINTMONO:
                entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:PrintMono()", true);
                break;
            case MM_TICK:
                entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:Tick(int)", false);
                break;
            case MM_PROCESSMSG:
                entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:ProcessMsg", true);
                break;
            case MM_SETPROXY:
                entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:SetProxy(int)", false);
                break;
            case MM_SETSERVICECONFIG:
                entry_point_method_desc = mono_method_desc_new("CommonNetWork.CCommonNetwork:SetServiceConfig(int,int,int)", false);
                break;
            default:
                break;
        }

        if (entry_point_method_desc != NULL)
        {
            entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, main_class);
            m_mInvokeMethods[name] = entry_point_method;
            if (entry_point_method_desc != NULL)
                mono_method_desc_free(entry_point_method_desc);
        }

        return entry_point_method;
    }

    
    void Logic::TestFunc1(int sessionID)
    {
        printf("SessionID is %d \n",sessionID);

    }

    void Logic::Logic_Test(Logic* logic)
    {
        MonoMethod* entry_point_method = logic->GetInvokeMethod(MM_PRINTMONO);
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, NULL, NULL);
        return;
    }

    void Logic::Tick(Logic* logic)
    {
        MonoMethod* entry_point_method = logic->GetInvokeMethod(MM_TICK);
		void* args[1];
		UInt64 now_tick = TimeUtil::GetTick();
		args[0] = &now_tick;
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, args, NULL);
        
        return;
    }

    void Logic::ProcessLogic(UInt32 cmd_id,char* msgBody,UInt32 len,int sessionID)
    {
        if (cmd_id == 0x02)
        {
            ProcessRegisteredProtocol(sessionID);
            return;
        }

        MonoMethod* entry_point_method = GetInvokeMethod(MM_PROCESSMSG);
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
        MonoArray* array = mono_array_new(mono_domain_get (),mono_get_byte_class (),len-2);
        memcpy (mono_array_addr (array, char, 0), body, len-2);
        UInt32 packet_len = *((UInt16*)length);
        void* args[] = { &sessionID,&cmd_id,array,&packet_len};
        //调用方法
        mono_runtime_invoke(entry_point_method, NULL, args, NULL);
		delete body;
    }

    void Logic::ProcessRegisteredProtocol(int sessionID)
    {
        MonoMethod* entry_point_method = GetInvokeMethod(MM_SETPROXY);
        void* args[1];
        args[0] = &sessionID;
        mono_runtime_invoke(entry_point_method, NULL, args, NULL);     

        MonoMethod* entry_point_method1 = GetInvokeMethod(MM_SETSERVICECONFIG);
        void* args1[1];
        int service_id = (static_cast<UInt16>(cfg.serverType) << 8) + static_cast<UInt16>(cfg.serverUID); // source
        int max_db_service = 1;
        int dbservice = (static_cast<UInt16>(1) << 8) + 1; 
         
        args1[0] = &service_id;
        args1[1] = &max_db_service;
        args1[2] = &dbservice;
        //调用方法
        mono_runtime_invoke(entry_point_method1, NULL, args1, NULL);     
    }

    //转发消息
    void Logic::ProcessProxyLogic(UInt32 cmd_id,char* msgBody,UInt32 len,UInt8 target_type,UInt8 target_id,UInt8 source_type,UInt8 source_id,int sessionID)
    {
        printf("ProcessProxyLogic: %u,target type id is %u : %u,source type id is %u : %u,sessionID is %u ! \n", cmd_id,target_type,target_id,source_type,source_id,sessionID);
        if (cmd_id == 0x01)
        {
            m_mLinkedServer[(static_cast<UInt16>(source_type) << 8) + static_cast<UInt16>(source_id)] = sessionID;
            // connect reg msg
            Stream st(static_cast<UInt32>(0x2),
                    SPLIT_ID(source_type,source_id),
                    SPLIT_ID(target_type,target_id)
                    );
            st << "register_okay_protocol!";
            st << Stream::eos;
            NETWORK()->SendMsgToClient(sessionID,&st[0],st.size());
        }
        else
            ProxyMsg2Server(m_mLinkedServer[(static_cast<UInt16>(target_type) << 8) + static_cast<UInt16>(target_id)],cmd_id,msgBody,len,SPLIT_ID(target_type,target_id),SPLIT_ID(source_type,source_id));
    }

    void Logic::SendMsg(int sessionID,int cmdid,MonoArray * buffer,int size)
    {
        Stream st(static_cast<UInt32>(cmdid),
            (static_cast<UInt16>(1) << 8) + static_cast<UInt16>(1), // target 
            static_cast<UInt16>(cfg.serverType) << 8 + static_cast<UInt16>(cfg.serverUID) // source
            );
        st << static_cast<UInt16>(size);
        st.append((uint8_t*)mono_array_addr(buffer, char, 0), size);
        st << Stream::eos;
        printf("SendMsg cmd is %u,Size is %u !!! \n",cmdid,size);

        NETWORK()->SendMsgToClient(sessionID,&st[0],st.size());
    }

    void Logic::SendMsg2Server(int sessionID,int cmdid,MonoArray* buffer,int size,int target)
    {
        Stream st(static_cast<UInt32>(cmdid),
                 static_cast<UInt16>(target), // target 
                 static_cast<UInt16>(cfg.serverType) << 8 + static_cast<UInt16>(cfg.serverUID) // source
            );
        st << static_cast<UInt16>(size);
        st.append((uint8_t*)mono_array_addr(buffer, char, 0), size);
        st << Stream::eos;

        NETWORK()->SendMsgToClient(sessionID,&st[0],st.size());
    }

    void Logic::ProxyMsg2Server(int sessionID,int cmdid,const void * buffer,int size,int target,int source)
    {
        Stream st(static_cast<UInt32>(cmdid),
            static_cast<UInt16>(target), // target 
            static_cast<UInt16>(source) // source
            );
        //st << static_cast<UInt16>(size);
        st.append((uint8_t*)buffer, size);
        st << Stream::eos;
        printf("ProxyMsg2Server cmd is %u,Size is %u !!! \n",cmdid,size);

        NETWORK()->SendMsgToClient(sessionID,&st[0],st.size());
    }

    void Logic::GetDBStrcut(MonoString** ip,MonoString** user,MonoString** passwd,MonoString** db,int* port)
    {
        *ip = mono_string_new (mono_domain_get (), cfg.dbHost.c_str());
        *user = mono_string_new (mono_domain_get (), cfg.dbUser.c_str());
        *passwd = mono_string_new (mono_domain_get (), cfg.dbPassword.c_str());
        *db = mono_string_new (mono_domain_get (), cfg.dbSource.c_str());
        *port = 3306;
    }
}
