#include "InAppPurchaseDelegate.h"
#include "CCLuaEngine.h"
USING_NS_CC;

InAppPurchaseDelegate::InAppPurchaseDelegate()
{
	m_ScriptHandler = 0;
	m_bQuery = false;
	if(!InAppPurchaseInterface::hasInit)
		InAppPurchaseInterface::initStore(this);
}

void InAppPurchaseDelegate::addProduct(const char* productId, const char* price)
{
	std::vector<ProductInfo>::iterator iter = m_Products.begin();
	for(;iter != m_Products.end(); ++iter)
	{
		if(iter->productId.compare(productId) == 0)
			break;
	}

	if( iter == m_Products.end() )
	{
		ProductInfo info;
		info.productId = productId;
		info.price = price;
		m_Products.push_back(info);
	}
	else
	{
		iter->price = price;
	}
}

bool InAppPurchaseDelegate::queryProductFinish()
{
	bool bRet = true;
	for ( std::vector<ProductInfo>::const_iterator it = m_Products.begin(); it != m_Products.end(); ++it )
	{
		if ( (*it).price.length() == 0 )
		{
			bRet = false;
			break;
		}
	}
	return bRet;
}

void InAppPurchaseDelegate::onQueryProductFinish()
{
	m_bQuery = false;
	if(m_ScriptHandler)
	{
		auto stack = LuaEngine::getInstance()->getLuaStack();
		auto state = stack->getLuaState();

		if(state)
		{
			stack->pushInt(IAP_EVENT_QUERY_FINISH);
			stack->executeFunctionByHandler(m_ScriptHandler,1);
		}
	}
}

void InAppPurchaseDelegate::onPurchaseFinish(void* content)
{
	if(m_ScriptHandler)
	{
		auto stack = LuaEngine::getInstance()->getLuaStack();
		auto state = stack->getLuaState();

		if(state)
		{
			const char* str = (const char*)content;
			stack->pushInt(IAP_EVENT_PURCHASE_FINISH);
            if (str != NULL ) {
                stack->pushString(str);
            }else
                stack->pushNil();
			stack->executeFunctionByHandler(m_ScriptHandler,2);
		}
	}
}

void InAppPurchaseDelegate::onPurchaseFailed( const char* desc )
{
	if(m_ScriptHandler)
	{
		auto stack = LuaEngine::getInstance()->getLuaStack();
		auto state = stack->getLuaState();

		if(state)
		{
			stack->pushInt(IAP_EVENT_PURCHASE_FAILED);
			stack->pushString(desc);
			stack->executeFunctionByHandler(m_ScriptHandler,2);
		}
	}
}

void InAppPurchaseDelegate::registerScriptHandler(int nHandler)
{
	m_ScriptHandler = nHandler;
}

void InAppPurchaseDelegate::unregisterScriptHandler()
{
	m_ScriptHandler = 0;
}

void InAppPurchaseDelegate::clearProduct()
{
	m_Products.clear();
}

void InAppPurchaseDelegate::queryProducts()
{
	if(m_Products.empty() || m_bQuery) return;
	const char** productIdArray = new const char*[m_Products.size()];
	for(size_t i = 0; i < m_Products.size(); ++i)
		productIdArray[i] = m_Products[i].productId.c_str();
	InAppPurchaseInterface::queryProductInfo( productIdArray, m_Products.size() );
	m_bQuery = true;
}

void InAppPurchaseDelegate::purchase(unsigned int index)
{
	if(index >= m_Products.size())
	{
		assert(index < m_Products.size());
		return;
	}
	if(InAppPurchaseInterface::canMakePurchases())
		InAppPurchaseInterface::makePurchase(m_Products[index].productId.c_str(),1);
}

const char* InAppPurchaseDelegate::getPrice(unsigned int index)
{
	if(index < m_Products.size())
		return m_Products[index].price.c_str();
	else
	{
#ifndef WIN32
		assert(index < m_Products.size());
#endif
		return NULL;
	}
}