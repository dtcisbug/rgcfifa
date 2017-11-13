#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <queue>

//////////////////////////////////////////////////////////////////////////
template <typename Type>
class Queue
{
public:
	Queue()
	{
	}

	~Queue()
	{
	}

	Queue(const Queue<Type>& other) : m_Queue(other.m_Queue)
	{
	}

	Queue<Type>& operator=(const Queue<Type>& other)
	{
		m_Queue = other.m_Queue;
		return *this;
	}

public:
	inline void	Push(const Type& elem)
	{
		m_Queue.push_back( elem );
	}

	inline void Push(const Queue<Type>& other)
	{
		m_Queue.insert(m_Queue.end(), other.m_Queue.begin(), other.m_Queue.end());
	}

	inline Type	Pop()
	{
		assert( !m_Queue.empty() );
		Type elem = m_Queue.front();
		m_Queue.pop_front();
		return elem;
	}

	inline bool	Empty() const
	{
		return m_Queue.empty();
	}

	inline void Clear()
	{
		m_Queue.clear();
	}

	inline int	Size() const
	{
		return m_Queue.size();
	}

private:
	std::deque<Type> m_Queue;
};

#endif // _QUEUE_H_
