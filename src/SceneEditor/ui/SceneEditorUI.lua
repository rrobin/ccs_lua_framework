local SceneEditorUI = class("SceneEditorUI", function() return cc.Scene:create() end)
SceneEditorUI.__index = SceneEditorUI

require("ui.command.addTreeItem")
require("SceneEditor.command.DeleteLayer")
require("SceneEditor.command.DeleteScene")
require("SceneEditor.command.NewLayer")
require("SceneEditor.command.NewScene")
require("SceneEditor.command.RenameScene")

function SceneEditorUI:ctor()
	local layer = ccui.loadLayer("SceneEditor.ExportJson")
	self:addChild(layer)
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

	local delLayerBtn = layer:getChild("Button_11")
	delLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.removeLayer)})

	local tileLayerBtn = layer:getChild("TileBtn")
	tileLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.tileLayer)})

	local undoBtn = layer:getChild("UndoBtn")
	undoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.undo)})

	local redoBtn = layer:getChild("RedoBtn")
	redoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.redo)})

	local treePanel = layer:getChild("TreePanel")
	self._tree = require("ui.TreeControl").new(treePanel:getSize(),"MainTree",handler(self,self.touchTree))
	self._tree:pos(treePanel:pos())
	layer:removeChild(treePanel)
	layer:addChild(self._tree)
end
-- SceneOp
function SceneEditorUI:saveScene()
	-- body
end

function SceneEditorUI:loadScene()
end

function SceneEditorUI:newScene()
	local cmd1 = command.NewScene.new("新场景",960*2)
	local cmd2 = command.addTreeItem.new(self._tree,"新场景")
	local cmd3 = command.addTreeItem.new(self._tree,"背景","Root1")
	local cmd4 = command.addTreeItem.new(self._tree,"地板","Root1")
	local cmd5 = command.addTreeItem.new(self._tree,"前景","Root1")
	Do(cmd1,cmd2,cmd3,cmd4,cmd5)
end

function SceneEditorUI:delScene()
	local cmd1 = command.DeleteScene.new("新场景")
	local cmd2 = command.removeTreeItem.new(self._tree,self._selected)
	Do(cmd1,cmd2)
end

function SceneEditorUI:renameScene()
end

-- GroundLayerOp
function SceneEditorUI:addLayer()
	local cmd1 = command.NewLayer.new()
end

function SceneEditorUI:removeLayer()
end

function SceneEditorUI:renameLayer()
end

function SceneEditorUI:tileLayer()
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
	self._curScene = SceneManager:findScene(self._selected.value)
	cclog("selected:"..self._selected.name)
end

return SceneEditorUI