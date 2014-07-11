#include "alipay.h"
#include "platform/android/jni/JniHelper.h"
#include "Purchase/InAppPurchaseInterface.h"
#include "NetConnection.h"

vector<productInfo> aliProduct;

class alipay_java
{
public:
	int alipayProduct_java( productInfo info )
	{
		JniMethodInfo methodInfo;
		if ( !JniHelper::getStaticMethodInfo( methodInfo, "com/szlsCard/uber/com/alipayCallByC", "getAlipayResult", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I" ) )
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return 0;
		}

		CCLOG( "call alipayProduct_java" );

		jstring subject	= methodInfo.env->NewStringUTF( info.subject.c_str() );
		jstring body	= methodInfo.env->NewStringUTF( info.body.c_str() );
		jstring price	= methodInfo.env->NewStringUTF( info.price.c_str() );

		//jstring result = static_cast<jstring>( methodInfo.env->CallStaticObjectMethod( methodInfo.classID, methodInfo.methodID, subject, body, price ) );
		//string myResult = methodInfo.env->GetStringUTFChars( result, NULL );

		jint result = methodInfo.env->CallStaticIntMethod( methodInfo.classID, methodInfo.methodID, subject, body, price );

		CCLOG( "alipayProduct_java CallStaticIntMethod:result-%d", (int)result );

		methodInfo.env->DeleteLocalRef(subject);
		methodInfo.env->DeleteLocalRef(body);
		methodInfo.env->DeleteLocalRef(price);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

		return (int)result;
	}

	void backResult( int result, jstring trade_no )
	{
		JniMethodInfo methodInfo;
		if ( !JniHelper::getStaticMethodInfo( methodInfo, "com/szlsCard/uber/com/alipayCallByC", "getAlipayResult", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I" ) )
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return ;
		}

		string out_trade_no = methodInfo.env->GetStringUTFChars( trade_no, NULL );

		methodInfo.env->DeleteLocalRef(methodInfo.classID);

		CCLOG( "backResult-%d, out_trade_no-%s", result, out_trade_no.c_str() );
		// result=9000 pay success
		if ( result == 9000 )
		{
			InAppPurchaseInterface::onPurchaseFinish( (void*)out_trade_no.c_str(), 0 );

// 			CCLOG( "send package 0xA30" );
// 			WorldPacket data( 0xA30, strlen( out_trade_no.c_str() ) );
// 			data << out_trade_no;
// 			sNetConn.SendPacket( &data );
		}
		else 
			InAppPurchaseInterface::onPurchaseFailed( CCString::createWithFormat( "backResult-%d, out_trade_no-%s, ali buy failed!", result, out_trade_no.c_str() )->getCString() );
	}
	
};

static alipay_java& shareAlipayJava()
{
	static alipay_java alipayJava;
	return alipayJava;
}

int alipay::alipayProfuct( productInfo info )
{
	int res = shareAlipayJava().alipayProduct_java( info );
	return res;
}


// this method is called by alipayCallByC
extern "C"
{
	// com.szlsCard.uber.com  alipayCallByC
	// result is the alipay pay result
	JNIEXPORT void JNICALL Java_com_szlsCard_uber_com_alipayCallByC_nativeBackResult(JNIEnv*  env, jobject thiz, int result, jstring trade_no)
	{
		shareAlipayJava().backResult( result, trade_no );
	}
};