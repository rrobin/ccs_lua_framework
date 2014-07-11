//
//  InAppPurchaseManager.h
//  TestPayment
//
//  Created by mc815 on 13-2-2.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#import <StoreKit/StoreKit.h>  

@interface InAppPurchaseManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
{
    SKProductsRequest *productsRequest;
}

+ (InAppPurchaseManager*) sharedInstance;

- (void)requestProUpgradeProductData:(NSSet *)productIdentifiers;

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

- (void)initStore;

- (BOOL)canMakePurchases;

- (void)purchaseProUpgrade:(NSString *)productId;

- (void)messageNotify:(NSString *)msg;

@end
