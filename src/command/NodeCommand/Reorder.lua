cc.reorderCommand = class("cc.reorderCommand", NodeCommand)
cc.reorderCommand.__index = cc.reorderCommand

function cc.reorderCommand:ctor(node,z)
	self.super.ctor(self,node)
	self._delta = node:getLocalZOrder() - z
end

function cc.reorderCommand:undo()
	local z = self._object:getLocalZOrder()
	self._object:setLocalZOrder(z + self._delta)
end

function cc.reorderCommand:redo()
	local z = self._object:getLocalZOrder()
	self._object:setLocalZOrder(z - self._delta)
end

return cc.reorderCommand