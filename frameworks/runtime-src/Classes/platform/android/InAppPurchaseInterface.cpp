#include "InAppPurchaseInterface.h"
#include "InAppPurchaseDelegate.h"
#include "alipay.h"
#include "NetConnection.h"

bool InAppPurchaseInterface::hasInit = false;
InAppPurchaseDelegate* InAppPurchaseInterface::_delegate = NULL;

#include <stdlib.h>

bool InAppPurchaseInterface::initStore(InAppPurchaseDelegate* delegate)
{
	hasInit = true;
	assert(_delegate == NULL);
	_delegate = delegate;
	return true;
}

bool InAppPurchaseInterface::canMakePurchases()
{
	return true;
}

void InAppPurchaseInterface::queryProductInfo( const char** productIdArray, int32 size )
{
	aliProduct.clear();
	char* str = new char[1024];
	for ( int32 i = 0; i < size; ++i )
	{
		productInfo info;
		info.subject = productIdArray[i];
		sprintf( str, "body_%d", i );
		info.body = str;
		//sprintf( str, "%.2f", (float)(i+1)/100 );
		info.price = "";
		aliProduct.push_back( info );

		CCLog( CCString::createWithFormat( "subject-%s, body-%s, price-%s", info.subject.c_str(), info.body.c_str(), info.price.c_str() )->getCString() );
		//onQueryProductBack( info.subject.c_str(), info.price.c_str() );
	}
	delete str;
	
#ifdef VER_ID
	WorldPacket SendPacket(0xA38,200);
	SendPacket << (uint32)VER_ID;
	sNetConn.SendPacket(&SendPacket);
#else
	CCLog("unknown VER_ID");
#endif
}

void InAppPurchaseInterface::onQueryProductBack( const char* productId, const char* price )
{
	InAppPurchaseInterface::_delegate->addProduct( productId, price );
	for( uint32 i = 0; i < aliProduct.size(); ++i )
	{
		if ( aliProduct[i].subject == productId )
			aliProduct[i].price = price;
	}
}

void InAppPurchaseInterface::onQueryProductFinish()
{
    if ( _delegate->queryProductFinish() ) {
        _delegate->onQueryProductFinish();
    }
    else
    {
        CCLog("query app store Product finish error!");
    }
}

void InAppPurchaseInterface::makePurchase( const char* productId, int32 quantity )
{
	CCLog( "InAppPurchaseInterface::makePurchase" );

	alipay* lpAlipay = new alipay;
	if ( !lpAlipay )
	{
		assert( false );
		return ;
	}

	int result;
	string productstr = productId;
	for ( size_t i = 0; i < aliProduct.size(); ++i )
	{
		if ( aliProduct[i].subject == productstr )
		{
			result = lpAlipay->alipayProfuct( aliProduct[i] );
			break;
		}
	}
	SAFE_DELETE( lpAlipay );

// 	CCLog( "InAppPurchaseInterface::makePurchase-result-%s", result );
// 	if ( result == 9000 )
// 		onPurchaseFinish( NULL, 0 );
// 	else
// 		onPurchaseFailed( "alipay Failed" );
}

void InAppPurchaseInterface::onPurchaseFinish( void* backData, int32 size )
{
	_delegate->onPurchaseFinish( backData );
}

void InAppPurchaseInterface::onPurchaseFailed( const char* desc )
{
	_delegate->onPurchaseFailed( desc );
}
