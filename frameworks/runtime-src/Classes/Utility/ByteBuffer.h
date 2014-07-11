/* 

*/

#ifndef _BYTEBUFFER_H
#define _BYTEBUFFER_H

#include "common.h"
#include <vector>
#include <map>
#include <list>
#include <assert.h>
#include "Errors.h"
#include "Log.h"
#include "ByteConverter.h"

class ByteBufferException
{
public:
	ByteBufferException(bool _add, size_t _pos, size_t _esize, size_t _size)
		: add(_add), pos(_pos), esize(_esize), size(_size)
	{
		PrintPosError();
	}

	void PrintPosError() const
	{
		/*CCLog("Attempted to %s in ByteBuffer (pos: " SIZEFMTD " size: "SIZEFMTD") value with size: " SIZEFMTD,
			(add ? "put" : "get"), pos, size, esize);*/
	}
private:
	bool add;
	size_t pos;
	size_t esize;
	size_t size;
};

template<class T>
struct Unused
{
	Unused() {}
};

class ByteBuffer
{
public:
	const static size_t DEFAULT_SIZE = 0x1000;

	// constructor
	ByteBuffer(): _rpos(0), _wpos(0)
	{
		_storage.reserve(DEFAULT_SIZE);
	}

	// constructor
	ByteBuffer(size_t res): _rpos(0), _wpos(0)
	{
		_storage.reserve(res);
	}

	// copy constructor
	ByteBuffer(const ByteBuffer& buf): _rpos(buf._rpos), _wpos(buf._wpos), _storage(buf._storage) { }

	void clear()
	{
		_storage.clear();
		_rpos = _wpos = 0;
	}

	template <typename T> void put(size_t pos,T value)
	{
		EndianConvert(value);
		put(pos,(uint8*)&value,sizeof(value));
	}

	void put(size_t pos,int value)
	{
		EndianConvert(value);
		put(pos,(uint8*)&value,sizeof((uint8)value));
	}

	ByteBuffer& operator<<(uint8 value)
	{
		append<uint8>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint16 value)
	{
		append<uint16>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint32 value)
	{
		append<uint32>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint64 value)
	{
		append<uint64>(value);
		return *this;
	}

	// signed as in 2e complement
	ByteBuffer& operator<<(int8 value)
	{
		append<int8>(value);
		return *this;
	}

	ByteBuffer& operator<<(int16 value)
	{
		append<int16>(value);
		return *this;
	}

	ByteBuffer& operator<<(int32 value)
	{
		append<int32>(value);
		return *this;
	}

	ByteBuffer& operator<<(int64 value)
	{
		append<int64>(value);
		return *this;
	}

	// floating points
	ByteBuffer& operator<<(float value)
	{
		append<float>(value);
		return *this;
	}

	ByteBuffer& operator<<(double value)
	{
		append<double>(value);
		return *this;
	}

	ByteBuffer& operator<<(const std::string& value)
	{
		append((uint8 const*)value.c_str(), value.length());
		append((uint8)0);
		return *this;
	}

	ByteBuffer& operator<<(const char* str)
	{
		append((uint8 const*)str, str ? strlen(str) : 0);
		append((uint8)0);
		return *this;
	}

	ByteBuffer& operator>>(bool& value)
	{
		value = read<char>() > 0 ? true : false;
		return *this;
	}

	ByteBuffer& operator>>(uint8& value)
	{
		value = read<uint8>();
		return *this;
	}

	ByteBuffer& operator>>(uint16& value)
	{
		value = read<uint16>();
		return *this;
	}

	ByteBuffer& operator>>(uint32& value)
	{
		value = read<uint32>();
		return *this;
	}

	ByteBuffer& operator>>(uint64& value)
	{
		value = read<uint64>();
		return *this;
	}

	//signed as in 2e complement
	ByteBuffer& operator>>(int8& value)
	{
		value = read<int8>();
		return *this;
	}

	ByteBuffer& operator>>(int16& value)
	{
		value = read<int16>();
		return *this;
	}

	ByteBuffer& operator>>(int32& value)
	{
		value = read<int32>();
		return *this;
	}

	ByteBuffer& operator>>(int64& value)
	{
		value = read<int64>();
		return *this;
	}

	ByteBuffer& operator>>(float& value)
	{
		value = read<float>();
		return *this;
	}

	ByteBuffer& operator>>(double& value)
	{
		value = read<double>();
		return *this;
	}

	ByteBuffer& operator>>(std::string& value)
	{
		value.clear();
		while (rpos() < size())                         // prevent crash at wrong string format in packet
		{
			char c = read<char>();
			if (c == 0)
				break;
			value += c;
		}
		return *this;
	}

	template<class T>
	ByteBuffer& operator>>(Unused<T> const&)
	{
		read_skip<T>();
		return *this;
	}


	uint8 operator[](size_t pos) const
	{
		return read<uint8>(pos);
	}

	size_t rpos() const { return _rpos; }

	size_t rpos(size_t rpos_)
	{
		_rpos = rpos_;
		return _rpos;
	}

	size_t wpos() const { return _wpos; }

	size_t wpos(size_t wpos_)
	{
		_wpos = wpos_;
		return _wpos;
	}

	template<typename T>
	void read_skip() { read_skip(sizeof(T)); }

	void read_skip(size_t skip)
	{
		if (_rpos + skip > size())
			throw ByteBufferException(false, _rpos, skip, size());
		_rpos += skip;
	}

	template <typename T> T read()
	{
		T r = read<T>(_rpos);
		_rpos += sizeof(T);
		return r;
	}

	template <typename T> T read(size_t pos) const
	{
		if (pos + sizeof(T) > size())
			throw ByteBufferException(false, pos, sizeof(T), size());
		T valTemp;
		memcpy( &valTemp, &_storage[pos], sizeof(T) );
		T val = *((T const*)(&valTemp));
		EndianConvert(val);
		return val;
	}

	void read(uint8* dest, size_t len)
	{
		if (_rpos  + len > size())
			throw ByteBufferException(false, _rpos, len, size());
		memcpy(dest, &_storage[_rpos], len);
		_rpos += len;
	}

	void read(U8Ptr* p, size_t len)
	{
		if(!p) return;
		if (_rpos  + len > size())
			throw ByteBufferException(false, _rpos, len, size());
		p->clone(&_storage[_rpos], len);
		_rpos += len;
	}

	uint64 readPackGUID()
	{
		uint64 guid = 0;
		uint8 guidmark = 0;
		(*this) >> guidmark;

		for (int i = 0; i < 8; ++i)
		{
			if (guidmark & (uint8(1) << i))
			{
				uint8 bit;
				(*this) >> bit;
				guid |= (uint64(bit) << (i * 8));
			}
		}

		return guid;
	}

	const uint8* contents() const { return &_storage[0]; }

	size_t size() const { return _storage.size(); }
	bool empty() const { return _storage.empty(); }

	void resize(size_t newsize)
	{
		_storage.resize(newsize);
		_rpos = 0;
		_wpos = size();
	}

	void reserve(size_t ressize)
	{
		if (ressize > size())
			_storage.reserve(ressize);
	}

	void append(const std::string& str)
	{
		append((uint8 const*)str.c_str(), str.size() + 1);
	}

	void append(const char* src, size_t cnt)
	{
		return append((const uint8*)src, cnt);
	}

	template<class T> void append(const T* src, size_t cnt)
	{
		return append((const uint8*)src, cnt * sizeof(T));
	}

	void append(const uint8* src, size_t cnt)
	{
		if ( !src || !cnt )
			return;

		assert(size() < 10000000);

		if (_storage.size() < _wpos + cnt)
			_storage.resize(_wpos + cnt);
		memcpy(&_storage[_wpos], src, cnt);
		_wpos += cnt;
	}

	void append(const ByteBuffer& buffer)
	{
		if (buffer.wpos())
			append(buffer.contents(), buffer.wpos());
	}

	// can be used in SMSG_MONSTER_MOVE opcode
	void appendPackXYZ(float x, float y, float z)
	{
		uint32 packed = 0;
		packed |= ((int)(x / 0.25f) & 0x7FF);
		packed |= ((int)(y / 0.25f) & 0x7FF) << 11;
		packed |= ((int)(z / 0.25f) & 0x3FF) << 22;
		*this << packed;
	}

	void appendPackGUID(uint64 guid)
	{
		uint8 packGUID[8+1];
		packGUID[0] = 0;
		size_t size = 1;
		for (uint8 i = 0; guid != 0; ++i)
		{
			if (guid & 0xFF)
			{
				packGUID[0] |= uint8(1 << i);
				packGUID[size] =  uint8(guid & 0xFF);
				++size;
			}

			guid >>= 8;
		}

		append(packGUID, size);
	}

	void append(const U8Ptr* str)
	{
		append((uint8 const*)str->m_ptr, str->getLength());
	}

	void put(size_t pos, const uint8* src, size_t cnt)
	{
		if (pos + cnt > size())
			throw ByteBufferException(true, pos, cnt, size());
		memcpy(&_storage[pos], src, cnt);
	}

	void print_storage() const
	{
		/*if (!sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))   // optimize disabled debug output
			return;

		std::ostringstream ss;
		ss <<  "STORAGE_SIZE: " << size() << "\n";

		if (sLog.IsIncludeTime())
			ss << "         ";

		for (size_t i = 0; i < size(); ++i)
			ss << uint32(read<uint8>(i)) << " - ";

		CCLog(ss.str().c_str());*/
	}

	void textlike() const
	{
		/*if (!sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))   // optimize disabled debug output
			return;

		std::ostringstream ss;
		ss <<  "STORAGE_SIZE: " << size() << "\n";

		if (sLog.IsIncludeTime())
			ss << "         ";

		for (size_t i = 0; i < size(); ++i)
			ss << read<uint8>(i);

		CCLog(ss.str().c_str());*/
	}

	void hexlike() const
	{
		/*if (!sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))   // optimize disabled debug output
			return;

		std::ostringstream ss;
		ss <<  "STORAGE_SIZE: " << size() << "\n";

		if (sLog.IsIncludeTime())
			ss << "         ";

		size_t j = 1, k = 1;

		for (size_t i = 0; i < size(); ++i)
		{
			if ((i == (j * 8)) && ((i != (k * 16))))
			{
				ss << "| ";
				++j;
			}
			else if (i == (k * 16))
			{
				ss << "\n";

				if (sLog.IsIncludeTime())
					ss << "         ";

				++k;
				++j;
			}

			char buf[4];
			snprintf(buf, 4, "%02X", read<uint8>(i));
			ss << buf << " ";

		}
		CCLog(ss.str().c_str());*/
	}

	void setU8(int value)
	{
		append<uint8>((uint8)value);
	}

	int getU8()
	{
		return (int)read<uint8>();
	}

	void setU16(int value)
	{
		append<uint16>((uint16)value);
	}

	int getU16()
	{
		return (int)read<uint16>();
	}

	void setU32(int value)
	{
		append<uint32>((uint32)value);
	}

	int getU32()
	{
		return (int)read<uint32>();
	}

	void setI8(int value)
	{
		append<int8>((int8)value);
	}

	int getI8()
	{
		return (int)read<int8>();
	}

	void setI16(int value)
	{
		append<int16>((int16)value);
	}

	int getI16()
	{
		return (int)read<int16>();
	}

	void setI32(int value)
	{
		append<int32>(value);
	}

	int getI32()
	{
		return read<int32>();
	}

	void setFloat(float value)
	{
		append<float>(value);
	}

	float getFloat()
	{
		return read<float>();
	}

	void setStr(const char* str)
	{
		append((uint8 const*)str, str ? strlen(str) : 0);
		append((uint8)0);
	}
//	std::string getValue;
	const char* getStr()
	{
// 		getValue = "";
// 		while (rpos() < size())                         // prevent crash at wrong string format in packet
// 		{
// 			char c = read<char>();
// 			if (c == '\0')
// 				break;
// 			getValue += c;
// 		}
//		return getValue.c_str();
		const char* str = (const char*)&_storage[_rpos];
		_rpos += strlen(str)+1;
		return str;
		//return (const char*)&_storage[_rpos];
	}

	void setU64(Guid* guid)
	{
		append<uint64>(guid->getValue());
	}

	void setPackGuid(Guid* guid)
	{
		appendPackGUID(guid->getValue());
	}
private:
	// limited for internal use because can "append" any unexpected type (like pointer and etc) with hard detection problem
	template <typename T> void append(T value)
	{
		EndianConvert(value);
		append((uint8*)&value, sizeof(value));
	}

protected:
	size_t _rpos, _wpos;
	std::vector<uint8> _storage;
};

template <typename T>
inline ByteBuffer& operator<<(ByteBuffer& b, std::vector<T> const& v)
{
	b << (uint32)v.size();
	for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
	{
		b << *i;
	}
	return b;
}

template <typename T>
inline ByteBuffer& operator>>(ByteBuffer& b, std::vector<T>& v)
{
	uint32 vsize;
	b >> vsize;
	v.clear();
	while (vsize--)
	{
		T t;
		b >> t;
		v.push_back(t);
	}
	return b;
}

template <typename T>
inline ByteBuffer& operator<<(ByteBuffer& b, std::list<T> const& v)
{
	b << (uint32)v.size();
	for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
	{
		b << *i;
	}
	return b;
}

template <typename T>
inline ByteBuffer& operator>>(ByteBuffer& b, std::list<T>& v)
{
	uint32 vsize;
	b >> vsize;
	v.clear();
	while (vsize--)
	{
		T t;
		b >> t;
		v.push_back(t);
	}
	return b;
}

template <typename K, typename V>
inline ByteBuffer& operator<<(ByteBuffer& b, std::map<K, V>& m)
{
	b << (uint32)m.size();
	for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); ++i)
	{
		b << i->first << i->second;
	}
	return b;
}

template <typename K, typename V>
inline ByteBuffer& operator>>(ByteBuffer& b, std::map<K, V>& m)
{
	uint32 msize;
	b >> msize;
	m.clear();
	while (msize--)
	{
		K k;
		V v;
		b >> k >> v;
		m.insert(std::make_pair(k, v));
	}
	return b;
}

template<>
inline void ByteBuffer::read_skip<char*>()
{
	std::string temp;
	*this >> temp;
}

template<>
inline void ByteBuffer::read_skip<char const*>()
{
	read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<std::string>()
{
	read_skip<char*>();
}
#endif
