#include "Common/Config.h"

#include "TcpServer.h"
#include "Common/Thread.h"
#include "Common/TimeUtil.h"

#ifdef _WIN32
#define _WSPIAPI_H_
#define _WINSOCKAPI_
#endif
#include <event2/event.h>
#include <event2/util.h>

namespace Network
{

TcpServer::TcpServer():
	_ev_base(NULL), _running(false)
{
	initServer();
}

TcpServer::~TcpServer()
{
}

void TcpServer::initServer()
{
	if(_ev_base != NULL)
		return;

	_ev_base = event_base_new();

	if(!_ev_base)
	{
		destroy();
		throw std::bad_alloc();
	}
}

void TcpServer::destroy()
{
	if(_ev_base != NULL)
	{
		event_base_free(_ev_base);
		_ev_base = NULL;
	}
}

void TcpServer::run()
{
	_running = true;
	while(_running)
	{
		{
			initServer();
			postInitServer();
		}
		event_base_dispatch(_ev_base);
		destroy();
	}
}

void TcpServer::uninit()
{
	_running = false;
}

void TcpSlaveServer::postInitServer()
{
	_evOp = event_new(_ev_base, -1, EV_PERSIST, _ev_op_event, this);
	if(_evOp != NULL)
	{
		struct timeval tv = {0, 250000};
		event_add(_evOp, &tv);
	}

    _evTick = event_new(_ev_base, -1, EV_PERSIST, _ev_tick_event, this);
    if(_evTick != NULL)
    {
        struct timeval tv = {1, 0};
        event_add(_evTick, &tv);
    }
}

void TcpSlaveServer::initConnection(int stype)
{
    if(_connUp.find(stype) != _connUp.end() && _connUp[stype] > 0)
        return;    

	_connUp[stype] = 0;
	FastMutex::ScopedLock lk(_opMutex);
	_opList.push_back(_OpStruct(1, -stype));
}

void TcpSlaveServer::lostConnection( int stype )
{
    _connUp[stype] = -1;
}

void TcpSlaveServer::accepted( int ss )
{
	FastMutex::ScopedLock lk(_opMutex);
	_opList.push_back(_OpStruct(1, ss));
}

void TcpSlaveServer::remove( int id )
{
	FastMutex::ScopedLock lk(_opMutex);
	_opList.push_back(_OpStruct(2, id));
}

void TcpSlaveServer::_accepted( int ss )
{
	TcpConduit * conduit = NULL;
	_mutex.lock();
	while(!_emptySet.empty())
	{
		std::set<size_t>::iterator it = _emptySet.begin();
		size_t id = *it;
		if(id < _conduits.size())
		{
			try
			{
                int uid = id * WORKERS + _slave_idx;
				if(ss < 0)
				{
					try {
                        conduit = newConnection(ss, this, uid);

                        if(conduit)
                            conduit->initConnection();
					} catch(...)
					{
                        if(conduit)
                            delete conduit;
						conduit = NULL;
					}
				}
				else
					conduit = newConduit(ss, this, uid);
				if(conduit == NULL)
				{
					if(ss < 0)
					{
                        _connUp[-ss] = -1;
					}
					_mutex.unlock();
					return;
				}
			}
			catch(...)
			{
				if(ss < 0)
				{
                    _connUp[-ss] = -1;
				}
				_mutex.unlock();
				return;
			}
			_emptySet.erase(it);
			_conduits[id].reset(conduit);
            if (ss < 0)
                _connUp[-ss] = id * WORKERS + _slave_idx;
			_mutex.unlock();
			++ _count;
			return;
		}
	}
	size_t id = _conduits.size();
	try
	{
        int uid = id * WORKERS + _slave_idx;
		if(ss < 0)
		{
			try {
                conduit = newConnection(ss, this, uid);
                if(conduit)
                    conduit->initConnection();
			} catch(...)
			{
                if(conduit)
                    delete conduit;
				conduit = NULL;
			}
		}
		else
			conduit = newConduit(ss, this, uid);
		if(conduit == NULL)
		{
			if(ss < 0)
			{
                _connUp[-ss] = -1;
			}
			_mutex.unlock();
			return;
		}
	}
	catch(...)
	{
		if(ss < 0)
		{
            _connUp[-ss] = -1;
		}
		_mutex.unlock();
		return;
	}
	_conduits.push_back(std::shared_ptr<TcpConduit>(conduit));
	++ _count;
    if (ss < 0)
		_connUp[-ss] = id * WORKERS + _slave_idx;
	_mutex.unlock();
}

void TcpSlaveServer::_remove( int id )
{
	std::shared_ptr<TcpConduit> tcptr;
	_mutex.lock();
	UInt32 rid = id / WORKERS;
	if(rid < _conduits.size() && _conduits[rid].get() != NULL)
	{
		tcptr = _conduits[rid];
		_conduits[rid].reset();
		if(rid == _conduits.size() - 1)
		{
			int rrid = rid;
			do
			{
                if (!_emptySet.empty())
                    _emptySet.erase(rrid);
				-- rrid;
			}
			while(rrid >= 0 && _conduits[rrid].get() == NULL);
			_conduits.resize(rrid + 1);
		}
		else
		{
			_emptySet.insert(rid);
		}
		if(_count > 0) -- _count;
	}
	_mutex.unlock();
}

void TcpSlaveServer::broadcast( const void * buf, int len )
{
    Mutex::ScopedLock lk(_mutex);
	for(_ConduitList::iterator it = _conduits.begin(); it != _conduits.end(); ++ it)
	{
		if((*it).get() != NULL && (*it)->active())
			(*it)->send(buf, len);
	}
}

void TcpSlaveServer::destroy()
{
	{
		Mutex::ScopedLock lk(_mutex);
		_conduits.clear();
		_count = 0;
	}
	if(_evOp != NULL)
	{
		event_del(_evOp);
		_evOp = NULL;
	}
    if(_evTick != NULL)
    {
        event_del(_evTick);
        _evTick = NULL;
    }
	TcpServer::destroy();
}

void TcpSlaveServer::_ev_op_event( int, short, void * arg )
{
	static_cast<TcpSlaveServer *>(arg)->onOpCheck();
}

void TcpSlaveServer::onOpCheck()
{
	if(!_running)
		event_base_loopbreak(_ev_base);
	_opMutex.lock();
	if(_opList.empty())
		_opMutex.unlock();
	else
	{
		std::vector<_OpStruct> rlist = _opList;
		_opList.clear();
		_opMutex.unlock();
		size_t sz = rlist.size();
		for(size_t i = 0; i < sz; ++ i)
		{
			_OpStruct& _os = rlist[i];
			if(_os.type == 1)
				_accepted(_os.data);
			else
				_remove(_os.data);
		}
	}
}

void TcpSlaveServer::_ev_tick_event(int, short, void* arg)
{
    static_cast<TcpSlaveServer*>(arg)->onTick(TimeUtil::Now());
}

void TcpSlaveServer::onTick(UInt32 now)
{
    for(_ConduitList::iterator iter = _conduits.begin();
            iter != _conduits.end(); ++iter)
    {
        if((*iter).get() != NULL) (*iter)->OnTick(now);
    }
}

TcpMasterServer::TcpMasterServer(ServerCommonConfig server_cfg):
	TcpServer(), _socket(0), _ev_server(NULL),_server_cfg(server_cfg)
{
	listen(INADDR_ANY, server_cfg.m_ServerListenPort, 8);
	evutil_make_socket_nonblocking(_socket);
	make_linger(_socket);
}

void TcpMasterServer::listen(UInt32 addr, UInt16 port, UInt32 backlog)
{
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_socket < 0)
		throw std::bad_exception();
	struct sockaddr_in addr2 = {0};
	addr2.sin_family = AF_INET;
	addr2.sin_addr.s_addr = htonl(addr);
	addr2.sin_port = htons(port);
	int r = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&r, sizeof(r));
	if(bind(_socket, (const sockaddr *)&addr2, sizeof(addr2)) < 0)
		throw std::bad_exception();
	if(::listen(_socket, backlog) < 0)
		throw std::bad_exception();
}

void TcpMasterServer::on_server_write()
{
	event_base_loopbreak(_ev_base);
}

void TcpMasterServer::postInitServer()
{
	for(UInt32 i = 0; i < WORKERS; ++ i)
	{
		TcpSlaveServer * s = newWorker(i);
        s->setServerConfig(_server_cfg);
		_workers.push_back(std::shared_ptr<TcpSlaveServer>(s));
	}
	for(int i = 0; i < WORKERS; ++ i)
	{
		_workerThreads[i].start(*_workers[i]);
	}

	_ev_server = event_new(_ev_base, _socket, EV_READ | EV_WRITE | EV_PERSIST, _ev_server_event, this);

	if(_ev_server == NULL)
	{
		close(_socket);
		destroy();
		throw std::bad_alloc();
	}

	event_add(_ev_server, NULL);

	_ev_timer = event_new(_ev_base, -1, EV_PERSIST, _ev_timer_event, this);
	if(_ev_timer != NULL)
	{
		struct timeval tv = {5, 0};
		event_add(_ev_timer, &tv);
	}
}

void TcpMasterServer::on_server_read()
{
	while(1)
	{
		struct sockaddr_in addr = {0};
		socklen_t l = sizeof(addr);
		int sock = accept(_socket, (struct sockaddr *)&addr, &l);
		if(sock < 0)
			return;

		evutil_make_socket_nonblocking(sock);
		make_linger(sock);
		UInt32 min_cap = _workers[0]->getCount();
		int idx = 0;
		for(int i = 1; i < WORKERS; ++ i)
		{
			UInt32 cap = _workers[i]->getCount();
			if(cap < min_cap)
			{
				min_cap = cap;
				idx = i;
			}
		}
		_workers[idx]->accepted(sock);
	}
}

const std::shared_ptr<TcpConduit> TcpMasterServer::find( int id )
{
	if(id == -1)
		return _empty;

	TcpSlaveServer * server = _workers[id % WORKERS].get();
	Mutex::ScopedLock lk(server->_mutex);
	UInt32 rid = id / WORKERS;
	if(rid >= server->_conduits.size())
		return _empty;
	return server->_conduits[rid];
}

const std::shared_ptr<TcpConduit> TcpMasterServer::findConn( int id )
{
    if (id > 0)
        return find(id);
    int rid = -id;
	return find(_workers[0]->_connUp[rid]);
}

void TcpMasterServer::remove( int id )
{
	_workers[id % WORKERS]->remove(id);
}

void TcpMasterServer::close( int id )
{
	if(id == -1)
		return;

	TcpSlaveServer * server = _workers[id % WORKERS].get();
	Mutex::ScopedLock lk(server->_mutex);
	UInt32 rid = id / WORKERS;
	if(rid >= server->_conduits.size() || server->_conduits[rid].get() == NULL)
		return;
	server->_conduits[rid]->closeConn();
}

void TcpMasterServer::closeConn( int id )
{
	int rid = -1 - id;
	if(rid >= TCP_CONN_IDX_MAX)
        return;
	if(rid < 0)
		close(id);
    else
        close(_workers[0]->_connUp[rid]);
}

void TcpMasterServer::broadcast( const void * buf, int len )
{
	for(int i = 0; i < WORKERS; ++ i)
	{
		_workers[i]->broadcast(buf, len);
	}
}

UInt32 TcpMasterServer::getCount()
{
	UInt32 count = 0;
	for(int i = 0; i < WORKERS; ++ i)
	{
		count += _workers[i]->getCount();
	}
	return count;
}

void TcpMasterServer::uninit()
{
	TcpServer::uninit();
	shutdown(_socket, 2);
	for(int i = 0; i < WORKERS; ++ i)
	{
		_workers[i]->uninit();
		_workerThreads[i].join();
	}
}

void TcpMasterServer::_ev_server_event( int fd, short fl, void * arg )
{
	TcpMasterServer * svr = static_cast<TcpMasterServer *>(arg);
	if(fl & EV_WRITE)
		svr->on_server_write();
	else
		svr->on_server_read();
}

void TcpMasterServer::destroy()
{
	if(_ev_server != NULL)
	{
		struct event * ev = _ev_server;
		event_del(ev);
		event_free(ev);
		_ev_server = NULL;
	}
	if(_ev_timer != NULL)
	{
		struct event * ev = _ev_timer;
		event_del(ev);
		event_free(ev);
		_ev_server = NULL;
	}
	if(_socket != 0)
	{
		close(_socket);
		_socket = 0;
	}
}

void TcpMasterServer::_ev_timer_event( int, short, void * param )
{
	static_cast<TcpMasterServer *>(param)->onTimerCheck();
}

void TcpMasterServer::onTimerCheck()
{
	if(_running)
    {
        for (auto& iter : _server_cfg.m_ServerConnectMap)
        {
            _workers[0]->initConnection(iter.first);
        }
    }
	else
		event_base_loopbreak(_ev_base);
}

}
