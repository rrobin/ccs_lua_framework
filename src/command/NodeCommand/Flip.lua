cc.FlipCommand = class("cc.FlipCommand", NodeCommand)
cc.FlipCommand.__index = cc.FlipCommand

cc.axis_x = 0
cc.axis_y = 1
cc.axis_both = 2

function cc.FlipCommand:ctor(sprite,axis)
	self.super.ctor(self,sprite)
	self._tips = "Flip Node"
	self._axis = axis	
end

function cc.FlipCommand:undo()
	if self._axis == cc.axis_x then
		self._object:setFlippedX(self._object:isFlippedX()==false)
	elseif self._axis == cc.axis_y then
		self._object:setFlippedY(self._object:isFlippedY()==false)
	elseif self._axis ==cc.axis_both then
		self._object:setFlippedX(self._object:isFlippedX()==false)
		self._object:setFlippedY(self._object:isFlippedY()==false)
	end
end

function cc.FlipCommand:redo()
	self:undo()
end

return cc.FlipCommand