#pragma once
#include "common.h"
#include "cocos2d.h"
USING_NS_CC;

class U8Ptr
{
public:
	U8Ptr(int len)
	{
		m_ptr = new uint8[len];
		memset(m_ptr, 0, len);
		m_len = len;
	}
	U8Ptr(const char* p, int len)
	{
		if (len <= 0)
			len = strlen(p);

		m_ptr = new uint8[len];
		memset(m_ptr, 0, len);
		m_len = len;
		memcpy(m_ptr, p, len);
	}
	~U8Ptr()
	{
		delete[] m_ptr;
	}
	void clone(uint8* p,size_t t)
	{
		assert(m_len <= t);
		if(m_len <= t)
			memcpy(m_ptr, p, t); 
	};
	const int& getLength() const{return m_len;}

	uint8*	m_ptr;
private:
	int		m_len;
};

class Guid
{
public:
	Guid():m_guid(0){};
	Guid(uint64 guid){ m_guid = guid;}
	uint64 getValue() { return m_guid;}
	bool equals(Guid* guid) 
	{
		if(guid)
			return m_guid == guid->getValue();

		return false;
	}
	void printDebug() { CCLOGINFO( "guid = 0x%llx",m_guid );}
private:
	uint64 m_guid;
};