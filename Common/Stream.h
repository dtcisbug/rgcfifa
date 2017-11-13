#ifndef _STREAM_H_
#define _STREAM_H_

#include <memory.h>

class Stream
{
public:
	static Stream& eos(Stream& st)
	{
		st.data<UInt16>() = st.size() - 4;
		return st;
	}
	Stream(): _pos(0) {}
	Stream(UInt8 cmd, UInt8 magic = 0xFF): _pos(0)
	{
		init(cmd, magic);
	}
	Stream(const UInt8 * buf, size_t len): _pos(0)
	{
		if(len > 0)
		{
			_buf.assign(buf, buf + len);
		}
	}
	Stream(std::vector<UInt8>& v): _pos(0)
	{
		_buf.assign(v.begin(), v.end());
	}
	void init(UInt8 cmd, UInt8 magic = 0xFF)
	{
		UInt8 buf[4] = {0, 0, magic, cmd};
		_buf.assign(buf, buf + 4);
	}
	inline operator std::vector<UInt8>&() {return _buf;}
	inline operator UInt8*() {return _buf.empty() ? NULL : &_buf[0];}
	inline size_t size() {return _buf.size();}
	inline size_t left() {return _buf.size() - _pos;}
	inline size_t pos() {return _pos;}
	inline bool empty() {return _buf.empty();}
	inline void reset()
	{
		_pos = 0;
	}
	inline void clear()
	{
		_buf.clear();
		reset();
	}
	size_t first_of(UInt8 b)
	{
		size_t c = _buf.size();
		for(size_t i = 0; i < c; ++ i)
		{
			if(_buf[i] == b)
			{
				return i;
			}
		}
		return (size_t)-1;
	}
	inline void pop_front(size_t n)
	{
		if(n >= _buf.size())
			_buf.clear();
		else
			_buf.erase(_buf.begin(), _buf.begin() + n);
	}
	inline void remove(size_t s, size_t n)
	{
		if(s >= _buf.size())
			return;
		if(s + n > _buf.size())
			n = _buf.size() - s;
		_buf.erase(_buf.begin() + s, _buf.begin() + s + n);
	}
	inline void append_zero(size_t len)
	{
		if(len > 0)
			_buf.resize(_buf.size() + len, 0);
	}
	inline void append(const UInt8 * buf, size_t len)
	{
		_buf.insert(_buf.end(), buf, buf + len);
	}
	inline void prepend(const UInt8 * buf, size_t len)
	{
		_buf.insert(_buf.begin(), buf, buf + len);
	}
	inline int read(UInt8 * buf, size_t len)
	{
		if(_pos + len > _buf.size())
			len = _buf.size() - _pos;
		if(len == 0)
			return 0;
		memcpy(buf, &_buf[_pos], len);
		_pos += len;
		return (int)len;
	}
	template<typename T>
	inline Stream& operator>>(T& v)
	{
		read((UInt8 *)&v, sizeof(T));
		return *this;
	}
	template<typename T>
	inline Stream& operator<<(const T& v)
	{
		append((UInt8 *)&v, sizeof(T));
		return *this;
	}
	inline Stream& operator>>(std::vector<UInt8>& v)
	{
		read(&v.front(), v.size());
		return *this;
	}
	inline Stream& operator<<(const std::vector<UInt8>& v)
	{
		_buf.insert(_buf.end(), v.begin(), v.end());
		return *this;
	}
	template<typename T>
	inline Stream& operator>>(std::vector<T>& v)
	{
		UInt32 n;
		(*this)>>n;
		v.resize(n);
		if(n > 0)
		{
			read(&v[0], sizeof(T) * n);
		}
		return *this;
	}
	template<typename T>
	inline Stream& operator<<(const std::vector<T>& v)
	{
		UInt32 n = static_cast<UInt32>(v.size());
		(*this)<<n;
		append((UInt8 *)&v[0], sizeof(T) * n);
		return *this;
	}
	inline Stream& operator>>(std::string& v)
	{
		UInt16 l;
		(*this) >> l;
		UInt32 lft = static_cast<UInt32>(left());
		if(l > lft)
			l = lft;
		v.resize(l);
		memcpy(&v[0], &_buf[_pos], l);
		_pos += l;
		return *this;
	}
	inline Stream& operator<<(const std::string& v)
	{
		(*this) << static_cast<UInt16>(v.length());
		_buf.insert(_buf.end(), v.begin(), v.end());
		return *this;
	}
	inline Stream& operator<<(const char * v)
	{
		if(v == NULL)
		{
			(*this) << static_cast<UInt16>(0);
			return *this;
		}
		UInt16 len = static_cast<UInt16>(strlen(v));
		(*this) << len;
		_buf.insert(_buf.end(), v, v + len);
		return *this;
	}
	inline Stream& operator<<(char * v)
	{
		if(v == NULL)
		{
			(*this) << static_cast<UInt16>(0);
			return *this;
		}
		UInt16 len = static_cast<UInt16>(strlen(v));
		(*this) << len;
		_buf.insert(_buf.end(), v, v + len);
		return *this;
	}
	inline Stream& operator<<(Stream& (*fn)(Stream&))
	{
		return fn(*this);
	}
	inline Stream& operator+=(UInt32 n)
	{
		_pos += n;
		if(_pos > _buf.size())
			_pos = _buf.size();
		return *this;
	}
	inline Stream& operator-=(UInt32 n)
	{
		if(_pos < n)
			_pos = 0;
		else
			_pos -= n;
		return *this;
	}
	template<typename T>
	inline T& data(size_t offset = 0)
	{
		if(offset + sizeof(T) > _buf.size())
		{
			static T tmp(0);
			return tmp;
		}
		return *(T *)&_buf[offset];
	}

	inline Stream& operator<<(const Stream& v)
    { 
        (*this) << v._buf;        
        return *this;
    } 
protected:
	size_t _pos;
	std::vector<UInt8> _buf;
};

#endif // _STREAM_H_
