#ifndef _HASHLIST_H_
#define _HASHLIST_H_

#include <Mutex.h>

#define CORPSE_ENTRY (void *)(-1)

namespace Data
{

template<typename _KeyType, typename _ValueType, typename _Hasher, bool _UseMutex>
class HashList
{
private:
	struct HashEntry
	{
		int hash;
		_KeyType key;
		_ValueType value;

		HashEntry(int h, _KeyType& k, _ValueType& v): hash(h), key(k), value(v) {}
		HashEntry(const HashEntry& other): hash(other.hash), key(other.key), value(other.value) {}
	};
public:
	HashList(): _entryList(NULL), _capacity(0), _count(0)
	{
	}
	HashList(const HashList<_KeyType, _ValueType, _Hasher, _UseMutex>& other): HashList()
	{
		assign(other);
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
	~HashList()
	{
		lock();
		destroy();
		unlock();
	}

	void assign(const HashList<_KeyType, _ValueType, _Hasher, _UseMutex>& other)
	{
		lock();
		destroy();
		_capacity = other._capacity;
		_count = other._count;
		if(_capacity > 0)
		{
			_entryList = new HashEntry[_capacity];
			for(int i = 0; i < _capacity; ++ i)
			{
				if(other._entryList[i] == NULL || other._entryList[i] == CORPSE_ENTRY)
					_entryList[i] = other._entryList[i];
				else
					_entryList[i] = new HashEntry(*other.entryList[i]);
			}
		}
		else
		{
			_entryList = NULL;
		}
		unlock();
	}

	void destroy()
	{
		if(_entryList != NULL)
		{
			for(int i = 0; i < _capacity; ++ i)
			{
				if(_entryList[i] != CORPSE_ENTRY)
				delete _entryList[i];
			}
			delete[] _entryList;
			_entryList = NULL;
		}
		_capacity = 0;
	}

	bool insert(_KeyType& key, _ValueType& value)
	{
		checkupSpace();

		int hash = _hasher.doHash2(key);
		HashEntry * entry = new HashEntry(hash, key, value);

		if(insertInternal(entry))
			return true;
		delete entry;

		return false;
	}

	bool remove(_KeyType& key)
	{
		int hash = _hasher.doHash2(key);
		lock();
		int pos = hash % _capacity;
		for(int i = 0; i < _capacity; ++ i)
		{
			HashEntry *& entry = _entryList[pos];
			if(entry == NULL)
			{
				unlock();
				return false;
			}
			if(entry == CORPSE_ENTRY)
				continue;
			if(entry->hash == hash && entry->key == key)
			{
				delete entry;
				-- _count;
				if(_entryList[(pos + 1) % _capacity] == NULL)
				{
					entry = NULL;
					-- pos;
					if(pos < 0)
						pos = _capacity - 1;
					while(_entryList[pos] == CORPSE_ENTRY)
					{
						_entryList[pos] = NULL;
						-- pos;
						if(pos < 0)
							pos = _capacity - 1;
					}
				}
				else
					entry = static_cast<HashEntry *>(CORPSE_ENTRY);
				unlock();
				return true;
			}
			pos = (pos + 1) % _capacity;
		}
		unlock();
		return false;
	}

	bool take(_KeyType key, _ValueType& val, bool remove)
	{
		int hash = _hasher.doHash2(key);
		lock();
		int pos = hash % _capacity;
		for(int i = 0; i < _capacity; ++ i)
		{
			HashEntry *& entry = _entryList[pos];
			if(entry == NULL)
			{
				unlock();
				return false;
			}
			if(entry == CORPSE_ENTRY)
			{
				continue;
			}
			if(entry->hash == hash && entry->key == key)
			{
				val = entry->value;
				if(remove)
				{
					delete entry;
					-- _count;
					if(_entryList[(pos + 1) % _capacity] == NULL)
					{
						entry = NULL;
						-- pos;
						if(pos < 0)
							pos = _capacity - 1;
						while(_entryList[pos] == CORPSE_ENTRY)
						{
							_entryList[pos] = NULL;
							-- pos;
							if(pos < 0)
								pos = _capacity - 1;
						}
					}
					else
						entry = static_cast<HashEntry *>(CORPSE_ENTRY);
					-- _count;
				}
				unlock();
				return true;
			}
			pos = (pos + 1) % _capacity;
		}
		unlock();
		return false;
	}

	void reset()
	{
		lock();
		for(int i = 0; i < _capacity; ++ i)
		{
			HashEntry *& entry = _entryList[i];
			if(entry != NULL)
			{
				if(entry != CORPSE_ENTRY)
				{
					delete entry;
				}
				entry = NULL;
			}
		}
		unlock();
	}

protected:
	inline void checkupSpace()
	{
		if(_count + (_count >> 2) >= _capacity)
		{
			static int stepSize[] =
			{
				17,				37,				79,				163,			331,
				673,			1361,			2729,			5471,			10949,
				21911,			43853,			87719,			175447,			350899,
				701819,         1403641,		2807303,		5614657,		11229331,
				22458671,		44917381,		89834777,		179669557,		359339171,
				718678369,		1437356741,		2147483647
			};
			lock();
			int i = 0;
			while(stepSize[i] <= _capacity)
				++ i;
			HashEntry ** oldEntry = _entryList;
			int oldCap = _capacity;
			_capacity = stepSize[i];
			_entryList = new HashEntry *[_capacity];
			memset(_entryList, 0, sizeof(HashEntry *) * _capacity);
			_count = 0;
			if(oldEntry != NULL)
			{
				if(oldCap > 0)
				{
					for(i = 0; i < oldCap; ++ i)
					{
						HashEntry * entry = oldEntry[i];
						if(entry == NULL || entry == CORPSE_ENTRY)
							continue;
						insertInternal(entry);
					}
				}
				delete[] oldEntry;
			}
			unlock();
		}
	}

	bool insertInternal(HashEntry * ent)
	{
		lock();
		int pos = ent->hash % _capacity;
		for(int i = 0; i < _capacity; ++ i)
		{
			HashEntry *& entry = _entryList[pos];
			if(entry == NULL || entry == CORPSE_ENTRY)
			{
				entry = ent;
				++ _count;
				unlock();
				return true;
			}
			if(entry->hash == ent->hash && entry->key == ent->key)
			{
				unlock();
				return false;
			}
			pos = (pos + 1) % _capacity;
		}
		unlock();
		return false;
	}

private:
	HashEntry ** _entryList;
	int _capacity;
	int _count;
	_Hasher _hasher;
	FastMutex _mutex;
};

}

#endif // _HASHLIST_H_
