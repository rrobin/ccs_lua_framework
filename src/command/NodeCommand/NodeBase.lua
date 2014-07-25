NodeCommand = class("NodeCommand", command)
NodeCommand.__index = NodeCommand

function NodeCommand:ctor(Node)
	self._object = Node
	CC_SAFE_RETAIN(Node)
end

function NodeCommand:destory()
	CC_SAFE_RELEASE(self._object)
	self._object = nil
end

return NodeCommand