local testScene = class("testScene",function()
 	return cc.Scene:create() 
end)
testScene.__index = testScene

function testScene:ctor()
	local layer = ccui.layer()
	self:addChild(layer)
	local image = ccui.image({image = "1.png"})
	image:pos(cc.CENTER)
	image:setShader("brightShader")
	image:setUniform("brightness",0.5)
	layer:addChild(image)

	self._tree = require("ui.TreeControl").new(cc.size(200,200),"MainTree",nil)
	local root1 = self._tree:addItem("主干1")
	local child1_1 = self._tree:addItem("儿子1-1",root1)
	local child1_2 = self._tree:addItem("儿子1-2",root1)
	local child1_3 = self._tree:addItem("儿子1-3",root1)
	local root2 = self._tree:addItem("主干2")
	local child2_1 = self._tree:addItem("儿子2-1",root2)
	local child2_2 = self._tree:addItem("儿子2-2",root2)
	local child2_3 = self._tree:addItem("儿子2-3",root2)
	local root3 = self._tree:addItem("主干3")
	local root4 = self._tree:addItem("主干4")
	local root5 = self._tree:addItem("主干5")
	local child1_1_1 = self._tree:addItem("孙子1-1-1",child1_1)
	local child1_1_2 = self._tree:addItem("孙子1-1-2",child1_1)
	local child1_1_3 = self._tree:addItem("孙子1-1-3",child1_1)
	local child1_1_4 = self._tree:addItem("孙子1-1-4",child1_1)
	local child1_1_5 = self._tree:addItem("孙子1-1-5",child1_1)
	local child1_1_6 = self._tree:addItem("孙子1-1-6",child1_1)
	local child1_1_7 = self._tree:addItem("孙子1-1-7",child1_1)
	local child1_1_8 = self._tree:addItem("孙子1-1-8",child1_1)
	local child1_1_9 = self._tree:addItem("孙子1-1-9",child1_1)
	local child1_1_10 = self._tree:addItem("孙子1-1-10",child1_1)
	self._tree:print()
	self._tree:getNodePos(child1_1_7)
	--[[
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
	]]
end

return testScene
