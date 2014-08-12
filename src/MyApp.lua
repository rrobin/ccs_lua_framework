local MyApp = class("MyApp", cc.AppBase)
MyApp.__index = MyApp

local SceneEditor = require("SceneEditor.ui.SceneEditorUI")
--local testScene = require("testScene")

function MyApp:ctor()
	MyApp.super.ctor(self)
	local scene = SceneEditor.new()
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