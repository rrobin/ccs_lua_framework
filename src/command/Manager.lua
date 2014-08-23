import(".Base")
import(".mutilCommand")
import(".CustomCommand")
import(".NodeCommand.NodeBase")
import(".NodeCommand.Move")
import(".NodeCommand.Rotate")
import(".NodeCommand.Scale")
import(".NodeCommand.Flip")
import(".NodeCommand.Opactiy")
import(".NodeCommand.Reorder")

local CommandManager = class("CommandManager")
CommandManager.__index = CommandManager
--[[
	workStack 保存执行中的command栈
	reserveStack 保存撤销的command栈
]]

function CommandManager:ctor()
	self._workStack = stack.new()
	self._reserveStack = stack.new()
end

--[[
	执行一个command,并且重置撤销链表
]]
function CommandManager:execute(command)
	--先执行清理
	self:clearReservedCommands()
	cclog("执行:"..command._tips)
	command:redo()
	self._workStack:push(command)
end

--[[
	清空撤销栈
]]
function CommandManager:clearReservedCommands()
	while self._reserveStack:empty() == false
		do
		local command = self._reserveStack:pop()
		cclog("释放:"..command._tips)
		command:destory()
	end
end

--[[
	撤销操作
	step 撤销步数
	将撤销的command加入到撤销栈里
]]
function CommandManager:undo(step)
	if self._workStack:empty() then return end
	if self._workStack:count() < step then step = self._workStack:count() end
	for i=1,step do
		local command = self._workStack:pop()
		cclog("撤销:"..command._tips)
		command:undo()
		self._reserveStack:push(command)
	end
end

--[[
	重做操作
	step 重做步数
	将撤销栈里的command重新执行一次
]]
function CommandManager:redo(step)
	if self._reserveStack:empty() then return end
	if self._reserveStack:count() < step then step = self._reserveStack:count() end
	for i=1,step do
		local command = self._reserveStack:pop()
		cclog("重做:"..command._tips)
		command:redo()
		self._workStack:push(command)
	end
end

return CommandManager