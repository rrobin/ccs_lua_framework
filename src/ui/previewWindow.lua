--[[project.type = 2
local s_type = project.type
local size = SimulatorSize[s_type]
local ui_size = 
]]

local previewWindow = class("previewWindow", function() return cc.Layer:create() end)
previewWindow.__index = previewWindow

function previewWindow:ctor(arg)
	if type(arg) == "number" then
		self._size = SimulatorSize[arg]
	else
		self._size = arg
	end
end

function previewWindow:add(node)
	local size = node:getSize()
	
end

return previewWindow