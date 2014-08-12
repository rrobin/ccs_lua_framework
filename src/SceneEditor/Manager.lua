
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
}


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

function SceneManager:Save(path)
	cclog("还未考虑好是保存json还是xml还是二进制")
end

function SceneManager:Load(path)
	cclog("敬请期待")
end

return SceneManager