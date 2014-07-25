#include "PlatformUtility.h"
#include <windows.h>
#include <conio.h>
#include <Shlobj.h>
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

bool PlatformUtility::DirectoryExists(const std::string dir)	
{
	DWORD dwAttrib = GetFileAttributesA(dir.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool PlatformUtility::FileExists(const std::string path)
{
	DWORD dwAttrib = GetFileAttributesA(path.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

const std::string PlatformUtility::OpenFolder(std::string baseDir)
{
	char buff[MAX_PATH + 1] = {0};
	WCHAR curr[MAX_PATH + 1] = {0};

	if (baseDir.length() > 0)
	{
		MultiByteToWideChar(CP_UTF8, 0, baseDir.c_str(), baseDir.length(), curr, MAX_PATH);
	}
	else
	{
		GetCurrentDirectory(MAX_PATH + 1, curr);
	}

	BROWSEINFOA bi = {0};
	bi.hwndOwner = GetActiveWindow();
	bi.pszDisplayName = buff;
	bi.lpszTitle = "Select Folder";
	bi.lParam = reinterpret_cast<LPARAM>(curr);
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseFolderCallback;

	PIDLIST_ABSOLUTE pid = SHBrowseForFolderA(&bi);
	if (pid)
	{
		SHGetPathFromIDListA(pid, buff);
		return std::string(buff);
	}
	else
	{
		return std::string("");
	}
}

int CALLBACK PlatformUtility::BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED && lpData)
	{
		LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
		SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
	}
	return 0;
}

const std::string PlatformUtility::OpenFile(std::string dir, const char* filer)
{
	char buff[MAX_PATH + 1] = {0};

	OPENFILENAMEA ofn = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetActiveWindow();
	ofn.lpstrFilter = filer;
	ofn.lpstrTitle = "Select File";
	if (DirectoryExists(dir.c_str()))
	{
		ofn.lpstrInitialDir = dir.c_str();
	}
	ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = buff;
	ofn.nMaxFile = MAX_PATH;

	if (GetOpenFileNameA(&ofn))
	{
		return std::string(buff);
	}
	else
		return std::string("");
}