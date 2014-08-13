local GameScene = class("GameScene")
GameScene.__index = GameScene

function GameScene:ctor(name,width)
	self._width = width
	self._BackGround = Ground.new(self)
	self._Floor = Floor.new(self)
	self._FrontGround = FrontGround.new(self)
	self._name = name
end

function GameScene:getJsonData()
	local data = {}
	data["name"] = self._name
	data["width"] = self._width
	data["BackGround"] = self._BackGround:getJsonData()
	data["Floor"] = 	 self._Floor:getJsonData()
	data["FrontGround"] = self._FrontGround:getJsonData()
	return data
end

function GameScene:serialize(jsonValue)
	self._width = jsonValue["width"]
	self._name = jsonValue["name"]
	self._BackGround:serialize(jsonValue["BackGround"])
	self._Floor:serialize(jsonValue["Floor"])
	self._FrontGround:serialize(jsonValue["FrontGround"])
end
return GameScene