command.modifyObject = class("command.modifyObject", command)
command.modifyObject.__index = command.modifyObject

function command.modifyObject:ctor(objInfo,type,value)
	self._tips = "更改SceneObject属性"
	self._type = type
	if self._type == 1 then --  pos
		self._delta = cc.pSub(objInfo.Pos,value)
	elseif self._type == 2 then --scale
		self._delta = cc.pSub(objInfo.Scale,value)
	elseif self._type == 3 then --旋转
		self._delta = objInfo.Rotation - value
	elseif self._type == 4 then --透明度
		self._delta = objInfo.Opacity - value
	elseif self._type == 5 then -- 翻转
		self._delta = value
		self._org = self._objInfo.Flip
	elseif self._type == 6 then -- 层级
		self._delta = objInfo.zOrder - value
	end
	self._objInfo = objInfo
end

function command.modifyObject:undo()
	if self._type == 1 then --  pos
		self._objInfo.Pos = cc.pAdd(self._objInfo.Pos,self._delta)
	elseif self._type == 2 then --scale
		self._objInfo.Scale = cc.pAdd(self._objInfo.Scale,self._delta)
	elseif self._type == 3 then --旋转
		self._objInfo.Rotation = self._delta + self._objInfo.Rotation
	elseif self._type == 4 then --透明度
		self._objInfo.Opacity = self._delta + self._objInfo.Opacity
	elseif self._type == 5 then -- 翻转
		self._objInfo.Flip = self._org
	elseif	self._type == 6 then
		self._objInfo.zOrder = self._delta + self._objInfo.zOrder
	end
end

function command.modifyObject:redo()
	if self._type == 1 then --  pos
		self._objInfo.Pos = cc.pSub(self._objInfo.Pos,self._delta)
	elseif self._type == 2 then --scale
		self._objInfo.Scale = cc.pSub(self._objInfo.Scale,self._delta)
	elseif self._type == 3 then --旋转
		self._objInfo.Rotation = self._objInfo.Rotation - self._delta
	elseif self._type == 4 then --透明度
		self._objInfo.Opacity = self._objInfo.Opacity - self._delta
	elseif	self._type == 5 then -- 翻转
		self._objInfo.Flip = self._delta
	elseif self._type == 6 then
		self._objInfo.zOrder = self._objInfo.zOrder - self._delta
	end
end

return command.modifyObject