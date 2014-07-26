local GameScene = class("GameScene")
GameScene.__index = GameScene

function GameScene:ctor(name,width)
	self._width = width
	self._BackGround = BackGround.new()
	self._Floor = Floor.new()
	self._FrontGround = FrontGround.new()
	self._name = name
end

return GameScene