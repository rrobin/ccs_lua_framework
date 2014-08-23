local animationNode = class("particle",function()
		return ccui.image({image="Editor/P.jpg"})
	end)
animationNode.__index = animationNode

function animationNode:ctor(filename)

    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(filename)
	cclog("addAnimation filename:"..filename)
	local fname = string.ippath(filename)
	local name = string.ipextension(fname)

	cclog("addAnimation name:"..name)
	local p = ccs.Armature:create(name)
	p:getAnimation():playWithIndex(0)

	p:pos(cc.pMul(cc.s2p(self:getVirtualRendererSize()),0.5))
	self:addProtectedChild(p,-1)
end

return animationNode