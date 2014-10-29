require("Common.fileSystem")
local testScene = class("testScene",function()
 	return cc.Scene:create() 
end)
testScene.__index = testScene

function testScene:ctor()
	--local t = xml.load(cc.getFullPath("res/skeleton_and_texture.xml"))
	local layer = ccui.layer()
	self._layer = layer
	self:addChild(layer)
	local files = fs.Browse("res/armatures/")
	self._pool = {}
	local pool = self._pool
	for k,v in pairs(files) do
		-- 惭愧,不会写lua的正则表达式...只能用最笨的方式来分解文件
		pool[k] = { mov = {} }
		local f = pool[k]
		for i=1,3 do
			local find = false
			while 1
				do

				if not f.json and not f.xml then
					find = string.find(v[i],".ExportJson") ~= nil
				end

				if find then
					f.json = v[i]
					break
				end

				if not f.json and not f.xml then
			   		find = string.find(v[i],".xml") ~= nil
				end
				if find then
					f.xml = v[i]
				 	break
				end

				if not f.json and not f.png then
					find = string.find(v[i],".png") ~= nil
				end
				if find then
					f.png = v[i]
				 	break
				end

				if not f.json and not f.plist then
					find = string.find(v[i],".plist") ~= nil
				end

				if find then
					f.plist = v[i]
				 	break
				end

				break
			end
		end
	end

	self._tree = require("ui.TreeControl").new(cc.size(300,500),"animTree",handler(self,self.Play))

	for c,f in pairs(pool) do
		if f.xml then 
			local _png = "armatures/"..c.."/"..f.png
			local _plist = "armatures/"..c.."/"..f.plist
			local _xml = "armatures/"..c.."/"..f.xml
			ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(_png,_plist,_xml)
			local p = self._tree:addItem(c)
			_xml = cc.getFullPath(_xml);
			local skeleton = xml.load(_xml)
			f.character = skeleton:find("armatures"):find("armature").name
			local node = skeleton:find("animations")
			for k=1,#node do
				local anims = node[k]:find("animation")
				for i=1,#anims do
					local mov = anims[i]
					if not f.mov[mov.name] then
						f.mov[mov.name] = {}
						self._tree:addItem(mov.name,p)
					end
					if not f.mov[mov.name][anims.name] then
						f.mov[mov.name][anims.name] = true
					end
				end
			end
			f.frameRate = skeleton.frameRate/60
		elseif f.json then
			local _json = "armatures/"..c.."/"..f.json
			ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(_json)
			local p = self._tree:addItem(c)
			_json = cc.getFullPath(_json)
			local file = io.open(_json)
			if file then
				local json_str = file:read("*a")
				json_str = json.decode(json_str,1)
				f.character = json_str["armature_data"][1].name
				local anim_data = json_str["animation_data"]
				for k=1,#anim_data do
					local name = anim_data[k].name
					local mov_data = anim_data[k].mov_data
					for i=1,#mov_data do
						local mov = mov_data[i]
						if not f.mov[mov.name] then
							f.mov[mov.name] = {}
							self._tree:addItem(mov.name,p)
						end
						if not f.mov[mov.name][name] then
							f.mov[mov.name][name] = true
						end
					end
				end
				file:close()
			else
				assert(false,"没有找到目标文件")
			end
			f.frameRate = 1.0
		end
	end

	self._data = 
	{
		character = "",
		armature = nil,
	}

	self._tree:pos(cc.p(25,100))
	self._tree:Layout()
	layer:addChild(self._tree)
	--[[

	local p = ccui.particle("Particles/BurstPipe.plist")
	p:pos(cc.CENTER)
	layer:addChild(p)
	local pos = nil
	local spos = nil
	p:addTouchEvent({[ccui.TouchEventType.began] = function(widget)
			spos = widget:getTouchBeganPosition()
			pos = p:pos()
		end,
		[ccui.TouchEventType.moved] =  function (widget)
			local mpos = widget:getTouchMovePosition()
			local offset = cc.pSub(mpos,spos)
			local _pos = cc.pAdd(pos,offset)
			widget:pos(_pos)
		end})
]]
	--[[
	local list = ccui.listView({size=winSize})
	local label = ccui.label({text="test"})
	list:setItemModel(label)
	local t = fs.Browse(lfs.currentdir(),"*",2)
	local function logTable(tab,p)
		for k,v in pairs(tab) do
			if type(v) == "table" then
				local n = k
				if p then
					n = p.."/"..k
				end
				logTable(v,n)
			else
				local f = v
				if p then
					f = p.."/"..f
				end
				cclog(f)
			end
		end
	end
	logTable(t)
	local r,e = fs.rmfiles(lfs.currentdir(),"%.txt")
	if e then
		cclog(e)
	end
	--[[
	local i = 0
	while filename ~= nil
		do
		list:pushBackDefaultItem()
		local item = list:getItem(i)
		item:setString(filename)
		local f = lfs.attributes(lfs.currentdir().."/"..filename)
		cclog(filename..":"..f.mode)
		filename = dir_obj:next()
		i = i+1
	end
	layer:addChild(list)
	]]
	--[[local image = ccui.image({image = "1.png"})
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
	]]
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

function testScene:changeCharacter(name)
	if name ~= self._data.character then
		self._layer:removeChild(self._data.armature)
		self._data.character = name
		local info = self._pool[name]
		assert(info)
		self._data.armature = ccs.Armature:create(info.character)
		self._layer:addChild(self._data.armature)
		self._data.armature:pos(cc.CENTER)
		self._data.armature:getAnimation():setSpeedScale(info.frameRate)
	end
end

function testScene:Play()
	local item = self._tree:getSelectedItem()
	if item.P then
		self:changeCharacter(item.P.value)
		local info = self._pool[item.P.value]
		local bones = info.mov[item.value]
		for v,_ in pairs(bones) do
			if v ~= info.character then
				self._data.armature:getBone(v):getChildArmature():getAnimation():play(item.value)
			else
				self._data.armature:getAnimation():play(item.value)
			end
		end
	else
		self:changeCharacter(item.value)
		self._data.armature:getAnimation():playWithIndex(0)
	end		
end

return testScene
