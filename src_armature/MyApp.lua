local MyApp = class("MyApp", cc.AppBase)
MyApp.__index = MyApp

local testScene = require("testScene")

function MyApp:ctor()
	MyApp.super.ctor(self)
	--[[ 
	local scene = previewScene.new()
	local filename = "E:/Tools/3.xEditor/newScene.sce"
	scene:loadSce(filename)

    -- ]] 
    local scene = testScene.new()
	--[[local lastProj = EditorConfig:getLastProj()
	if lastProj then
		ProjectManager:load(lastProj.workpath)
	else
		ProjectManager:newProject()
		EditorConfig:openProj(ProjectManager._project)
	end]]
	--ProjectManager:newProject()
	--EditorConfig:openProj(ProjectManager._project)
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