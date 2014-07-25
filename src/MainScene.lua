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
	self._sprite = cc.Sprite:create("1.png")
	layer:addChild(self._sprite)
	self._sprite:pos(cc.CENTER)
end

function MainScene:openFile(btn)
	--[[
	local filename = PlatformUtility:OpenFile("","CocoStudio UI File(*.ExportJson;*csb)\0*.ExportJson;*.csb\0")
	if filename ~= "" then
		cclog("filename : ".. filename)
	end
	]]
	local random = math.random()
    cclog("random = " .. random)
    local command = nil
    if random < 0.2 then
    	command = cc.MoveCommand.new(self._sprite,cc.pAdd(self._sprite:pos(),cc.p(20,10)))
    elseif random < 0.4 then
    	command = cc.RotateCommand.new(self._sprite,self._sprite:getRotation()+20)
    elseif random < 0.6 then
    	local scale = random / 0.6 * 1000 / 100
    	cclog("scale = " .. scale)
    	command = cc.ScaleCommand.new(self._sprite,scale)
    else
    	local axis = math.floor((random / 0.8 * 1000) % 3)
    	cclog("axis = "..axis)
    	command = cc.FlipCommand.new(self._sprite,axis)
    end
	if command == nil then return end
	DoCmd(command)
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
