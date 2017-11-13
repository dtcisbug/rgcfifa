#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "HashList.h"

namespace Data
{

template<typename _Type>
class HashTableHasher
{
public:
	inline int doHash1(_Type& val)
	{
		return static_cast<int>(val);
	}
	inline int doHash2(_Type& val)
	{
		return static_cast<int>(val);
	}
};

template<typename _KeyType, typename _ValueType, typename _Hasher = HashTableHasher<_KeyType>, bool _UseMutex = true>
class HashTable
{
private:
	typedef HashList<_KeyType, _ValueType, _Hasher, _UseMutex> HashListType;
public:
	HashTable(int capacity = 257): _capacity(capacity)
	{
		_hashLists = new HashListType[_capacity];
	}
	HashTable(const HashTable<_KeyType, _ValueType, _Hasher, _UseMutex>& other)
	{
		assign(other);
	}
	~HashTable()
	{
		delete[] _hashLists;
	}
	__inline void lock()
	{
		if(_UseMutex)
		{
			_mutex.lock();
		}
	}
	__inline void unlock()
	{
		if(_UseMutex)
		{
			_mutex.unlock();
		}
	}
	void assign(const HashTable<_KeyType, _ValueType, _Hasher, _UseMutex>& other)
	{
		_capacity = other._capacity;
		_hashLists = new HashListType[_capacity];
		for(int i = 0; i < _capacity; ++ i)
		{
			_hashLists[i].assign(other._hashLists[i]);
		}
	}
	bool insert(_KeyType key, _ValueType val)
	{
		int hash = _hasher.doHash1(key);
		return _hashLists[hash % _capacity].insert(key, val);
	}
	bool remove(_KeyType key)
	{
		int hash = _hasher.doHash1(key);
		return _hashLists[hash % _capacity].remove(key);
	}
	bool take(_KeyType key, _ValueType& val, bool remove = false)
	{
		int hash = _hasher.doHash1(key);
		return _hashLists[hash % _capacity].take(key, val, remove);
	}
	void reset()
	{
		for(int i = 0; i < _capacity; ++ i)
		{
			_hashLists[i].reset();
		}
	}

private:
	int _capacity;
	HashListType * _hashLists;
	_Hasher _hasher;
	Mutex _mutex;
};

}

#endif // _HASHTABLE_H_
