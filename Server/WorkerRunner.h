#ifndef _WORKERRUNNER_H_
#define _WORKERRUNNER_H_

#include "Common/Config.h"
#include "MsgHandler/MsgHandler.h"

#include <event2/event.h>
#include "Log.h"

template<class H = MsgHandler>
class WorkerRunner
{
protected:
	struct TimerEvent
	{
		TimerEvent(void * p, void (*cb)(void *)): param(p), timer_cb(cb) {}
		struct event * ev;
		WorkerRunner<H> * owner;
		void * param;
		void (*timer_cb)(void *);
		UInt32 interval;
	};
public:
	WorkerRunner(UInt32 tv = 0): m_IsActive(false), m_IsPause(false), m_CheckPause(false),
    m_MsgHandler(NULL), m_Timerinterval(tv), m_Log(NULL), _event_base(NULL) { }
	virtual ~WorkerRunner() { Destroy(); }
	inline void RunnerProc()
	{
        try
        {
            m_Log = new Log(1, GetLogName());
        } catch (Exception&)
        {
        }

		_event_base = event_base_new();

		if(!_event_base)
		{
			Destroy();
			throw OutOfMemoryException();
		}

		if(Init())
		{
			m_MsgHandler = new H(TID());

			Run();

			UnInit();
		}

		Destroy();
	}

	inline void Pause() { if(m_IsPause) return;  m_CheckPause = true; m_IsPause = true; }
	inline void Resume() { if(!m_IsPause) return; m_IsPause = false; }

	inline void Shutdown()	//由所在线程启动和关闭此服务
	{
		SetActive( false );
        if (m_MsgHandler)
            m_MsgHandler->setRunnerShutdown(true);
	}

	inline Log* GetLog()
	{
		return m_Log;
	}

	inline UInt8 GetThreadID() { return TID(); }

protected:
	inline static void _event_timer_process(int, short, void * param)
	{
		TimerEvent * te = reinterpret_cast<TimerEvent *>(param);
		te->timer_cb(te->param);
	}
	inline static void _event_timer_process_firsttime(int, short, void * param)
	{
		TimerEvent * te = reinterpret_cast<TimerEvent *>(param);
		te->timer_cb(te->param);
		event_del(te->ev);

		WorkerRunner<H> * wr = reinterpret_cast<WorkerRunner<H> *>(te->owner);
		event_assign(te->ev, wr->_event_base, -1, EV_PERSIST, _event_timer_process, te);
		struct timeval tv = {te->interval / 1000, (te->interval % 1000) * 1000};
		if(event_add(te->ev, &tv) < 0)
		{
			wr->_events.erase(te->ev);
			event_free(te->ev);
			delete te;
			return;
		}
	}
	inline static void _event_msg_process(WorkerRunner<H> * wr)
	{
		wr->DoProcessMsg();
	}
	inline static void _event_timer_process(WorkerRunner<H> * wr)
	{
		wr->DoProcessTimer();
	}
	inline void DoProcessMsg()
	{
		if(!m_IsActive)
			event_base_loopbreak(_event_base);
		if(m_IsPause)
		{
			if(m_CheckPause)
			{
				OnPause();
				m_CheckPause = false;
			}
		}
		else
        {
            ProcessMsg();
        }
	}
	inline void DoProcessTimer()
	{
		if(!m_IsActive)
			event_base_loopbreak(_event_base);
		if(m_IsPause)
		{
			if(m_CheckPause)
			{
				OnPause();
				m_CheckPause = false;
			}
		}
		else
        {
            OnTimer();
        }
	}

public:
	template<class T>
	inline void * AddTimer(UInt32 interval, void (*cb)(T *), T * data = NULL, UInt32 fisrtInterval = 0)
	{
        typedef void (*_common_cb)(void *);
		_common_cb common_cb = reinterpret_cast<_common_cb>(cb);
		TimerEvent * te = new(std::nothrow) TimerEvent(data, common_cb);
		if(te == NULL)
			return NULL;
		struct event * _event;
		te->owner = this;
		te->interval = interval;
		if(fisrtInterval == 0 || fisrtInterval == 0xFFFFFFFF)
		{
			_event = event_new(_event_base, -1, EV_PERSIST, _event_timer_process, te);
			if(_event == NULL)
			{
				delete te;
				return NULL;
			}
			te->ev = _event;
			struct timeval tv = {interval / 1000, (interval % 1000) * 1000};
			if(event_add(_event, &tv) < 0)
			{
				event_free(_event);
				delete te;
				return NULL;
			}
			if(fisrtInterval == 0)
				cb(data);
		}
		else
		{
			_event = event_new(_event_base, -1, 0, _event_timer_process_firsttime, te);
			if(_event == NULL)
			{
				delete te;
				return NULL;
			}
			te->ev = _event;
			struct timeval tv = {fisrtInterval / 1000, (fisrtInterval % 1000) * 1000};
			if(event_add(_event, &tv) < 0)
			{
				event_free(_event);
				delete te;
				return NULL;
			}
		}

		_events[_event] = te;
		return _event;
	}

	inline bool RemoveTimer(void * timer)
	{
		struct event * ev = reinterpret_cast<struct event *>(timer);
		typename std::map<struct event *, TimerEvent *>::iterator it = _events.find(ev);
		if(it != _events.end())
		{
			event_free(it->first);
			delete it->second;
			_events.erase(it);
			return true;
		}
		return false;
	}

protected:
	inline void Run()
	{
		AddTimer(25, _event_msg_process, this);
        if(m_Timerinterval > 0)
		{
            AddTimer(m_Timerinterval, _event_timer_process, this);
		}

		m_IsActive = true;

		event_base_loop(_event_base, 0);
	}

	inline void Destroy()
	{
        UInt32 count = 0;

		for(typename std::map<struct event *, TimerEvent *>::iterator it = _events.begin(); it != _events.end(); ++ it)
		{
            do {
                m_Log->OutTrace("[%u]%u:event_free.\n", TID(), ++count);
            }while (0);
			event_free(it->first);
			delete it->second;
		}
		_events.clear();

        count = 0;
		if(_event_base == NULL)
		{
            do {
                m_Log->OutTrace("[%u]:event_base_free.\n", TID());
            } while (0);
			event_base_free(_event_base);
			_event_base = NULL;
		}
		if(m_MsgHandler != NULL)
		{
			m_MsgHandler->DeregisterAllMsg();
            do {
                m_Log->OutTrace("[%u]:delete m_MsgHandler.\n", TID());
            } while (0);
			delete m_MsgHandler;
			m_MsgHandler = NULL;
		}
		SAFE_DELETE(m_Log);
	}
	inline void SetActive(bool active) { m_IsActive = active; }
	inline bool IsActive() const { return m_IsActive; }
	inline bool ProcessMsg() { return m_MsgHandler->ProcessMsg(); }

protected:
	virtual UInt8 TID() const = 0;
	virtual bool Init() = 0;
	virtual void UnInit() = 0;
	virtual void OnTimer() {}
	virtual void OnPause() {}
	virtual std::string GetLogName() { return ""; }

protected:
	bool m_IsActive;
	bool m_IsPause;
	bool m_CheckPause;
	MsgHandler*	m_MsgHandler;

	UInt32 m_Timerinterval;

	Log* m_Log;

	struct event_base * _event_base;
	std::map<struct event *, TimerEvent *> _events;
};

#endif // _WORKERRUNNER_H_
