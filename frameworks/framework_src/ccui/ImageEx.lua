local ui = ccui
local image = ui.ImageView
local d = display

function image:setShader(shaderName)
	 self:getVirtualRenderer():setShader(shaderName)
end

function image:setUniform(name,value)
	self:getVirtualRenderer():setUniform(name,value)
end