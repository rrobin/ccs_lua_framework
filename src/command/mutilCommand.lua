mutilCommand = class("mutilCommand", Command)
mutilCommand.__index = mutilCommand

function mutilCommand:ctor(...)
	self._tips = "复合动作:"
	self._commands = {...}
	for k,command in pairs(self._commands) do
		if k ~= 1 then
			self._tips = self._tips.."/"
		end
		self._tips = self._tips..command._tips
	end
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
		if not command.destory then
			cclog("错误的命令,没有析构函数,命令名:"..command._tips)
		end
		cclog("释放:"..command._tips)
		command:destory()
	end
end

return mutilCommand