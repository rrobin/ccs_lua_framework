BrightSprite = class("BrightSprite",function(charcater,action)
	local sp = CCShaderSprite:create("shaders/bright.fsh")
	sp = ShaderSpriteExtend.extend(sp)
	sp:setNodeEventEnabled(true)
	sp:load(charcater)
	sp:playAction(action)
 	return sp
end)
BrightSprite.__index = BrightSprite

function BrightSprite:ctor()
	self:linkLocationC()
	self._brightness = 0.0
end

function BrightSprite:linkLocation()
	self._brightnessLocation = self:link("brightness")
end

function BrightSprite:setupLocation()
	if self._brightness and self._brightnessLocation then
		self:set1f(self._brightnessLocation,self._brightness)
	end
end

return BrightSprite