local AppDelegate = class("AppDelegate")
AppDelegate.__index = AppDelegate
AppDelegate.event = {}
AppDelegate.event.enterBackground = "APP_ENTER_BACKGROUND"
AppDelegate.event.enterforeground = "APP_ENTER_FOREGROUND"

function AppDelegate:ctor()
	local eventDispatcher = sharedDirector:getEventDispatcher()
    local customListenerBg =  cc.EventListenerCustom:create(AppDelegate.event.enterBackground,
     								handler(self, self.onEnterBackground))
    eventDispatcher:addEventListenerWithFixedPriority(customListenerBg, 1)
    local customListenerFg = cc.EventListenerCustom:create(AppDelegate.event.enterforeground,
     								handler(self, self.onEnterForeground))
    eventDispatcher:addEventListenerWithFixedPriority(customListenerFg, 1)
end

function AppDelegate:run()
end

function AppDelegate:onEnterBackground()
    cclog("onEnterBackground")
end

function AppDelegate:onEnterForeground()
	cclog("onEnterForeground")
end

function AppDelegate:exit()
	cc.Director:getInstance():endToLua()
	if cc.platform == "windows" or cc.platform == "mac" then
    	os.exit()
    end
end

return AppDelegate