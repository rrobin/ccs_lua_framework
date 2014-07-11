#pragma once

#include "cocos2d.h"
USING_NS_CC;

class CCScriptAction : public ActionInterval
{
public:
	CCScriptAction();
	virtual ~CCScriptAction();
	static CCScriptAction* create(float d, int nScriptHandler);
	
	void registerScriptHandler(int nScriptHandler);

	virtual void update(float time);

	virtual ActionInterval* reverse()const override;
	virtual ActionInterval* clone()const override;
private:
	int	m_nScriptHandler;
};