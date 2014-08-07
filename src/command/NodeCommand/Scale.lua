cc.ScaleCommand = class("cc.ScaleCommand", NodeCommand)
cc.ScaleCommand.__index = cc.ScaleCommand

function cc.ScaleCommand:ctor(Node,scaleX,scaleY)
	self.super.ctor(self,Node)
	self._tips = "Scale Node"
	if scaleX and scaleY then
		self._delta = cc.p(Node:getScaleX()-scaleX,Node:getScaleY()-scaleY)
	else
		self._delta = Node:getScale() - scaleX
	end
end

function cc.ScaleCommand:undo()
	if type(self._delta) == "number" then
		local scale = self._object:getScale()
		self._object:setScale(scale+self._delta)
	else
		local x = self._object:getScaleX()
		local y = self._object:getScaleY()
		self._object:setScaleX(x+self._delta.x)
		self._object:setScaleY(y+self._delta.y)
	end
end

function cc.ScaleCommand:redo()
	if type(self._delta) == "number" then
		local scale = self._object:getScale()
		self._object:setScale(scale-self._delta)
	else
		local x = self._object:getScaleX()
		local y = self._object:getScaleY()
		self._object:setScaleX(x-self._delta.x)
		self._object:setScaleY(y-self._delta.y)
	end
end

return cc.ScaleCommand