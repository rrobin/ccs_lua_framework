command.NewScene = class("command.NewScene", command)
command.NewScene.__index = command.NewScene

function command.NewScene:ctor(name,width)
	self._tips = "新建场景"
	self._param = { name, width }
end

function command.NewScene:undo()
	local name = self._param[1]
	SceneManager:removeScene(name)
end

function command.NewScene:redo()
	local name = self._param[1]
	local width = self._param[2]
	SceneManager:addScene(name,width)
end

function command.NewScene:destory()
	self._param = nil
end

return command.NewScene