local GameScene = class("GameScene")
GameScene.__index = GameScene

function GameScene:ctor(name,width)
	self._width = width
	self._BackGround = Ground.new(self)
	self._Floor = Ground.new(self)
	self._FrontGround = Ground.new(self)
	self._name = name
	self._objCount = 0
end

function GameScene:getJsonData()
	cclog("  GameScene:getJsonData()")
	local data = {}
	data["name"] = self._name
	data["width"] = self._width
	data["BackGround"] = self._BackGround:getJsonData()
	data["Floor"] = 	 self._Floor:getJsonData()
	data["FrontGround"] = self._FrontGround:getJsonData()
	data["ObjCount"] = self._objCount
	return data
end

function GameScene:serialize(jsonValue)
	self._width = jsonValue["width"]
	self._name = jsonValue["name"]
	cclog(" self._BackGround地址:"..tostring(self._BackGround))
	self._BackGround:serialize(jsonValue["BackGround"])
	self._Floor:serialize(jsonValue["Floor"])
	self._FrontGround:serialize(jsonValue["FrontGround"])
	self._objCount = jsonValue["ObjCount"]
end

return GameScene