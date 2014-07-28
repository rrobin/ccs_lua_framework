NodeCommand = class("NodeCommand", command)
NodeCommand.__index = NodeCommand

function NodeCommand:ctor(Node)
	self._object = Node
	self._param = {}
	self._temp = {}
	CC_SAFE_RETAIN(Node)
end

function NodeCommand:destory()
	CC_SAFE_RELEASE(self._object)
	self._object = nil
	self._param = nil
	self._temp = nil
end

return NodeCommand