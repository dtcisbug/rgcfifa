#ifndef _TCPSERVERWRAPPER_INC_
#define _TCPSERVERWRAPPER_INC_

#include <memory>

#include "GameClient.h"
#include "ClientConn.h"
#include "TcpServer.h"
#include "Common/Stream.h"

typedef std::shared_ptr<Network::TcpConduit> TcpConnection;

namespace Network
{
	class TcpSlaveWrapper:
		public TcpSlaveServerT<GameClient>
	{
	public:
		TcpSlaveWrapper(UInt32 idx): TcpSlaveServerT<GameClient>(idx) {}
		virtual TcpConduit * newConnection(int ss, TcpSlaveServer * s, int id)
		{
            int sock = -1;
			switch(ss)
			{
			case -1:
				if(/*!ClientConn::enabled()*/1)
					return NULL;
                sock = socket( AF_INET, SOCK_STREAM, 0 );
                printf("FD %s: %u\n", __PRETTY_FUNCTION__, sock);
                if(sock < 0)
                    return NULL;
				return new(std::nothrow) ClientConn(sock, s, id);
			default:
				return NULL;
			}
			return NULL;
		}
	};

	class TcpServerWrapper
	{
	public:
		TcpServerWrapper(UInt16 port)
		{
			m_TcpService = new TcpMasterServerT<GameClient, TcpSlaveWrapper>(port);
			assert(m_TcpService != NULL);
			m_Active = true;
		}

		~TcpServerWrapper()
		{
			delete m_TcpService;
		}

	public:
		inline void Start()
		{
			m_TcpThread.start(*m_TcpService);
		}
		inline void Join()
		{
			m_TcpThread.join();
		}
		inline void UnInit()
		{
            //printf("pid: %u, m_Active = %u\n", getpid(), m_Active);
			m_Active = false;
			m_TcpService->uninit();
		}

		//关闭某个连接
		inline void Close(int sessionID)
		{
			if(!m_Active)
				return;
			m_TcpService->close(sessionID);
		}

		inline TcpConnection GetConn(int sessionID)
		{
			if(!m_Active)
				return TcpConnection();
			return m_TcpService->find(sessionID);
		}

	public:
		template <typename MsgType>
		void SendMsgToClient(int sessionID, MsgType& msg);

		template <typename MsgType>
		void SendMsgToClient(TcpConduit * conduit, MsgType& msg);

		void SendMsgToClient(int sessionID, const void * buffer, UInt16 size);

		void SendMsgToClient(int sessionID, Stream& st);

		void Broadcast(const void *, int);
		template <typename PredType>
		void Broadcast(const void *, int, PredType);

		void Broadcast(Stream&);
		template <typename PredType>
		void Broadcast(Stream&, PredType);

		template<typename ConduitType, typename PredType, typename DataType>
		void Enumerate(PredType, DataType);
		UInt32 getOnlineNum();

	private:
		bool m_Active;
		Thread m_TcpThread;
		TcpMasterServerT<Network::GameClient, TcpSlaveWrapper>* m_TcpService;
	};

//////////////////////////////////////////////////////////////////////////
	template <typename MsgType>
	inline void TcpServerWrapper::SendMsgToClient(int sessionID, MsgType& msg)
	{
		if(!m_Active)
			return;
		TcpConnection conn = GetConn(sessionID);
		if(conn.get() == NULL)
		{
			//Warn_Debug...
			return;
		}
		std::vector<UInt8> buffer;
		msg.BuildHeader(buffer);
		msg.Serialize(buffer);
		msg.FixHeader(buffer);
		conn->send(&buffer[0], buffer.size());
	}

	template <typename MsgType>
	inline void TcpServerWrapper::SendMsgToClient(TcpConduit * conduit, MsgType& msg)
	{
		if(!m_Active)
			return;
		std::vector<UInt8> buffer;
		msg.BuildHeader(buffer);
		msg.Serialize(buffer);
		msg.FixHeader(buffer);
		conduit->send(&buffer[0], buffer.size());
	}

	inline void TcpServerWrapper::SendMsgToClient(int sessionID, const void * buffer, UInt16 size)
	{
		if(!m_Active)
			return;
		TcpConnection conn = m_TcpService->findConn(sessionID);
		if(conn.get() == NULL)
		{
			return;
		}
		conn->send(buffer, size);
	}

	inline void TcpServerWrapper::SendMsgToClient(int sessionID, Stream& st)
	{
		if(!m_Active)
			return;
		if (st.size() <= 0) return ;
		TcpConnection conn = m_TcpService->findConn(sessionID);

		if(conn.get() == NULL)
		{
			return;
		}
		conn->send(&st[0], st.size());
	}

	inline void TcpServerWrapper::Broadcast( const void * buffer, int size )
	{
		if(!m_Active)
			return;
		m_TcpService->broadcast(buffer, size);
	}

	template <typename PredType>
	inline void TcpServerWrapper::Broadcast( const void * buffer, int size, PredType pred )
	{
		if(!m_Active)
			return;
		m_TcpService->broadcast(buffer, size, pred);
	}

	template <typename PredType>
	inline void TcpServerWrapper::Broadcast( Stream& st, PredType pred )
	{
		if(!m_Active)
			return;
		m_TcpService->broadcast(&st[0], st.size(), pred);
	}

	inline void TcpServerWrapper::Broadcast( Stream& st )
	{
		if(!m_Active)
			return;
		m_TcpService->broadcast(&st[0], st.size());
	}

	template <typename ConduitType, typename PredType, typename DataType>
	inline void TcpServerWrapper::Enumerate( PredType pred, DataType data )
	{
		if(!m_Active)
			return;
		m_TcpService->enumerate<ConduitType>(pred, data);
	}

	inline UInt32 TcpServerWrapper::getOnlineNum()
	{
		if(!m_Active)
			return 0;
		return m_TcpService->getCount();
	}
}

#endif
