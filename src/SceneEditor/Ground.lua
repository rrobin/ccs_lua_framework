local Ground = class("Ground")
Ground.__index = Ground

function Ground:ctor(owner)
	self._ownerScene = owner
	self._layersVector = vector.new()
	self.layerNo = 0
end

function Ground:addLayer(layer,pos)
	local l = layer
	local index = nil
	if pos == nil then
	    self.layerNo = self.layerNo + 1
        index = self:LayerCount()
	else
	    index = pos
    end
	if not l then
		local name = "层"..tostring(index+1)
		l = GroundLayer.new(self,name)
	end
	self._layersVector:insert(l,index)
	return index
end

function Ground:removeLayer(index)
	if type(index) == "number" then 
		self._layersVector:earse(index)
	elseif type(index) == "string" then
		local count = self._layersVector:count()-1
		for i=0,count do
			local l = self._layersVector:at(i)
			if l._name == index then
				self._layersVector:earse(i)
				break
			end
		end
	else
		assert(false)
		cclog("invalid key")
	end
end

function Ground:LayerCount()
	return self._layersVector:count()
end

function Ground:getLayer(key)
	if type(key) == "number" then
		return self._layersVector:at(key)
	elseif type(key) == "string" then
		local count = self._layersVector:count()-1
		for i=0,count do
			local l = self._layersVector:at(i)
			if l._name == key then
				return l
			end
		end
	else
		assert(false)
		cclog("invalid key")
	end

	return nil
end

-- 根据层名得到其在vector的位置
function Ground:getIndex(lname)
    --[[for k,v in ipairs(self._layersVector) do
		if k._name == name then
			--cclog("node idx:"..idx)
			return v
		end
	end]]
    --cclog("lname:"..lname)
	local count = self._layersVector:count() - 1
	for i=0,count do
		local l = self._layersVector:at(i)
		if l._name == lname then
			return i
        end
    end
end

function Ground:getScene()
	return self._ownerScene
end

function Ground:getJsonData()
	local data = {}
	local layers = {}
	for i=1,self:LayerCount() do
		local l = self:getLayer(i-1)
		layers[i] = l:getJsonData()
	end
	data["layers"] = layers
	return data
end

function Ground:serialize(jsonValue)
	local layers = jsonValue["layers"]

	for i=1,#layers do
		self:addLayer()
		local l = self:getLayer(i-1)
		l:serialize(layers[i])
	end
end

return Ground
