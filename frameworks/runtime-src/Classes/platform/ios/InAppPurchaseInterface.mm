#include "InAppPurchaseInterface.h"
#include "InAppPurchaseDelegate.h"
#include "InAppPurchaseManager_objc.h"

bool InAppPurchaseInterface::hasInit = false;
InAppPurchaseDelegate* InAppPurchaseInterface::_delegate = NULL;

bool InAppPurchaseInterface::initStore(InAppPurchaseDelegate* delegate)
{
	hasInit = true;
    [[InAppPurchaseManager sharedInstance] initStore];
    _delegate = delegate;
	return true;
}

bool InAppPurchaseInterface::canMakePurchases()
{
	return [[InAppPurchaseManager sharedInstance] canMakePurchases];
}

void InAppPurchaseInterface::queryProductInfo( const char** productIdArray, int32 size )
{
    if (size > 0) {
        NSMutableSet *muSet = [NSMutableSet setWithCapacity:size];
        for (int i = 0; i < size; ++i) {
            [muSet addObject:[NSString stringWithUTF8String:productIdArray[i]]];
        }
        [[InAppPurchaseManager sharedInstance] requestProUpgradeProductData:muSet];
    }
	
}

void InAppPurchaseInterface::onQueryProductBack( const char* productId, const char* price )
{
    _delegate->addProduct(productId,price);
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
    [[InAppPurchaseManager sharedInstance] purchaseProUpgrade: [NSString stringWithUTF8String:productId]];
}

void InAppPurchaseInterface::onPurchaseFinish( void* backData, int32 size )
{
    _delegate->onPurchaseFinish( backData );
}

void InAppPurchaseInterface::onPurchaseFailed( const char* desc )
{
    _delegate->onPurchaseFailed( desc );
}
