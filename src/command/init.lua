CommandManager = import(".Manager").new()
Do = function(...)
	local args = {...}
	local command = nil
	if args[1] == command then
		return
	end
	if #args == 1 then
	 	command = args[1]
	else
		command = mutilCommand.new(...)
	end
	CommandManager:execute(command)
end

Undo = function(step)
	if not step then step = 1 end
	CommandManager:undo(step)
end

Redo = function(step)
	if not step then step = 1 end
	CommandManager:redo(step)
end

-- 申请一个command的命名空间
command = {}