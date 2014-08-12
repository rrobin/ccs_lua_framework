local GroundLayer = class("GroundLayer")
GroundLayer.__index = GroundLayer

function GroundLayer:ctor(owner,name)
	self._ownerGround = owner
	self._objectsVector = vector.new()
	self._name = name
	self._ratio = {x=1,y=1}
	self._zOrder = 0
end

function GroundLayer:tile()
	local count = self._objectsVector:count()
	if count == 1 then
		local object = self._objectsVector:at(0)
		local width = self._ownerGround:getScene()._width
		local instance = cc.Sprite:create(object.Filename)
		local size = instance:getSize()
		local obj_count = math.ceil(width/size.width)
		object.Pos = cc.p(size.width/2,size.height/2)
		for i=2,obj_count do --跳过1,已经在前面设置了
			local sub_obj = clone(object)
			sub_obj.Pos = cc.p(size.width*(i-1) + size.width/2, size.height/2)
			self._objectsVector:push_back(sub_obj)
		end
	end
end

function GroundLayer:addObject(object,pos)
	if not pos then pos = self._objectsVector:count() end
	cclog("GroundLayer:addObject pos:"..pos)
	self._objectsVector:insert(object,pos)
	return pos
end

function GroundLayer:removeObject(pos)
	self._objectsVector:earse(pos)
end

function GroundLayer:getObject(pos)
	return self._objectsVector:at(pos)
end

function GroundLayer:getGround()
	return self._ownerGround
end

function GroundLayer:rename(new_name)
	self._name = new_name
end

return GroundLayer