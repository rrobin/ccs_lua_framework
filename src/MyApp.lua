local MyApp = class("MyApp", cc.AppBase)
MyApp.__index = MyApp

function MyApp:ctor()
	MyApp.super.ctor(self)
end

function MyApp:onEnterBackground()
	cclog("onEnterBackground")
	network.shutdown()
end

function MyApp:onEnterForeground()
	cclog("onEnterForeground")
	network.reConnect()
end

return MyApp