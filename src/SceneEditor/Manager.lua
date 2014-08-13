require(uber.PACKAGE_NAME..".helper"..".json")
function pArray(p)
	if not p then return nil end
	local a = {}
	if p.x ~= nil then
		a["x"] = p.x
	end
	if p.y ~= nil then
		a["y"] = p.y
	end
	if p.z ~= nil then
		a["z"] = p.z
	end
	return a
end

SceneObject = 
{
	Filename = "SceneObject.png",
	Flip 	= { x=false, y=false },
	Pos 	= { x=0, y=0 },
	zOrder  = 0,
	Rotation = 0,
	Scale   = { x=1, y=1 },
	Opacity = 255,  -- 不透明度,0-255
	Filter  = nil,  -- filter表,保存滤镜名称和参数值
	locked  = false, --  界面锁定,锁定之后不可对其做任何操作
	visible = true, -- 可视,暂时预留
}

function SceneObject:getJsonData()
	local data = {}
	data["FileName"] = self.Filename
	data["Pos"] = pArray(self.Pos)
	data["Flip"] = pArray(self.Flip)
	data["zOrder"] = self.zOrder
	data["Rotation"] = self.Rotation
	data["Scale"] = pArray(self.Scale)
	data["Opacity"] = self.Opacity
	if self.Filter then
		data["Filter"] = self.Filter:getJsonData()
	end
	data["locked"] = self.locked
	data["visible"] = self.visible
	return data
end

function SceneObject:serialize(jsonValue)
	self.Filename = jsonValue["FileName"]
	self.Pos = jsonValue["Pos"]
	self.Flip = jsonValue["Flip"]
	self.zOrder = jsonValue["zOrder"]
	self.Rotation = jsonValue["Rotation"]
	self.Scale = jsonValue["Scale"]
	self.Opacity = jsonValue["Opacity"]
	self.locked = jsonValue["locked"]
	self.visible = jsonValue["visible"]
	local filter = jsonValue["Filter"]
	if filter then
		self.Filter = ccs.ObjectFactory.getInstance():createObject(filter["name"])
		self.Filter:serialize(filter)
	end
end


GroundLayer = import(".GroundLayer")
Ground = import(".Ground")
FrontGround = import(".FrontGround")
Floor = import(".Floor")
GameScene = import(".GameScene")

local SceneManager = class("SceneManager")
SceneManager.__index = SceneManager

function SceneManager:ctor()
	self._Scenes = {}
end

function SceneManager:addScene(name,width)
	if name and width then
		assert(self._Scenes[name] == nil)
		self._Scenes[name] = GameScene.new(name,width)
		return self._Scenes[name]
	elseif type(name) == "table" then
		local scene = name
		self._Scanes[scene._name] = scene
		return scene
	end
	return nil
end

function SceneManager:removeScene(param)
	if type(param) == "string" then
		if self._Scenes[param] then
			self._Scenes[param] = nil
		end
	elseif type(param) == "table" then
		self._Scanes[param._name] = nil
	end
end

function SceneManager:findScene(name)
	return self._Scenes[name]
end

function SceneManager:renameScene(old_name,new_name)
	local scene = self._Scenes[old_name]
	if scene then
		scene._name = new_name
		self._Scenes[old_name] = nil
		self._Scenes[new_name] = scene
	end
end

function SceneManager:Save(name,path)
	local scenedata = self:findScene(name):getJsonData()
	local json_str = json.encode(scenedata)
	local filePath = path.."\\".."aaa.json"
	local file = io.open(filePath,"w+")
	if file then
		cclog("保存成功")
		file:write(json_str) 
		file:close()
	end
end

function SceneManager:Load(path)
	local file = io.open("e:\\output\\aaa.json")
	if file then
		local json_str = file:read("*a")
		cclog(json_str)
		local parseTable = json.decode(json_str,1)
		local scene = GameScene.new("test",1234)
		scene:serialize(parseTable)
		return scene
	end
	return nil
end

return SceneManager