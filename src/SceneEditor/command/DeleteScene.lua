command.DeleteScene = class("command.DeleteScene", command)
command.DeleteScene.__index = command.DeleteScene

function command.DeleteScene:ctor(name)
	self._tips = "删除场景"
	self._scene = SceneManager:findScene(name)
end

function command.DeleteScene:redo()
	SceneManager:addScene(self._scene)
end

function command.DeleteScene:undo()
	SceneManager:removeScene(self._scene)
end

function command.DeleteScene:destory()
	self._scene = nil
end

return command.DeleteScene