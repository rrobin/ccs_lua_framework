#include "CCScriptAction.h"
#include "CCLuaEngine.h"


CCScriptAction* CCScriptAction::create(float d, int nScriptHandler)
{
	CCScriptAction* action = new CCScriptAction();
	action->initWithDuration(d);
	action->registerScriptHandler(nScriptHandler);
	action->autorelease();
	return action;
}

CCScriptAction::CCScriptAction()
{
	m_nScriptHandler = 0;
}

CCScriptAction::~CCScriptAction()
{
	if(m_nScriptHandler)
		ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_nScriptHandler);
}

void CCScriptAction::registerScriptHandler(int nScriptHandler)
{
	m_nScriptHandler = nScriptHandler;
}

void CCScriptAction::update(float time)
{
	auto scriptEngine = ScriptEngineManager::getInstance()->getScriptEngine();
	if(scriptEngine->getScriptType() == kScriptTypeLua)
	{
		auto pLuaEngine = LuaEngine::getInstance();
		auto pStack = pLuaEngine->getLuaStack();
		pStack->pushFloat(time);
		pStack->executeFunctionByHandler(m_nScriptHandler,1);
	}
}

ActionInterval* CCScriptAction::reverse() const
{
	return NULL;
}

ActionInterval* CCScriptAction::clone() const
{
	return NULL;
}