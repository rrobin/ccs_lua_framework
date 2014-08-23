local stack = class("stack")
stack.__index = stack

function stack:ctor(count)
	self._count = count
	self._values = {}
end

function stack:push(value)
	if self._count and #self._values == self._count then
		table.remove(self._values,1)
	end 
	self._values[#self._values+1] = value
end

function stack:pop()
	local value = self._values[#self._values]
	self._values[#self._values] = nil
	return value
end

function stack:empty()
	return #self._values == 0
end

function stack:count()
	return #self._values
end

function stack:top()
	return self._values[#self._values]
end

return stack