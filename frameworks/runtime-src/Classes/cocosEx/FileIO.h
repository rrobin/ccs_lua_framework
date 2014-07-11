#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "Utility/ByteBuffer.h"

class FileIO : public Ref
{
public:
	CREATE_FUNC(FileIO);
	virtual bool init(){return true;}
	ByteBuffer* getFileData(const char* filename);
private:
	ByteBuffer readBuffer;
};