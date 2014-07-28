command.RenameScene = class("command.RenameScene", command)
command.RenameScene.__index = command.RenameScene

function command.RenameScene:ctor(old_name,new_name)
	self._tips = "重命名场景"
	self._param = {old_name,new_name}
end

function command.RenameScene:redo()
	SceneManager:renameScene(self._param[1],self._param[2])
end

function command.RenameScene:undo()
	SceneManager:renameScene(self._param[2],self._param[1])
end

function command.RenameScene:destory()
	self._param = nil
end

return command.RenameScene