#ifndef _MSGTYPES_H_
#define _MSGTYPES_H_

#include "Common/Queue.h"
#include "Common/Platform.h"

enum MSGTYPE
{
    CLIENT_MSGTYPE = 0,
    SERVER_MSGTYPE = 1,

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

struct ArenaMsgHdr
{
    ArenaMsgHdr():
        sessionID(0) { }
    ArenaMsgHdr(UInt32 id, UInt8 type, int sess, UInt32 blen):
        msgHdr(id, type, blen,sess), sessionID(sess) { }
    MsgHdr  msgHdr;
    int sessionID;
};


typedef Queue<MsgHdr*>	MsgQueue;

#endif // _MSGTYPES_H_
