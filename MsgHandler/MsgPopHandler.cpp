#include "Common/Config.h"
#include "MsgPopHandler.h"
#include "Server/WorldServer.h"
#include "Server/Logic.h"
#include "MsgID.h"

void MsgPopHandler::DeregisterAllMsg()
{
	
}

bool MsgPopHandler::ProcessMsg()
{
	MsgQueue tmp;
	MsgQueue msgQueue;
	if(!GLOBAL().GetMsgQueue( m_Worker, msgQueue ))
		return false;
	MsgHdr* hdr = NULL;
	do
	{
		hdr = msgQueue.Pop();
        switch(hdr->msgType)
        {
            case CLIENT_MSGTYPE:
                {
                    ClientMsgHdr msg1;
                    char* msgBody = (char*)((ClientMsgHdr*)hdr + 1);
                    LOGIC().ProcessLogic(hdr->cmdID,msgBody,hdr->bodyLen,hdr->sessionID); 
                }
                break;
            case SERVER_MSGTYPE:
                {
                    ArenaMsgHdr msg1;
                    char* msgBody = (char*)((ArenaMsgHdr*)hdr + 1);
                    LOGIC().ProcessLogic(hdr->cmdID,msgBody,hdr->bodyLen,hdr->sessionID); 
                }
                break;
            default:
                break;
        }
		char* msgBody = (char*)((MsgHdr*)hdr + 1);
		
        GLOBAL().FreeMsgBlock((char *)hdr);
	}
	while (!msgQueue.Empty());
	return true;
}
