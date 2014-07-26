SimulatorType = 
{
   IPhone4 = 0,		-- 480x320
   IPhone4HD = 1, 	-- 960x640
   IPhone5 = 2,		-- 1136x640
   IPhone6 = 3,		--
   IPad	   = 4,		-- 1024x768
   IPadHD  = 5,		-- 2048x1536
}

SimulatorSize =
{
 	{width = 480,height = 320},		-- ip4
 	{width = 960,height = 640},		-- ip4HD
 	{width = 1136,height = 640},	-- ip5
 	{width = 480,height = 320},		-- ip6
 	{width = 1024,height = 768},	-- ipad
 	{width = 2048,height = 1536},	-- ipadHD
}

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