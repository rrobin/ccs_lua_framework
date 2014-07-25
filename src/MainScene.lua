local MainScene = class("MainScene",function()
 	return cc.Scene:create() 
end)
MainScene.__index = MainScene

function MainScene:ctor()
	local layer = ccui.loadLayer("MainScene.ExportJson")
	self:addChild(layer)
	local fileBtn = layer:getChild("OpenFileBtn")
	fileBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.openFile) })
end

function MainScene:openFile(btn)
	local filename = PlatformUtility:OpenFile("","CocoStudio UI File(*.ExportJson;*csb)\0*.ExportJson;*.csb\0")
	if filename ~= "" then
		cclog("filename : ".. filename)
	end
end

function MainScene:onEnter()
end

return MainScene
