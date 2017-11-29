#ifndef _CFG_H_
#define _CFG_H_

#include <tuple>

class Cfg
{
public:
	Cfg();
	void load(const char * = NULL);
	inline void setFilename(const char * fn) {_filename = fn;}

	UInt8		serverType;
	UInt8		serverUID;
	UInt16		tcpPort;
    std::vector<std::tuple<UInt8,UInt8,std::string,UInt16>> serverConnectList;

    std::string ifName;
    UInt32 serverIp;
	std::string	scriptPath;
	UInt32		serverLogId;
	std::string announceFile;

	std::string	dbHost;
	UInt16		dbPort;
	std::string	dbUser;
	std::string	dbPassword;
	std::string	dbSource;
	
    bool debug;

	std::string arenaHost;
	UInt16      arenaPort;

    std::string channelName;
    std::string slugName;
    int channelNum;
    int serverNum;

public:
	inline void setServerType(UInt8 type) {serverType = type;}
	inline void setServerUID(UInt8 uid) {serverUID = uid;}
	inline void setTcpPort(UInt16 p) {tcpPort = p;}
    void addConnectList(UInt8 type,UInt8 uid,const char* str,UInt16 p);

	void setIfName(const char* iname);
	inline void setScriptPath(const char * p) {scriptPath = p;}
	inline void setServerLogId(UInt32 id) {/*serverLogId = id;*/}
	inline void setDatabase(const char * h, UInt16 p, const char * u, const char * pw, const char * s )
	{dbHost = h; dbPort = p; dbUser = u; dbPassword = pw; dbSource = s;}
	inline void setArenaServer(const char * h, UInt16 p) { arenaHost = h; arenaPort = p; }
    void setAdminAllowedIP( const char * str);
    bool isAdminIPAllowed( UInt32 ip );
    inline void setChannelInfo(const char * sn, int num) { slugName = sn; channelNum = num; }
private:
	struct IPMask
	{
		UInt32 addr;
		UInt32 mask;
	};

	IPMask parseAddress(const std::string& addr);

	std::string _filename;
	std::vector<IPMask> _adminIPAllowed;
};

extern Cfg cfg;

#endif // _CFG_H_
