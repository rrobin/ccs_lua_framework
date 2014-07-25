#pragma once
#include "common.h"

class PlatformUtility
{
public:
    static void OpenRate();
	static void OpenFullLink( const char* link );
	static bool IsNetUseable();
	static std::string GetDeviceMacAddress();
    static void SetLockScreen( bool canLock );
    static bool IsTheseProcessRunning( const char** checkProcesses, uint32 size );
    static uint64 GetPhysicalMemory();
	static uint64 GetSystemUptime();
    static std::string GetKeychain();
    static std::string getAnonymAccount();
    static std::string getAccount();
    static std::string getPassword();
    static void setAnonymAccount(const char* account);
    static void setAccount(const char* account);
    static void setPassword(const char* password);
    static bool SaveMacToKeychain( const char* mac_address );
	static std::string GetDeviceIfa();
	static bool getDeviceValue(int flag);
	static void setDeviceValue(int flag);
    static void CallTrackingIFA();
	static std::string GetDeviceIdentify();
    static void initTapjoy();
    static void initLimeiCPC();
    static void showiAd( bool bshow );
	static bool DirectoryExists(const std::string dir);
	static bool FileExists(const std::string path);

	static const std::string OpenFolder(std::string baseDir);
	static int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	static const std::string OpenFile(std::string dir,const char* filer);
protected:
private:
};
