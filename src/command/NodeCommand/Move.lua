cc.MoveCommand = class("cc.MoveCommand", NodeCommand)
cc.MoveCommand.__index = cc.MoveCommand

function cc.MoveCommand:ctor(Node,pos)
	self.super.ctor(self,Node)
	self._tips = "Move a Node"
	self._offset = cc.pSub(Node:pos(),pos)
end

function cc.MoveCommand:redo()
	local pos = self._object:pos()
	local dst = cc.pAdd(pos,self._offset)
	self._object:pos(dst)
end

function cc.MoveCommand:undo()
	local pos = self._object:pos()
	local dst = cc.pSub(pos,self._offset)
	self._object:pos(dst)
end

return cc.MoveCommand