#include "Purchase/InAppPurchaseInterface.h"

bool InAppPurchaseInterface::hasInit = false;
InAppPurchaseDelegate* InAppPurchaseInterface::_delegate = NULL;

bool InAppPurchaseInterface::initStore(InAppPurchaseDelegate* delegate)
{
	hasInit = true;
	assert(_delegate == NULL);
	_delegate = delegate;
	return true;
}

bool InAppPurchaseInterface::canMakePurchases()
{
	return false;
}

void InAppPurchaseInterface::queryProductInfo( const char** productIdArray, int32 size )
{
	
}

void InAppPurchaseInterface::onQueryProductBack( const char* productId, const char* price )
{

}

void InAppPurchaseInterface::makePurchase( const char* productId, int32 quantity )
{

}

void InAppPurchaseInterface::onPurchaseFinish( void* backData, int32 size )
{

}

void InAppPurchaseInterface::onPurchaseFailed( const char* desc )
{

}

void InAppPurchaseInterface::onQueryProductFinish()
{

}
