cc.OpacityCommand = class("cc.OpactiyCommand", NodeCommand)
cc.OpacityCommand.__index = cc.OpacityCommand

function cc.OpacityCommand:ctor(node,opacity)
	self.super.ctor(self,node)
	self._delta = node:getOpacity() - opacity
end

function cc.OpacityCommand:redo()
	local opacity = self._object:getOpacity()
	self._object:setOpacity(opacity - self._delta)
end

function cc.OpacityCommand:undo()
	local opacity = self._object:getOpacity()
	self._object:setOpacity(opacity+self._delta)
end

return cc.OpacityCommand