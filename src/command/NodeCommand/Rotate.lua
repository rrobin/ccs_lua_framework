cc.RotateCommand = class("cc.RotateCommand", NodeCommand)
cc.RotateCommand.__index = cc.RotateCommand

function cc.RotateCommand:ctor(Node,rotation)
	self.super.ctor(self,Node)
	self._tips = "Rotate Node"
	self._delta = rotation - Node:getRotation()
end

function cc.RotateCommand:undo()
	self._object:setRotation(self._object:getRotation() - self._delta)
end

function cc.RotateCommand:redo()
	self._object:setRotation(self._delta+self._object:getRotation())
end

return cc.RotateCommand