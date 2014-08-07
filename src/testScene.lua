local testScene = class("testScene",function()
 	return cc.Scene:create() 
end)
testScene.__index = testScene

function testScene:ctor()
	local layer = ccui.layer()
	self:addChild(layer)
	local scrollview = ccui.scrollView({size = cc.size(960,640),innerSize = cc.size(960*3,640),direction = ccui.ScrollViewDir.horizontal})
	local filename = "back.ExportJson"
	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(filename)
	local name = string.ipextension(filename)
	local armature = ccs.Armature:create(name)
	scrollview:addChild(armature)
	local pos = cc.p(480,320)
	armature:pos(pos)

	filename = "middle.ExportJson"
	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(filename)
	name = string.ipextension(filename)
	armature = ccs.Armature:create(name)
	scrollview:addChild(armature)
	armature:pos(pos)

	filename = "floor.ExportJson"
	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(filename)
	name = string.ipextension(filename)
	armature = ccs.Armature:create(name)
	scrollview:addChild(armature)
	armature:pos(pos)

	filename = "front.ExportJson"
	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(filename)
	name = string.ipextension(filename)
	armature = ccs.Armature:create(name)
	scrollview:addChild(armature)
	armature:pos(pos)

	layer:addChild(scrollview)
end

return testScene
