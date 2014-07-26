local Ground = class("Ground")
Ground.__index = Ground

function Ground:ctor()
	self._layers = vector.new()
end

function Ground:addLayer(layer)
	local l = layer
	if not l then

	end
end

function Ground:removeLayer(index)
	self._layers:earse(index)
end

return Ground
