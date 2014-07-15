#include "PlatformUtility.h"
#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <netdb.h>
#import <SystemConfiguration/SCNetworkReachability.h>
#include <stdint.h>
#include <mach/mach_time.h>
#include <sys/sysctl.h>

void PlatformUtility::OpenRate()
{
    
}

void PlatformUtility::OpenFullLink( const char* link )
{
    NSString* linkStr = [NSString stringWithUTF8String:link];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:linkStr]];
}

bool PlatformUtility::IsNetUseable()
{
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
    SCNetworkReachabilityFlags flags;
    
    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    CFRelease(defaultRouteReachability);
    
    if (!didRetrieveFlags)
    {
        return false;
    }
    
    BOOL isReachable = flags & kSCNetworkFlagsReachable;
    BOOL needsConnection = flags & kSCNetworkFlagsConnectionRequired;
    return (isReachable && !needsConnection) ? true : false;
}

std::string PlatformUtility::GetDeviceMacAddress()
{
    return std::string("");
}

std::string PlatformUtility::GetKeychain()
{
    return std::string("");
}

bool PlatformUtility::SaveMacToKeychain(const char* mac_address)
{
    return false;
}

void PlatformUtility::SetLockScreen( bool canLock )
{
    if (canLock)
    {
        [UIApplication sharedApplication].idleTimerDisabled=NO;
    }
    else
    {
        [UIApplication sharedApplication].idleTimerDisabled=YES;
    }
}

bool PlatformUtility::IsTheseProcessRunning( const char** checkProcesses, uint32 size )
{
    return true;
}

uint64 PlatformUtility::GetPhysicalMemory()
{
    return [[NSProcessInfo processInfo] physicalMemory];
}

uint64 PlatformUtility::GetSystemUptime()
{
    struct timeval boottime;
    int mib[2] = {CTL_KERN, KERN_BOOTTIME};
    
    size_t size = sizeof(boottime);
    
    time_t now;
    
    time_t uptime = -1;
    
    (void)time(&now);
    
    if (sysctl(mib, 2, &boottime, &size, NULL, 0) != -1 && boottime.tv_sec != 0)
    {
        uptime = now - boottime.tv_sec;
    }
    
    return (uint64)uptime;
}

std::string PlatformUtility::GetDeviceIfa()
{
    return std::string("");
}

std::string PlatformUtility::GetDeviceIdentify()
{
    return std::string("");
}


std::string PlatformUtility::getAnonymAccount()
{
    return std::string("");
}

std::string PlatformUtility::getAccount()
{
    return std::string("");
}

std::string PlatformUtility::getPassword()
{
    return std::string("");
}

void PlatformUtility::setAnonymAccount(const char* account)
{

}

void PlatformUtility::setAccount(const char* account)
{
    
}

void PlatformUtility::setPassword(const char* password)
{

}

void PlatformUtility::initLimeiCPC()
{

}

void PlatformUtility::showiAd(bool bshow)
{

}

bool PlatformUtility::getDeviceValue(int flag)
{
    return 0;
}

void PlatformUtility::setDeviceValue(int flag)
{
    

}

void PlatformUtility::CallTrackingIFA()
{
 
}

void PlatformUtility::initTapjoy()
{
}