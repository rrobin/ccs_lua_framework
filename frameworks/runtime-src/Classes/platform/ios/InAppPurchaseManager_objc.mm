//
//  InAppPurchaseManager.m
//  TestPayment
//
//  Created by mc815 on 13-2-2.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#import "InAppPurchaseManager_objc.h"
#include "InAppPurchaseInterface.h"

@implementation InAppPurchaseManager

static InAppPurchaseManager *iapManager = nil;

// Init
+ (InAppPurchaseManager *) sharedInstance
{
    @synchronized(self)     {
        if (!iapManager)
            iapManager = [[InAppPurchaseManager alloc] init];
    }
    return iapManager;
}

+ (id) alloc
{
    @synchronized(self)     {
        NSAssert(iapManager == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super alloc];
    }
    return nil;
}

- (void)requestProUpgradeProductData:(NSSet *)productIdentifiers
{
    NSLog( @"Query product by requestProUpgradeProductData" );
    //NSSet *productIdentifiers = [NSSet setWithObject:productId];
    productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
    // we will release the request object in the delegate callback  
}

// requestProUpgradeProductData call back
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSLog( @"Recv productsRequest" );
    for(SKProduct* productInfo in response.products)
    {
        NSString *localePrice = [self localizedPrice:productInfo];
        InAppPurchaseInterface::onQueryProductBack([productInfo.productIdentifier UTF8String], [localePrice UTF8String]);
    }
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@", invalidProductId);
        NSString *invalidPrice =  @"-1";
        InAppPurchaseInterface::onQueryProductBack([invalidProductId UTF8String], [invalidPrice UTF8String]);
        //[self messageNotify:@"get info failed!"];
    }
    // do something on finish
    InAppPurchaseInterface::onQueryProductFinish();
    // finally release the reqest we alloc/init’ed in requestProUpgradeProductData
    [productsRequest release];
}

- (NSString*)localizedPrice:(SKProduct*)product {
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:product.priceLocale];
    NSString *formattedString = [numberFormatter stringFromNumber:product.price];
    [numberFormatter release];
    return formattedString;
}

- (NSString *)encode:(const uint8_t *)input length:(NSInteger)length {
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData *data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t *output = (uint8_t *)data.mutableBytes;
    
    for (NSInteger i = 0; i < length; i += 3) {
        NSInteger value = 0;
        for (NSInteger j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger index = (i / 3) * 4;
        output[index + 0] =                    table[(value >> 18) & 0x3F];
        output[index + 1] =                    table[(value >> 12) & 0x3F];
        output[index + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[index + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] autorelease];
}

//add by zhoujy    
- (void)messageNotify:(NSString *)msg
{
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:msg
                                                       delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}

//  
// call this method once on startup
//  
- (void)initStore
{
    // restarts any purchases if they were interrupted last time the app was open  
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
    // get the product description (defined in early sections)
    // [self requestProUpgradeProductData];
}

//  
// call this before making a purchase  
//  
- (BOOL)canMakePurchases
{
    return [SKPaymentQueue canMakePayments];
}

//  
// kick off the upgrade transaction  
//  
- (void)purchaseProUpgrade:(NSString *)productId
{  
    SKPayment *payment = [SKPayment paymentWithProductIdentifier:productId];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

// add by zhoujy!we can trans receipt to server here  
- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
    NSString *receipt_base64 = [self encode:(uint8_t *)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];
    InAppPurchaseInterface::onPurchaseFinish((void*)[receipt_base64 UTF8String], 0);
}

//  
// removes the transaction from the queue and posts a notification with the transaction result  
//  
- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
    // remove the transaction from the payment queue.  
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    if (wasSuccessful) {
        //
    }
    else {
        // notify?
    }
}  

//  
// called when the transaction was successful  
//  
- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//  
// called when a transaction has been restored and and successfully completed  
//  
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction.originalTransaction];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//  
// called when a transaction has failed  
//  
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        // error!  
        [self finishTransaction:transaction wasSuccessful:NO];
        //NSString *errorInfo = transaction.error.localizedDescription;
        //[self messageNotify:errorInfo];
    }
    else
    {
        // this is fine, the user just cancelled, so don’t notify
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
    NSString *errorInfo = transaction.error.localizedDescription;
    InAppPurchaseInterface::onPurchaseFailed([errorInfo UTF8String]);
}

//  
// called when the transaction status is updated
//  
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
            default:
                break;
        }
    }
}

@end
