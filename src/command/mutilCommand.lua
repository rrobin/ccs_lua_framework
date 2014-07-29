mutilCommand = class("mutilCommand", Command)
mutilCommand.__index = mutilCommand

function mutilCommand:ctor(...)
	self._tips = "复合动作"
	self._commands = {...}
end

function mutilCommand:redo()
	for _,command in pairs(self._commands) do
		command:redo()
	end
end

function mutilCommand:undo()
	for i=#self._commands,1,-1 do
		self._commands[i]:undo()
	end
end

function mutilCommand:destory()
	for _,command in pairs(self._commands) do
		command:destory()
	end
end

return mutilCommand