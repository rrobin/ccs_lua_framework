local GameScene = class("GameScene")
GameScene.__index = GameScene

function GameScene:ctor(name,width)
	self._width = width
	self._BackGround = Ground.new(self)
	self._Floor = Floor.new(self)
	self._FrontGround = FrontGround.new(self)
	self._name = name
end

return GameScene