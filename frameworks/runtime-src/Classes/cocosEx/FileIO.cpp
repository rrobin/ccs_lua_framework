#include "FileIO.h"

ByteBuffer* FileIO::getFileData(const char* filename)
{
	auto data = CCFileUtils::getInstance()->getDataFromFile(filename);
	if(data.getSize() > 0 )
	{
		readBuffer.clear();
		readBuffer.append(data.getBytes(),data.getSize());
	}
	return &readBuffer;
}