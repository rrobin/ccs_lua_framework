#include "adwall/AdWallInterface.h"

bool AdWallInterface::init( int adWallType )
{
	return true;
}

bool AdWallInterface::canUseAdWall()
{
	return false;
}

void AdWallInterface::setNetAccountName( const char* accountName )
{
	
}

void AdWallInterface::enterAdWall()
{

}

void AdWallInterface::queryScore()
{

}

void AdWallInterface::onQueryScoreBack( int score )
{

}

void AdWallInterface::reduceScore( int score )
{

}

void AdWallInterface::onReduceScoreBack( int adwallType, int score, const char* accountName /* = */ )
{

}

void AdWallInterface::onLeaveApp()
{

}

void AdWallInterface::onResumeApp()
{

}

void AdWallInterface::initLimeiCPC()
{

}

void AdWallInterface::initTapjoy()
{

}