local AppDelegate = class("AppDelegate")
AppDelegate.__index = AppDelegate
AppDelegate.event = {}
AppDelegate.event.enterBackground = "APP_ENTER_BACKGROUND"
AppDelegate.event.enterforeground = "APP_ENTER_FOREGROUND"

function AppDelegate:ctor()
	local node = cc.Node:create()
	local eventDispatcher = node:getEventDispatcher()
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
	self:dispatchEvent({name = AppDelegate.event.enterBackground})
end

function AppDelegate:onEnterForeground()
	self:dispatchEvent({name = AppDelegate.event.enterforeground})
end

function AppDelegate:exit()
	cc.Director:getInstance():endToLua()
	if cc.platform == "windows" or cc.platform == "mac" then
    	os.exit()
    end
end

return AppDelegate