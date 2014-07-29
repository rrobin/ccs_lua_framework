command.modifyObject = class("command.modifyObject", command)
command.modifyObject.__index = command.modifyObject

function command.modifyObject:ctor(objInfo,type,value)
	self._tips = "更改SceneObject属性"
	self._type = type
	if self._type == 1 then --  pos
		self._delay = cc.pSub(objInfo.Pos,value)
	elseif self._type == 2 then --scale
		self._delay = cc.pSub(objInfo.Scale,value)
	elseif self._type == 3 then --旋转
		self._delay = objInfo.Rotation - value
	elseif self._type == 4 then --透明度
		self._delay = objInfo.Opacity - value
	end
	self._objInfo = objInfo
end

function command.modifyObject:redo()
	if self._type == 1 then --  pos
		self._objInfo.Pos = cc.pAdd(self._objInfo.Pos,self._delay)
	elseif self._type == 2 then --scale
		self._objInfo.Scale = cc.pAdd(self._objInfo.Scale,self._delay)
	elseif self._type == 3 then --旋转
		self._objInfo.Rotation = self._delay + self._objInfo.Rotation
	elseif self._type == 4 then --透明度
		self._objInfo.Opacity = self._delay + self._objInfo.Opacity
	end
end

function command.modifyObject:undo()
	if self._type == 1 then --  pos
		self._objInfo.Pos = cc.pSub(self._objInfo.Pos,self._delay)
	elseif self._type == 2 then --scale
		self._objInfo.Scale = cc.pSub(self._objInfo.Scale,self._delay)
	elseif self._type == 3 then --旋转
		self._objInfo.Rotation = self._objInfo.Rotation - self._delay
	elseif self._type == 4 then --透明度
		self._objInfo.Opacity = self._objInfo.Opacity - self._delay
	end
end

return command.modifyObject