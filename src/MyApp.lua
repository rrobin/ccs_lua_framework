local MyApp = class("MyApp", cc.AppBase)
MyApp.__index = MyApp

function MyApp:ctor()
	MyApp.super.ctor(self)
	--require("MainScene").new()
	local scene = require("SceneEditor.ui.SceneEditorUI").new()--require("testScene").new()--require("SceneEditor.ui.SceneEditorUI").new()
    cc.runScene(scene)
end

function MyApp:onEnterBackground()
	cclog("onEnterBackground")
	--network.shutdown()
end

function MyApp:onEnterForeground()
	cclog("onEnterForeground")
	--network.reConnect()
end

return MyApp