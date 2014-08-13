local Floor = class("Floor")
Floor.__index = Floor

function Floor:ctor(owner)
	self._ownerScene = owner
	self._objects = {}
end

function Floor:addObject(object,name)
	self._objects[name] = object
end

function Floor:removeObject(name)
	if self._objects[name] then
		self._objects[name] = nil
	end
end

function Floor:getJsonData()
	local data = {}
	local objects = {}
	data["objects"] = objects
	return data 
end

function Floor:serialize(jsonValue)
end

return Floor