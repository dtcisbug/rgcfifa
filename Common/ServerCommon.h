#ifndef Foundation_SERVER_COMMON_INCLUDED
#define Foundation_SERVER_COMMON_INCLUDED

#include "Platform.h"
#include <map>
#include <tuple>

struct ServerCommonConfig
{
    ServerCommonConfig(UInt8 type,UInt8 uid,UInt16 port) : m_ServerType(type),m_ServerUID(uid),m_ServerListenPort(port)
    {
        m_ServerConnectMap.clear(); 
    }

    void AddConnectList(UInt8 type,UInt8 uid,std::string ip,UInt16 port)
    {
        //m_ServerConnectMap.insert(std::make_pair(static_cast<UInt16>(type << 8) + uid,std::make_tuple(ip,port)));
        m_ServerConnectMap[static_cast<UInt16>(type << 8) + uid] = std::make_tuple(ip,port);
    }

    void AddConnectList(UInt16 uid,std::string ip,UInt16 port)
    {
        //m_ServerConnectMap.insert(std::make_pair(uid,std::make_tuple(ip,port)));
        m_ServerConnectMap[uid] = std::make_tuple(ip,port);
    }

    //ServerCommonConfig(const ServerCommonConfig& config)
    ServerCommonConfig& operator = (const ServerCommonConfig &config)
    {
        m_ServerType = config.m_ServerType; 
        m_ServerUID = config.m_ServerUID; 
        m_ServerListenPort = config.m_ServerListenPort; 
        for (auto& iter : config.m_ServerConnectMap)    
        {
            this->AddConnectList(static_cast<UInt8>(iter.first >> 8),iter.first & 0xFF,std::get<0>(iter.second),std::get<1>(iter.second));
        }
        return *this;
    }

    std::string GetIpFromConnectMap(UInt16 uid) {
        if (m_ServerConnectMap.find(uid) == m_ServerConnectMap.end())
            return "127.0.0.1";
        else
            return std::get<0>(m_ServerConnectMap[uid]);
    }

    UInt16 GetPortFromConnectMap(UInt16 uid) {
        if (m_ServerConnectMap.find(uid) == m_ServerConnectMap.end())
            return 0;
        else
            return std::get<1>(m_ServerConnectMap[uid]);
    }

        
    UInt8 m_ServerType;
    UInt8 m_ServerUID;
    UInt16 m_ServerListenPort;
    std::map<UInt16,std::tuple<std::string,UInt16>> m_ServerConnectMap;
};

#endif // Foundation_Server_Common_INCLUDED
