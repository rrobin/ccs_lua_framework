#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "luabinding/game_luabinding.h"
#include "luabinding/game_manual.h"
#include "game_lua_extensions.h"
USING_NS_CC;
using namespace CocosDenshion;

void keyEventCallback(EventKeyboard::KeyCode code, Event *event)
{ 
	typedef EventKeyboard::KeyCode KeyCode;
	switch(code)
	{ 
	case KeyCode::KEY_BACKSPACE:
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 
		IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
#else 
		Director::getInstance()->end();
#endif 
		break; 
	case KeyCode::KEY_DELETE:
		IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
		break;
// 	case KeyCode::KEY_RETURN:
// 		IMEDispatcher::sharedDispatcher()->detachDelegateWithIME();
	}
};

enum
{
    FINISH_LAUNCHING,
    ENTER_BACKGROUND,
    ENTER_FOREGROUND,
    EVENT_NUMS,
};

const char* AppEvent[EVENT_NUMS] =
{
    "APP_FINISH_LAUNCHING",
    "APP_ENTER_BACKGROUND",
    "APP_ENTER_FOREGROUND",
};

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

#define  LOAD_PRECOMPILE

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::createWithRect("Bin", Rect(0,0,960,640));
		director->setOpenGLView(glview);
	}

    glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	CCFileUtils::sharedFileUtils()->addSearchPath("src/");

    // register lua engine
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
	auto pStack = engine->getLuaStack();
	auto L = pStack->getLuaState();
	tolua_game_open(L);
	register_all_game_manual(L);
	game_lua_extensions(L);
//#undef COCOS2D_DEBUG
#ifdef LOAD_PRECOMPILE
#ifndef COCOS2D_DEBUG
	pStack->loadChunksFromZIP("game.bat");
#endif
	pStack->loadChunksFromZIP("framework_precompiled.zip");
#endif
	if(engine->executeScriptFile("main") != 0)
		return false;
//#define COCOS2D_DEBUG
	EventListenerKeyboard *listener = EventListenerKeyboard::create(); 
	listener->onKeyReleased = keyEventCallback; 
	director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1); 

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->dispatchCustomEvent(AppEvent[ENTER_BACKGROUND]);
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->dispatchCustomEvent(AppEvent[ENTER_FOREGROUND]);
}
