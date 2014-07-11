#include "AdWallInterface.h"
//#include "AdWallManager.h"
//#include "Client.h"
//#include "WorldPacket.h"
//#include "Opcodes.h"
#import <Tapjoy/Tapjoy.h>

bool AdWallInterface::m_hasInit = false;
bool AdWallInterface::m_isInitLimeiCPC = false;

bool AdWallInterface::init( int adWallType )
{
	m_hasInit = true;
    //bool initRet = [[AdWallManager sharedInstance] initAdWall:adWallType];
	//return initRet;
    return true;
}

bool AdWallInterface::canUseAdWall()
{
    /*bool clientInNet = sClient.isInNet();
    bool clientAdWallType = sClient.m_adwallType > 0;
    if ( m_hasInit )
    {
        if( clientInNet )
        {
            if( clientAdWallType )
                return true;
        }
    }*/
    return false;
}

void AdWallInterface::setNetAccountName( const char* accountName )
{
    //[[AdWallManager sharedInstance] setAccountName:[NSString stringWithUTF8String:accountName]];
}

void AdWallInterface::enterAdWall()
{
	//[[AdWallManager sharedInstance] enterAdWall];
}

void AdWallInterface::queryScore()
{
    //[[AdWallManager sharedInstance] queryScore];
}

void AdWallInterface::onQueryScoreBack( int score )
{
    /*if ( score > 0 && canUseAdWall() ) {
        reduceScore( score );
    }*/
}

void AdWallInterface::reduceScore( int score )
{
    //[[AdWallManager sharedInstance] reduceScore:score];
}

void AdWallInterface::onReduceScoreBack( int adwallType, int score, const char* accountName /* = ""*/ )
{
    /*
    if ( score > 0 ) {
        // 在这里增加元宝，并到服务器记录日志
        WorldPacket data(CMSG_ADWALL_ADD_YUANBAO,8);
        data << adwallType << score;
        sClient.getSession()->SendPacket(&data);
        
        if ( adwallType == ADWALL_TYPE_LIMEICPC )
        {
            {
                WorldPacket CPCdata(CMSG_NET_LIMEI_CPC_AD_COUNT, 30);
                CPCdata << accountName << (uint8)1 << (uint8)ADWALL_TYPE_LIMEICPC;
                sClient.getSession()->SendPacket( &CPCdata );
            }
        }
    }
     */
}

void AdWallInterface::onLeaveApp()
{
    //[[AdWallManager sharedInstance] onLeaveApp];
}

void AdWallInterface::onResumeApp()
{
    //[[AdWallManager sharedInstance] onResumeApp];
}

void AdWallInterface::initLimeiCPC()
{
    /*
    if ( !m_isInitLimeiCPC )
    {
        if ( sClient.m_adwallType == ADWALL_TYPE_LIMEICPC )
        {
            [[AdWallManager sharedInstance] initLimeiCPC];
        }
        
        m_isInitLimeiCPC = true;
    }
     */
}

void AdWallInterface::initTapjoy()
{
    [Tapjoy requestTapjoyConnect:Tapjoy_appID secretKey:Tapjoy_secretKey options:@{ TJC_OPTION_ENABLE_LOGGING : @(YES) }];
}
