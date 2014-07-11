#pragma once
#include "InAppPurchaseInterface.h"
#include <vector>

enum
{
	IAP_EVENT_QUERY_FINISH,
	IAP_EVENT_PURCHASE_FINISH,
	IAP_EVENT_PURCHASE_FAILED,
};

struct ProductInfo		// 商品信息
{
	std::string productId;
	std::string price;
};

class InAppPurchaseDelegate
{
public:
	InAppPurchaseDelegate();
	~InAppPurchaseDelegate(){ unregisterScriptHandler(); }
	virtual void addProduct(const char* productId, const char* price);
	virtual void queryProducts();
	virtual void purchase(unsigned int index);

	const char* getPrice(unsigned int index);

	virtual bool queryProductFinish();
	virtual void onQueryProductFinish();
	virtual void onPurchaseFinish( void* content);
	virtual void onPurchaseFailed( const char* desc );
	void	registerScriptHandler(int nHandler);
	void	unregisterScriptHandler();
	void	clearProduct();
private:
	std::vector<ProductInfo>	m_Products;
	int							m_ScriptHandler;
	bool						m_bQuery;
};