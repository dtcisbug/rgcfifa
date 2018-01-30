#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "TcpConduit.h"
#include "Network.h"

#include "Common/Mutex.h"
#include "Common/Thread.h"
#include "Common/Runnable.h"
#include "Common/ServerCommon.h"

struct event_base;
struct event;

namespace Network
{
	#define WORKERS 2
	#define TCP_CONN_IDX_MAX 2  

	#ifdef _WIN32
	#define event_int intptr_t
	#else
	#define event_int int
	#endif

	class TcpService:
		public Runnable
	{
	public:
		TcpService();
		virtual ~TcpService();
		virtual void destroy();
		void run();
		virtual void uninit();
		inline struct event_base *getEvBase() {return _ev_base;}

	protected:
		void initServer();
		virtual void postInitServer() {}

	protected:
		struct event_base * _ev_base;

		bool _running;
	};

	class TcpMasterServer;
	class TcpSlaveServer:
		public TcpService
	{
		friend class TcpMasterServer;
		friend class TcpClientService;
	public:
		TcpSlaveServer(UInt32 idx): TcpService(), _slave_idx(idx), _count(0), _evOp(NULL), _evTick(NULL), _server_cfg(0,0,0) 
        { 
        }
		void initConnection(int = 1);
		void lostConnection(int = 1);
		void accepted(int);
		void remove(int);
		inline UInt32 getCount() { return _count;}
		virtual void destroy();

	protected:
		virtual void postInitServer();
		void _accepted(int);
		void _remove(int);

		virtual TcpConduit * newConduit(int, TcpSlaveServer *, int) = 0;
		virtual TcpConduit * newConnection(int, TcpSlaveServer *, int) = 0;

		typedef std::vector<std::shared_ptr<TcpConduit> > _ConduitList;

		static void _ev_op_event(event_int, short, void *);
		void onOpCheck();

        static void _ev_tick_event(event_int, short, void*);
        void onTick(UInt32 now);

		template<typename PredType>
		void broadcast(const void *, int, PredType pred);
		void broadcast(const void *, int);
		template <typename ConduitType, typename PredType, typename DataType>
		void enumerate(PredType pred, DataType);
        void setServerConfig(const ServerCommonConfig& cfg) { _server_cfg = cfg;}

	protected:
		UInt32 _slave_idx;

        //TcpConduit* _connConduit;
		_ConduitList _conduits;
		std::set<size_t> _emptySet;

        std::map<int/*id*/,int/*flag*/> _connUp;

	private:
		Mutex _mutex;
		UInt32 _count;

		struct event * _evOp;
        struct event * _evTick;
		FastMutex _opMutex;
		struct _OpStruct
		{
			_OpStruct(UInt8 _t = 0, int _d = 0): type(_t), data(_d) {}
			UInt8 type;
			int data;
		};
		std::vector<_OpStruct> _opList;
    protected:
        ServerCommonConfig _server_cfg;

	};

	class TcpMasterServer:
		public TcpService
	{
	public:
		TcpMasterServer(ServerCommonConfig server_cfg);
		void listen(UInt32 addr, UInt16 port, UInt32 backlog);
		const std::shared_ptr<TcpConduit> find(int id);
		const std::shared_ptr<TcpConduit> findConn(int id);
		void remove(int id);
		void close(int id);
		void closeConn(int id);
		template <typename PredType>
		void broadcast(const void *, int, PredType pred);
		void broadcast(const void *, int);
		template <typename ConduitType, typename PredType, typename DataType>
		void enumerate(PredType pred, DataType);
		UInt32 getCount();
		virtual void uninit();
		virtual void destroy();

	protected:
		void postInitServer();
		virtual TcpSlaveServer * newWorker(int) = 0;
		static void _ev_server_event(event_int, short, void *);
		void on_server_write();
		void on_server_read();
		static void _ev_timer_event(event_int, short, void *);
		void onTimerCheck();

	private:
		int _socket;
		struct event * _ev_server, * _ev_timer;
		std::shared_ptr<TcpConduit> _empty;
		Thread _workerThreads[WORKERS];
		std::vector<std::shared_ptr<TcpSlaveServer> > _workers;
        ServerCommonConfig _server_cfg;
	};

    class TcpClientService:
		public TcpService
	{
	public:
		TcpClientService();
		void remove(int id);
		void close(int id);
		void closeConn(int id);
        UInt32 getCount();
		virtual void uninit();
		virtual void destroy();
		const std::shared_ptr<TcpConduit> findConn(int id);
        const std::shared_ptr<TcpConduit> find( int id );
        void AddConnectServer(UInt16 uid,std::string ip,UInt16 port);

	protected:
		void postInitServer();
		virtual TcpSlaveServer * newWorker(int) = 0;
		static void _ev_timer_event(event_int, short, void *);
		void onTimerCheck();

	private:
		struct event *_ev_timer;
		std::shared_ptr<TcpConduit> _empty;
		Thread _workerThreads;
		std::vector<std::shared_ptr<TcpSlaveServer> > _workers;
        ServerCommonConfig _server_cfg;
	};


	template<class T = TcpConduit>
	class TcpSlaveServerT:
		public TcpSlaveServer
	{
	public:
		TcpSlaveServerT(UInt32 idx): TcpSlaveServer(idx) {}
	protected:
		virtual TcpConduit * newConduit(int ss, TcpSlaveServer * s, int id) { return new(std::nothrow) T(ss, s, id); }
		virtual TcpConduit * newConnection(int, TcpSlaveServer *, int) { return NULL; }
	};

    template<class T = TcpConduit, class SL = TcpSlaveServerT<T> >
        class TcpClientServiceT:
            public TcpClientService 
    {
        public:
            TcpClientServiceT(): TcpClientService() {}
        protected:
            TcpSlaveServer * newWorker(int idx) { return new SL(idx); }
    };

	template<class T = TcpConduit, class SL = TcpSlaveServerT<T> >
	class TcpMasterServerT:
		public TcpMasterServer
	{
	public:
		TcpMasterServerT(ServerCommonConfig server_cfg): TcpMasterServer(server_cfg) {}
	protected:
		TcpSlaveServer * newWorker(int idx) { return new SL(idx); }
	};

	template <typename PredType>
	void TcpSlaveServer::broadcast( const void * buf, int len, PredType pred )
	{
		Mutex::ScopedLock lk(_mutex);
		for(_ConduitList::iterator it = _conduits.begin(); it != _conduits.end(); ++ it)
		{
			TcpConduit * conduit = (*it).get();
			if(conduit != NULL && conduit->active() && bool(pred(conduit)))
				(*it)->send(buf, len);
		}
	}

	template <typename PredType>
	void TcpMasterServer::broadcast( const void * buf, int len, PredType pred )
	{
		for(int i = 0; i < WORKERS; ++ i)
		{
			_workers[i]->broadcast(buf, len, pred);
		}
	}

	template <typename ConduitType, typename PredType, typename DataType>
	void TcpSlaveServer::enumerate( PredType pred, DataType data )
	{
		Mutex::ScopedLock lk(_mutex);
		for(_ConduitList::iterator it = _conduits.begin(); it != _conduits.end(); ++ it)
		{
			if((*it).get() != NULL && !pred((ConduitType *)(*it).get(), data))
					return;
		}
	}

	template <typename ConduitType, typename PredType, typename DataType>
	void TcpMasterServer::enumerate( PredType pred, DataType data )
	{
		for(int i = 0; i < WORKERS; ++ i)
		{
			_workers[i]->enumerate<ConduitType>(pred, data);
		}
	}
}

#endif // _TCPSERVER_H_
