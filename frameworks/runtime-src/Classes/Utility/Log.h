#pragma once

#include "Singleton.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "cocos2d.h"

using namespace cocos2d;

class Log
{
public:
	void outDebug(const char* str, ...){}
	void outError(const char* err, ...){}
	void outErrorDb(const char* err, ...){}
	void outString(const char* err, ...){}
	bool IsOutDebug() {return false;}
};

#define sLog Singleton<Log>::instance()
