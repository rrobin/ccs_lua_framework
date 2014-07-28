command.addTreeItem = class("command.addTreeItem", NodeCommand)
command.addTreeItem.__index = command.addTreeItem

function command.addTreeItem:ctor(tree,name,parent,pos)
	self.super.ctor(self,tree)
	self._tips = "添加树控件子项"
	self._param = {name,parent,pos}
end

function command.addTreeItem:redo()
	local name = self._param[1]
	local parent = self._param[2]
	local pos = self._param[3]
	self._node = self._object:addItem(name,parent,pos)
	self._object:Layout()
end

function command.addTreeItem:undo( ... )
	self._object:removeItem(self._node)
	self._object:Layout()
end

return command.addTreeItem