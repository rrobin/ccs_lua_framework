command.NewLayer = class("commad.NewLayer", command)
command.NewLayer.__index = command.NewLayer

function command.NewLayer:ctor(name,ground)
	self._tips = "新建层"
	self._name = name
	self._ground = ground
end

function command.NewLayer:redo()
	local l = nil
	if self._name then
	 	GroundLayer.new(self._ground,self._name)
	 end
	self._index = self._ground:addLayer(l)
end

function command.NewLayer:undo()
	self._ground:removeLayer(self._index)
end

function command.NewLayer:destory()
	self._name = nil
	self._ground = nil
end

return command.NewLayer