#include "PlatformUtility.h"
#include <windows.h>
#include <conio.h>
#include "cocos2d.h"
USING_NS_CC;

char mac_addr[18];
void PlatformUtility::OpenRate()
{
    // do nothing
}

void PlatformUtility::OpenFullLink( const char* link )
{
	// do nothing
}

bool PlatformUtility::IsNetUseable()
{
	return true;
}

std::string PlatformUtility::GetDeviceMacAddress()
{
	GUID uuid;
	CoCreateGuid(&uuid);
	sprintf(mac_addr,"%02X:%02X:%02X:%02X:%02X:%02X",uuid.Data4[2],uuid.Data4[3],uuid.Data4[4],uuid.Data4[5],uuid.Data4[6],uuid.Data4[7]);
	return std::string(mac_addr);
	//return "12321345";
}

void PlatformUtility::SetLockScreen( bool canLock )
{

}

bool PlatformUtility::IsTheseProcessRunning( const char** checkProcesses, uint32 size )
{

	return false;
}

uint64 PlatformUtility::GetPhysicalMemory()
{
	uint64 memory = (uint64)1024 * 1024 * 1024;
	return memory;
}

uint64 PlatformUtility::GetSystemUptime()
{
	//uint64 ret = GetTickCount();
	//ret = ret / 1000;
	//return ret;
	return 0;
}

std::string PlatformUtility::GetKeychain()
{
	return std::string("1234567890123456789012345");
}

std::string PlatformUtility::getAnonymAccount()
{
	return UserDefault::getInstance()->getStringForKey("Anonym");
}

std::string PlatformUtility::getAccount()
{
	return UserDefault::getInstance()->getStringForKey("Account");
}
std::string PlatformUtility::getPassword()
{
	return UserDefault::getInstance()->getStringForKey("Password");
}

void PlatformUtility::setAnonymAccount(const char* account)
{
	UserDefault::getInstance()->setStringForKey("Anonym",account);
}

void PlatformUtility::setAccount(const char* account)
{
	UserDefault::getInstance()->setStringForKey("Account",account);
}

void PlatformUtility::setPassword(const char* password)
{
	UserDefault::getInstance()->setStringForKey("Password",password);
}

bool PlatformUtility::SaveMacToKeychain( const char* mac_address )
{
	return true;
}

std::string PlatformUtility::GetDeviceIfa()
{
	return std::string("daijinlong");
}

void PlatformUtility::CallTrackingIFA()
{

}

void PlatformUtility::initLimeiCPC()
{

}

void PlatformUtility::showiAd( bool bshow )
{

}

std::string PlatformUtility::GetDeviceIdentify()
{
	// IOS7以下是返回macAddress, IOS7及IOS7以上返回Ifa
	return GetDeviceIfa();
}

void PlatformUtility::initTapjoy()
{

}

bool PlatformUtility::getDeviceValue(int flag)
{
	return true;
}

void PlatformUtility::setDeviceValue(int flag)
{

}