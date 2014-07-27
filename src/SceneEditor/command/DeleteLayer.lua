command.DeleteLayer = class("command.DeleteLayer", command)
command.DeleteLayer.__index = command.DeleteLayer

function command.DeleteLayer:ctor(index,ground)
	self._tips = "删除层"
	self._index = index
	self._ground = ground
end

function command.DeleteLayer:redo()
	local l = self._ground:getLayer(self._index)
	self._ground:removeLayer(self._index)
	self._layer = l
end

function command.DeleteLayer:undo()
	self._index = self._ground:addLayer(self._layer)
end

function command.DeleteLayer:destory()
	self._index = nil
	self._ground = nil
	self._layer = nil
end

return command.DeleteLayer