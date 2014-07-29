local SceneEditorUI = class("SceneEditorUI", function() return cc.Scene:create() end)
SceneEditorUI.__index = SceneEditorUI

require("ui.command.addTreeItem")
require("SceneEditor.command.DeleteLayer")
require("SceneEditor.command.DeleteScene")
require("SceneEditor.command.NewLayer")
require("SceneEditor.command.NewScene")
require("SceneEditor.command.RenameScene")
require("SceneEditor.command.modifyObject")

function SceneEditorUI:ctor()
	local layer = ccui.loadLayer("SceneEditor.ExportJson")
	self:addChild(layer)
	self._layer = layer
	local newSceneBtn = layer:getChild("NewSceneBtn")
	newSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.newScene)})

	local openSceneBtn = layer:getChild("OpenSceneBtn")
	openSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.loadScene)})

	local saveSceneBtn = layer:getChild("SaveSceneBtn")
	saveSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.saveScene)})

	local delSceneBtn = layer:getChild("DelSceneBtn")
	delSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.delScene)})

	local newLayerBtn = layer:getChild("NewLayerBtn")
	newLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.addLayer)})

	local delLayerBtn = layer:getChild("DelLayerBtn")
	delLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.removeLayer)})

	local tileLayerBtn = layer:getChild("TileBtn")
	tileLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.tileLayer)})

	local undoBtn = layer:getChild("UndoBtn")
	undoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.undo)})

	local redoBtn = layer:getChild("RedoBtn")
	redoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.redo)})

	local addObjBtn = layer:getChild("AddObjBtn")
	addObjBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.addObject)})

	local delObjBtn = layer:getChild("DelObjBtn")
	delObjBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.removeObject)})

	self._previewWindow = layer:getChild("preview_Win")

	self:initObjectPanel(layer)

	local treePanel = layer:getChild("TreePanel")
	self._tree = require("ui.TreeControl").new(treePanel:getSize(),"MainTree",handler(self,self.touchTree))
	local Layout = treePanel:getLayoutParameter()
	self._tree:setLayoutParameter(Layout)
	--self._tree:pos(treePanel:pos())
	layer:getChild("ScenePanel"):removeChild(treePanel)
	layer:getChild("ScenePanel"):addChild(self._tree)

	self._curScene = {data=0,ui=0,treeNode = 0}
	self._curGround = {data=0,ui=nil,treeNode = 0,name=""}
	self._curLayer = {data=0,ui=0,treeNode = 0}
	self._Grounds = {}
	self._layers = {}
	self._ui = {}
	self._object = nil
end

function SceneEditorUI:initObjectPanel()
	--local filename = layer:getChild("ObjFile_Label")
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local pos = self._object:pos()
			pos.x = tonumber(widget:getString())
			cclog("detach_with_ime")
			self._object:pos(pos)
		end})
	--Pos_x:setText("")
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local pos = self._object:pos()
			pos.y = tonumber(widget:getString())
			self._object:pos(pos)
		end})
	--Pos_y:setText("")
	local Scale_x = self._layer:getChild("Scale_X")
	Scale_x:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local scale = tonumber(widget:getString())
			self._object:setScaleX(scale)
		end})
	--Scale_x:setText("")
	local Scale_y = self._layer:getChild("Scale_Y")
	Scale_y:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local scale = tonumber(widget:getString())
			self._object:setScaleY(scale)
		end})
	--Scale_y:setText("")
	local Rotate = self._layer:getChild("Rotate")
	Rotate:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local rotate = tonumber(widget:getString())
			self._object:setRotation(rotate)
		end})
	--Rotate:setText("")
	local H_FlipBtn = self._layer:getChild("H_FlipBtn")
	H_FlipBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(button)
			local b = false 
			if button:isBright() ~= self._object:isFlippedX() then
				b = true
			end
			button:setBright(self._object:isFlippedX())
			self._object:setFlippedX(b)
		end})
	local V_FlipBtn = self._layer:getChild("V_FlipBtn")
	V_FlipBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(button)
			local b = false 
			if button:isBright() ~= self._object:isFlippedY() then
				b = true
			end
			button:setBright(self._object:isFlippedY())
			self._object:setFlippedY(b)
		end})
	local Slider_51 = self._layer:getChild("Slider_51")
	local OpacityLabel = self._layer:getChild("OpacityLabel")
	Slider_51:addSliderEvent(
		function(slider)
			local percent = slider:getPercent()
			local opacity = math.floor(255*percent/100)
			self._object:setOpacity(opacity)
			OpacityLabel:setString(tostring(opacity))
		end)
	local ApplyBtn = self._layer:getChild("ApplyBtn")
	ApplyBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function()
			local pos = cc.p(0,0)
			pos.x = tonumber(Pos_x:getString())
			pos.y = tonumber(Pos_y:getString())
			self._object:pos(pos)
			local scale = {x=1,y=1}
			scale.x = tonumber(Scale_x:getString())
			scale.y = tonumber(Scale_y:getString())
			self._object:setScaleX(scale.x)
			self._object:setScaleY(scale.y)
			local rotate = tonumber(Rotate:getString())
			self._object:setRotation(rotate)
		end})
end

function SceneEditorUI:setupObjectPanel(SceneObject)
	local filename = self._layer:getChild("ObjFile_Label")
	filename:setString(SceneObject.Filename)
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:setText(SceneObject.Pos.x)
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:setText(SceneObject.Pos.y)
	local Scale_x = self._layer:getChild("Scale_X")
	Scale_x:setText(SceneObject.Scale.x)
	local Scale_y = self._layer:getChild("Scale_Y")
	Scale_y:setText(SceneObject.Scale.y)
	local Rotate = self._layer:getChild("Rotate")
	Rotate:setText(SceneObject.Rotate)
	local H_FlipBtn = self._layer:getChild("H_FlipBtn")
	H_FlipBtn:setBright(SceneObject.FlipX==false)
	local V_FlipBtn = self._layer:getChild("V_FlipBtn")
	V_FlipBtn:setBright(SceneObject.FlipX==false)
	local Slider_51 = self._layer:getChild("Slider_51")
	Slider_51:setPercent(SceneObject.Opacity)
	local OpacityLabel = self._layer:getChild("OpacityLabel")
	OpacityLabel:setString(tostring(SceneObject.Opacity))
end

-- SceneOp
function SceneEditorUI:saveScene()
	-- body
end

function SceneEditorUI:loadScene()
end

function SceneEditorUI:newScene()
	local scene = SceneManager:findScene("新场景")
	if scene then return end 
	scene = SceneManager:addScene("新场景",960*2)
	local parent = self._tree:addItem("新场景")
	self._Grounds[self._tree:addItem("背景",parent)] = scene._BackGround
	self._Grounds[self._tree:addItem("地板",parent)] = scene._Floor
	self._Grounds[self._tree:addItem("前景",parent)] = scene._FrontGround
	self._tree:extend(parent)
	self:addSceneUI(960*2)
	--[[
	local cmd1 = command.NewScene.new("新场景",960*2)
	local cmd2 = command.addTreeItem.new(self._tree,"新场景")
	local cmd3 = command.addTreeItem.new(self._tree,"背景","Root1")
	local cmd4 = command.addTreeItem.new(self._tree,"地板","Root1")
	local cmd5 = command.addTreeItem.new(self._tree,"前景","Root1")
	Do(cmd1,cmd2,cmd3,cmd4,cmd5)
	]]
end

function SceneEditorUI:delScene()
	SceneManager:removeScene("新场景")
	self._tree:removeItem(self._curScene)
	self._curScene = {data=0,ui=0,treeNode = 0}
	self._curGround = {data=0,ui=0,treeNode = 0}
	--[[
	local cmd1 = command.DeleteScene.new("新场景")
	local cmd2 = command.removeTreeItem.new(self._tree,self._selected)
	Do(cmd1,cmd2)
	]]
end

function SceneEditorUI:renameScene()
end

-- GroundLayerOp
function SceneEditorUI:addLayer()
	if self._curGround.name == "背景" then
		--self._curGround.data:addLayer()
		local name = "层"..self._curGround.data._count+1
		local cmd1 = command.NewLayer.new(name,self._curGround.data)
		local cmd2 = command.addTreeItem.new(self._tree,name,self._curGround.treeNode)
		Do(cmd1,cmd2)
		local s = self:getSize()
		s.width = self._curScene.data._width/960*s.width
		local panel = ccui.panel({size = s})
		self._layers[self._curGround.name..name] = panel
		self._curGround.ui:addChild(panel)
	end
end

function SceneEditorUI:removeLayer()
end

function SceneEditorUI:renameLayer()
end

function SceneEditorUI:tileLayer()
end

-- SceneObjectOp
function SceneEditorUI:addObject()
	local filename = PlatformUtility:OpenFile("C:\\","Png(*.png)\0*.png\0")
	local name = self._curLayer.data._name
	cclog("cur layer name:"..name)
	local sprite = ccui.image({image=filename})
	self._layers[self._curGround.name..name]:addChild(sprite)
	local objInfo = clone(SceneObject)
	objInfo.Filename = filename
	objInfo.Pos = cc.CENTER
	self:setupObjectPanel(objInfo)
	sprite:pos(cc.CENTER)
	sprite:addTouchEvent({[ccui.TouchEventType.began] = handler(self,self.touchSprite),
		[ccui.TouchEventType.moved] = handler(self,self.moveSprite),
		[ccui.TouchEventType.ended] = handler(self,self.stopSprite),
		[ccui.TouchEventType.canceled] = handler(self,self.stopSprite),
		})
	self._object = sprite
	self._curLayer.data:addObject(objInfo)
	self._object.data = objInfo
end

function SceneEditorUI:touchSprite(image)
	self._spos = image:getTouchBeganPosition()
	self._object.spos = self._object:pos()
end

function SceneEditorUI:moveSprite(image)
	local mpos =image:getTouchMovePosition()
	local offset = cc.pSub(mpos,self._spos)
	local pos = cc.pAdd(self._object.spos,offset)
	self._object:pos(pos)
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:setText(string.format("%d",math.floor(pos.x)))
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:setText(string.format("%d",math.floor(pos.y)))
end

function SceneEditorUI:stopSprite(image)
	local epos = image:getTouchEndPosition()
	local pos = cc.pAdd(self._object.spos,cc.pSub(epos,self._spos))
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:setText(string.format("%d",math.floor(pos.x)))
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:setText(string.format("%d",math.floor(pos.y)))
	local cmd1 = cc.MoveCommand.new(self._object,pos)
	local cmd2 = command.modifyObject.new(self._object.data,1,pos)
	Do(cmd1,cmd2)
end

function SceneEditorUI:removeObject()
end

--CommondOp
function SceneEditorUI:undo()
	Undo()
end

function SceneEditorUI:redo()
	Redo()
end

function SceneEditorUI:touchTree(tree_name)
	cclog("tree_name:"..tree_name)
	self._selected = self._tree:getSelectedItem()
	self._selectedType = -1
	local node = self._selected
	while node ~= nil
		do
		 if node.P == nil then
		 	self._curScene.data = SceneManager:findScene(node.value)
		 	self._curScene.treeNode = node.name
		 	cclog("curScene:"..node.value)
		 end
		 if self._Grounds[node.name] then
		 	if self._curGround.ui ~= nil then
		 		self._curGround.ui:setVisible(false)
		 	end
		 	self._curGround.data = self._Grounds[node.name]
		 	self._curGround.treeNode = node.name
		 	self._curGround.ui = self._ui[node.value]
		 	self._curGround.name = node.value
		 	self._curGround.ui:setVisible(true)
		 	cclog("curGround:"..node.value)
		 end
		 node = node.P
		 self._selectedType = self._selectedType + 1
	end

	if self._selectedType == 2 then
		self._curLayer.data = self._curGround.data:getLayer(self._selected.value)
		self._curLayer.treeNode = self._selected.name
	elseif self._selectedType > 2 then

	end

	cclog("selectedType:"..self._selectedType)
end

-- for preview
function SceneEditorUI:addSceneUI(width)
	self._previewWindow:removeAllChildren()
	local winSize = self._previewWindow:getSize()
	local inner = winSize
	inner.w = width/960*winSize.width
	local scrollview = ccui.scrollView({size = winSize,innerSize = inner,direction = ccui.ScrollViewDir.horizontal})
	self._previewWindow:addChild(scrollview,1,0)
	local panel = ccui.panel({size=inner}) --,colorType = ccui.LayoutBackGroundColorType.gradient,color = cc.c3b(255,0,0),endColor = cc.c3b(125,0,0)
	self._ui["背景"] = panel
	panel:setVisible(false)
	scrollview:addChild(panel,1,1)
	panel = ccui.panel({size=inner})--,colorType = ccui.LayoutBackGroundColorType.gradient,color = cc.c3b(0,255,0),endColor = cc.c3b(0,125,0)
	self._ui["地板"] = panel
	panel:setVisible(false)
	scrollview:addChild(panel,2,2)
	panel = ccui.panel({size=inner}) --,colorType = ccui.LayoutBackGroundColorType.gradient,color = cc.c3b(0,0,255),endColor = cc.c3b(0,0,125)
	self._ui["前景"] = panel
	panel:setVisible(false)
	scrollview:addChild(panel,3,3)
end  

function SceneEditorUI:addLayerUI()
end

return SceneEditorUI