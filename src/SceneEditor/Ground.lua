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
	self._layersVector:earse(index)
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

function Ground:getScene()
	return self._ownerScene
end

return Ground
