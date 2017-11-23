#include "Common/Config.h"
#include "MsgHandler.h"
#include "Server/WorldServer.h"
#include "MsgID.h"

void MsgHandler::DeregisterAllMsg()
{
	for (int i = 0; i < MAX_MSG_NUM; i++)
	{
		//delete a NULL pointer is also safe
        if (m_HandlerList[i])
        {
            TRACE_LOG("m_HandlerList[%u] delete", i);
        }
		delete (m_HandlerList[i]);
		m_HandlerList[i] = NULL;
	}
}

bool MsgHandler::ProcessMsg()
{
	Handler* handler = NULL;
	MsgQueue tmp;
	MsgQueue msgQueue;
	if(!GLOBAL().GetMsgQueue( m_Worker, msgQueue ))
		return false;
	MsgHdr* hdr = NULL;
	do
	{
		hdr = msgQueue.Pop();
		assert( hdr->cmdID < MAX_MSG_NUM );
        handler = m_HandlerList[hdr->cmdID];
        if (handler != NULL)
        {
            if (!handler->m_Wrapper(handler->m_Func, hdr))
            {
                //Error
                //COUT << "ERROR" << std::endl;
			}
		}
		else
		{
			//Error
		}
        GLOBAL().FreeMsgBlock((char *)hdr);
	}
	while (!msgQueue.Empty());
	return true;
}
