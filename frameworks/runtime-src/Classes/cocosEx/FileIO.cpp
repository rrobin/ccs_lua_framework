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

Texture2D* FileIO::openImage(const char* jpgFile,const char* maskFile)
{
	std::string name = jpgFile;
	name.erase(name.length()-4,4);
	auto ret = Director::getInstance()->getTextureCache()->getTextureForKey(name);
	if(ret)
		return ret;
	auto _img = new Image();
	auto _jpg = new Image();
	auto _mask = new Image();
	do 
	{
		if(!_jpg->initWithImageFile(jpgFile))
			break;
		if(!_mask->initWithImageFile(maskFile))
			break;
		auto _color = _jpg->getData();
		auto _alpha = _mask->getData();
		auto _w = _jpg->getWidth();
		auto _h = _jpg->getHeight();
		auto _l = _jpg->getDataLen();
		auto _out = new unsigned char[_l*4];
		for(int idx = 0; idx < _l; idx++)
		{
			_out[idx*4]	  = _color[idx*3];
			_out[idx*4+1] = _color[idx*3+1];
			_out[idx*4+2] = _color[idx*3+2];
			_out[idx*4+3] = _alpha[idx];
		}
		_img->initWithRawData(_out,_l*4,_w,_h,4);
		ret = Director::getInstance()->getTextureCache()->addImage(_img,name);
		SAFE_DELETE(_out);
		break;
	} while (1);

	SAFE_DELETE(_img);
	SAFE_DELETE(_jpg);
	SAFE_DELETE(_mask);
	return ret;
}