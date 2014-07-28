Command = class("Command")
Command.__index = Command

function Command:ctor()
	self._tips = ""
end

function Command:undo()
	-- body
end

function Command:redo()
	-- body
end

function Command:destory()
	-- body
end

return Command