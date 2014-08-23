local particle = class("particle",function()
		return ccui.image({image="Editor/P.jpg"})
	end)
particle.__index = particle

function particle:ctor(filename)
	local p = cc.ParticleSystemQuad:create(filename)
	p:pos(cc.pMul(cc.s2p(self:getVirtualRendererSize()),0.5))
	self:addProtectedChild(p,-1)
end

return particle