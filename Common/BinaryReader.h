#ifndef _BINARYREADER_H_
#define _BINARYREADER_H_

#include <memory.h>

class BinaryReader
{
public:
	BinaryReader(const void * buf, size_t len): _pos(0), _len(len), _buf(reinterpret_cast<const UInt8 *>(buf)) {}
	inline size_t size() {return _len;}
	inline size_t left() {return _len - _pos;}
	inline size_t pos() {return _pos;}
	inline bool empty() {return _len == 0;}
	inline void reset()
	{
		_pos = 0;
	}
	inline int read(UInt8 * buf, size_t len)
	{
		if(_pos + len > _len)
			len = _len - _pos;
		if(len == 0)
			return 0;
		memcpy(buf, &_buf[_pos], len);
		_pos += len;
		return (int)len;
	}
	template<typename T>
	inline BinaryReader& operator>>(T& v)
	{
		read((UInt8 *)&v, sizeof(T));
		return *this;
	}
	inline BinaryReader& operator>>(std::vector<UInt8>& v)
	{
		read(&v.front(), v.size());
		return *this;
	}
	template<typename T>
	inline BinaryReader& operator>>(std::vector<T>& v)
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
	inline BinaryReader& operator>>(std::string& v)
	{
		UInt16 l;
		(*this) >> l;
		UInt32 lft = static_cast<UInt32>(left());
		if(l > lft)
			l = lft;
		v.resize(l);
		if(l > 0)
		{
			memcpy(&v[0], &_buf[_pos], l);
			_pos += l;
		}
		return *this;
	}
	inline BinaryReader& operator+=(UInt32 n)
	{
		_pos += n;
		if(_pos > _len)
			_pos = _len;
		return *this;
	}
	inline BinaryReader& operator-=(UInt32 n)
	{
		if(_pos < n)
			_pos = 0;
		else
			_pos -= n;
		return *this;
	}
	template<typename T>
	inline const T& data(size_t offset = 0)
	{
		if(offset + sizeof(T) > _len)
		{
			static T tmp(0);
			return tmp;
		}
		return *(const T *)&_buf[offset];
	}
	const UInt8& operator [] (size_t idx) { if(idx < _len) return _buf[idx]; return _buf[0]; }
protected:
	size_t _pos, _len;
	const UInt8 * _buf;
};

#endif // _BINARYREADER_H_
