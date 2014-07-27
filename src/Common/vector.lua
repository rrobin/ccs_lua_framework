local vector = class("vector")
vector.__index = vector

function vector:ctor()
	self._values = {}
end

-- index start at 0
function vector:at(index)
	local size = #self._values
	assert(index < size)
	return self._values[index+1]
end

function vector:push_back(value)
	self._values[#self._values+1] = value
end

function vector:push_front(value)
	table.insert(self._values,1,value)
end

function vector:pop_back()
	self._values[#self._values] = nil
end

function vector:pop_front()
	table.remove(self._values,1)
end

function vector:insert(value,pos)
	if pos == self:count()-1 then
		self:push_back(value)
	elseif pos == 0 then
		self:push_front(value)
	else
		assert(pos < self:count())
		table.insert(self._values,pos+1,value)
	end
end

function vector:earse(pos)
	assert(pos >= 0 and pos < #self._values)
	table.remove(self._values,pos)
end

function vector:count()
	return #self._values
end

function vector:empty()
	return #self._values == 0
end

return vector