#include "Common/Config.h"
#include "Cfg.h"
#include "Network/Network.h"
#include "Common/StringTokenizer.h"

#ifndef _WIN32
#include <sys/ioctl.h> // for ioctl
#include <net/if.h> // for struct ifreq, IF_NAMESIZE
#endif

Cfg::Cfg( ): tcpPort(8889), serverIp(0), serverLogId(0), dbDataPort(3306), dbObjectPort(3306),
    fbVersion(false), vtVersion(false), debug(false),
    openYear(2011), openMonth(9), openDay(23), enableWallow(false), limitLuckyDraw(0),
	merged(false), supportCompress(true), GMCheck(true), channelNum(0), serverNum(0), serverNo(0), testPlatform(false),
    arenaPort(0), serverWarPort(0),
	enableLoginLimit(false), loginLimit(10000), onlineLimit(0), udplog(true), dclog(true), secdclog(false),secdclogTest(false),unionPlatform(false),autoForbid(false),autoKick(false),rpServer(e_rp_none),
    _filename("conf/config.lua")
{
}

void Cfg::load(const char * scriptStr)
{
	/*
    Script::ConfigScript script(this);
	if(scriptStr != NULL)
	{
		script.runScript(scriptStr);
		return;
	}
	script.doFile(_filename.c_str());
    */
}

void Cfg::setIfName(const char* iname)
{
    if (!iname)
        ifName = "eth0";
    else
        ifName = iname;

    int fd;
    fd = socket(AF_INET , SOCK_DGRAM , 0);
    if (fd < 0)
        return;

#ifdef _WIN32
    unsigned long broadcastIP = 0;
    char bufName[20];
    unsigned long* pLocalIP = NULL;
    unsigned long subMask = 0;
    HOSTENT *pHost = NULL;
    gethostname(bufName, 20);
    pHost = gethostbyname(bufName);
    pLocalIP = (unsigned long*)pHost->h_addr_list[0];

    serverIp = *pLocalIP;
#else
    struct ifreq ifr;
    size_t ilen = strlen(ifName.c_str());
    ilen = ilen > IF_NAMESIZE ? IF_NAMESIZE - 1: ilen;
    memset(ifr.ifr_name, 0x00, sizeof(ifr.ifr_name));
    strncpy(ifr.ifr_name , ifName.c_str(), ilen);
    if (ioctl(fd, SIOCGIFADDR , &ifr) < 0)
        return;

    serverIp = ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr;
#endif
}

Cfg::IPMask Cfg::parseAddress(const std::string& addr)
{
	StringTokenizer tk(addr, "/");
	Cfg::IPMask mask = {0, 0};
	if(tk.count() == 0)
		return mask;
	if(tk.count() > 1)
		mask.mask = 32 - atoi(tk[1].c_str());
	mask.addr = ntohl(inet_addr(tk[0].c_str()));
	return mask;
}

void Cfg::setAdminAllowedIP( const char * str )
{
	StringTokenizer tk(str, " ");
	for(size_t i = 0; i < tk.count(); ++ i)
	{
		IPMask ipm = parseAddress(tk[i]);
		if(ipm.mask < 32)
			_adminIPAllowed.push_back(ipm);
	}
}

bool Cfg::isAdminIPAllowed( UInt32 ip )
{
	if(_adminIPAllowed.empty())
		return true;
	for(size_t i = 0; i < _adminIPAllowed.size(); ++ i)
	{
		if(!((_adminIPAllowed[i].addr ^ ip) >> _adminIPAllowed[i].mask))
        {
#ifdef _DEBUG
            struct in_addr addr;
            addr.s_addr = ip;
            fprintf(stderr, "ADMIN IP ALLOWED: (%u): %s\n", ip, inet_ntoa(addr));
#endif
			return true;
        }
	}
#ifdef _DEBUG
    struct in_addr addr;
    addr.s_addr = ip;
    fprintf(stderr, "ADMIN IP IS NOT ALLOWED: (%u): %s\n", ip, inet_ntoa(addr));
#endif
	return false;
}

Cfg cfg;
