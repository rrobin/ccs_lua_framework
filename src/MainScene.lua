local MainScene = class("MainScene",function()
 	return cc.Scene:create() 
end)
MainScene.__index = MainScene

function MainScene:ctor()
	local layer = ccui.loadLayer("MainScene.ExportJson")
	self:addChild(layer)
	local fileBtn = layer:getChild("OpenFileBtn")
	fileBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.openFile)})
	local undoBtn = layer:getChild("UndoBtn")
	undoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.testUndo)})
	local redoBtn = layer:getChild("RedoBtn")
	redoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.testRedo)})
	--[[
	self._sprite = cc.Sprite:create("denglu/NARUTO_denglu_10101.png")
	self._sprite:setShader("outline")
	self._sprite:setUniform("u_outlineColor",{x=1.0, y=0.2, z=0.3})
	self._sprite:setUniform("u_radius",0.01)
	self._sprite:setUniform("u_threshold",1.75)
	layer:addChild(self._sprite)
	self._sprite:pos(cc.CENTER)
	]]
	local s = layer:getChild("Panel_20"):getSize()
	local scrollview = ccui.scrollView({size = cc.size(s.width,640),innerSize = cc.size(960*3,640),direction = ccui.ScrollViewDir.both
		,colorType = ccui.LayoutBackGroundColorType.solid,color = cc.c3b(0,0,255)})
	self._scrollview = scrollview
	layer:getChild("Panel_20"):addChild(scrollview,0)
end

function MainScene:openFile(btn)
	local filename = PlatformUtility:OpenFile("","CocoStudio UI File(*.ExportJson;*csb)\0*.ExportJson;*.csb\0")
	if filename ~= "" then
		cclog("filename : ".. filename)
	end

	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(filename)
	local name = string.ipextension(string.ippath(filename))
	local armature = ccs.Armature:create(name)
	self._scrollview:addChild(armature)
	local size = armature:getSize()
	armature:pos(cc.p(0,size.height/2))
end

function MainScene:testUndo(btn)
	Undo()
end

function MainScene:testRedo(btn)
	Redo()
end

function MainScene:onEnter()
end

return MainScene
