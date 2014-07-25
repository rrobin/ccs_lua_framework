cc.ScaleCommand = class("cc.ScaleCommand", NodeCommand)
cc.ScaleCommand.__index = cc.ScaleCommand

function cc.ScaleCommand:ctor(Node,scaleX,scaleY)
	self.super.ctor(self,Node)
	self._tips = "Scale a Node"
	if scaleX and scaleY then
		self._offset = cc.p(Node:getScaleX()-scaleX,Node:getScaleY()-scaleY)
	else
		self._offset = Node:getScale() - scaleX
	end
end

function cc.ScaleCommand:undo()
	if type(self._offset) == "number" then
		local scale = self._object:getScale()
		self._object:setScale(scale+self._offset)
	else
		local x = self:getScaleX()
		local y = self:getScaleY()
		self._object:setScaleX(x+self._offset.x)
		self._object:setScaleY(y+self._offset.y)
	end
end

function cc.ScaleCommand:redo()
	if type(self._offset) == "number" then
		local scale = self._object:getScale()
		self._object:setScale(scale-self._offset)
	else
		local x = self:getScaleX()
		local y = self:getScaleY()
		self._object:setScaleX(x-self._offset.x)
		self._object:setScaleY(y-self._offset.y)
	end
end

return cc.ScaleCommand