CommandManager = import(".Manager").new()
DoCmd = function(command) 
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