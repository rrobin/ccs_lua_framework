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
	if type(pos) == "number" then 
	    self._objectsVector:earse(pos)
    else
    	local count = self._objectsVector:count()-1
    	for i=0,count do
    		local obj = self._objectsVector:at(i)
    		if obj == pos then
    			cclog("remove object pos:"..i)
    			self._objectsVector:earse(i)
    			break
    		end
    	end
    end
end

function GroundLayer:getObject(pos)
	return self._objectsVector:at(pos)
end

function GroundLayer:getObjectCount()
	return self._objectsVector:count()
end

function GroundLayer:getObjectIndex(obj)
    local count = self._objectsVector:count()-1
    for i=0,count do
    		local objtemp = self._objectsVector:at(i)
    		if obj == objtemp then
    			cclog("get object pos:"..i)
    			return i
    		end
    end
end

function GroundLayer:getGround()
	return self._ownerGround
end

function GroundLayer:rename(new_name)
	self._name = new_name
end

function GroundLayer:getJsonData()
	local data = {}
	data["name"] = self._name
	data["ratio"] = self._ratio
	data["z"] = self._zOrder
	local childs = {}
	data["childs"] = childs
	cclog("  groundlayer self:"..tostring(self))
	cclog(" self._objectsVector:count():"..self._objectsVector:count())
	for i=1,self._objectsVector:count() do
		childs[i] = self:getObject(i-1):getJsonData()
	end
	
	return data
end

function GroundLayer:serialize(jsonValue)
	self._name = jsonValue["name"]
	self._ratio = jsonValue["ratio"]
	self._zOrder = jsonValue["z"]
	local childs = jsonValue["childs"]
	for i=1,#childs do
		local obj = clone(SceneObject)
		obj:serialize(childs[i])
		self:addObject(obj)
	end
end

return GroundLayer