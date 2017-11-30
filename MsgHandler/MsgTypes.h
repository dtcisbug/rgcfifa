#ifndef _MSGTYPES_H_
#define _MSGTYPES_H_

#include "Common/Queue.h"
#include "Common/Platform.h"

enum MSGTYPE
{
    CLIENT_MSGTYPE = 0,
    SERVER_MSGTYPE = 1,
    PROXY_MSGTYPE = 2,

    MAX_MSGTYPE
};

struct MsgHdr
{
	MsgHdr(): msgType(0), cmdID(0), bodyLen(0),sessionID(0) {}
	MsgHdr(UInt32 id, UInt8 type, UInt32 blen, int sid): msgType(type), cmdID(id), bodyLen(blen),sessionID(sid) {}
	UInt8	msgType;
	UInt32	cmdID;
	UInt32	bodyLen;
    int sessionID;
};

struct ClientMsgHdr
{
	ClientMsgHdr() { }
	ClientMsgHdr(UInt32 id, UInt8 type, UInt32 blen,int sid):
		msgHdr(id, type, blen,sid) { }
	MsgHdr	msgHdr;
};

struct ProxyMsgHdr
{
    ProxyMsgHdr() { }
    ProxyMsgHdr(UInt32 id, UInt8 type, int sess, UInt32 blen,int target,int source):
        msgHdr(id, type, blen,sess),
        target_type(target >> 8),target_id(static_cast<UInt8>(target)),
        source_type(source >> 8),source_id(static_cast<UInt8>(source)){ }
    MsgHdr  msgHdr;
    UInt8 target_type;
    UInt8 target_id;
    UInt8 source_type;
    UInt8 source_id;
};


typedef Queue<MsgHdr*>	MsgQueue;

#endif // _MSGTYPES_H_
