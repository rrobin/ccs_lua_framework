/* 
 */

#ifndef POCKETHERO_WORLDPACKET_H
#define POCKETHERO_WORLDPACKET_H

#include "common.h"
#include "ByteBuffer.h"
#include "cocos2d.h"
USING_NS_CC;

class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket()                                       : ByteBuffer(0), m_opcode(0), m_guid(0)
        {
        }
        explicit WorldPacket(int opcode, int res=200) : ByteBuffer(res), m_opcode(opcode), m_guid(0) { }

		WorldPacket( int opcode, uint64 guid, int res ) : ByteBuffer(res), m_opcode(opcode), m_guid(guid) { }
                                                            // copy constructor
        WorldPacket(const WorldPacket &packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode), m_guid(packet.m_guid)
        {
        }

        void Initialize(int opcode, int newres=200)
        {
            clear();
            _storage.reserve(newres);
            m_opcode = opcode;
        }

		void Initialize(int opcode, uint64 guid, int newres)
		{
			clear();
			_storage.reserve(newres);
			m_opcode = opcode;
			m_guid = guid;
		}

        int GetOpcode() const 
		{
			//CCLog("opcode = %d",m_opcode);
			return m_opcode; 
		}
        void SetOpcode(int opcode) { m_opcode = opcode; }

		uint64 GetGuid() const { return m_guid; }
		void SetGuid( uint64 guid ){ m_guid = guid; }
		void SetGuid( Guid* guid) { m_guid = guid->getValue(); }
    protected:
        int m_opcode;
		uint64 m_guid;
};

class UIData : public ByteBuffer
{
public:
	UIData(){}
	inline bool compare(const UIData& newData)
	{
		return	(wpos() == newData.wpos()) && (memcmp(this->contents(), newData.contents(), wpos()) == 0);
	}

	bool operator==(const UIData& data)
	{
		return this->compare(data);
	}

	bool operator!=(const UIData& data)
	{
		return this->compare(data) == false;
	}

	UIData& operator=(const UIData& copy)
	{
		if(this == &copy) return *this;
		this->clear();
		if(copy._wpos > 0)
			this->append(copy.contents(),copy._wpos);
		return *this;
	}

	void clone(const UIData* copy)
	{
		if(this == copy) return;
		this->clear();
		if(copy->_wpos > 0)
			this->append(copy->contents(),copy->_wpos);
	}
};
#endif
