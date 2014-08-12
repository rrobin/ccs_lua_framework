CustomCommand = class("CustomCommand", command)
CustomCommand.__index = CustomCommand

function CustomCommand:ctor(params)
	self._tips = params.tips
	self._params = params
	if self._params.init then
		self._params:init()
	end
end

function CustomCommand:redo()
	if self._params.redo then
		self._params:redo()
	end
end

function CustomCommand:undo()
	if self._params.undo then
		self._params:undo()
	end
end

function CustomCommand:destory()
	if self._params.destory then
		self._params:destory()
	end
end

return CustomCommand