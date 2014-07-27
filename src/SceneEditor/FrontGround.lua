FrontGround = class("FrontGround", Ground)
FrontGround.__index = FrontGround

function FrontGround:ctor(owner)
	self.super.ctor(self,owner)
	self.super.addLayer(self)
end

function FrontGround:addLayer(layer)
end

function FrontGround:removeLayer(index)
end

function FrontGround:getLayer()
	return self.super.getLayer(self,0)
end

return FrontGround