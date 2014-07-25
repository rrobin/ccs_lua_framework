cc.RotateCommand = class("cc.RotateCommand", NodeCommand)
cc.RotateCommand.__index = cc.RotateCommand

function cc.RotateCommand:ctor(Node,rotation)
	self.super.ctor(self,Node)
	self._tips = "Rotate a Node"
	self._offset = Node:getRotation() - rotation
end

function cc.RotateCommand:undo()
	self._object:setRotation(self._object:getRotation() - self._offset)
end

function cc.RotateCommand:redo()
	self._object:setRotation(self._offset+self._object:getRotation())
end

return cc.RotateCommand