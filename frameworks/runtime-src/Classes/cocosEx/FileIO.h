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

	Texture2D* openImage(const char* jpgFile,const char* maskFile);

	// for "SWF" file
	bool unZipFile(/*int outSize*/);
private:
	ByteBuffer readBuffer;
};