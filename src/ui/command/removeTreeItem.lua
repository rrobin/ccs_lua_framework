command.removeTreeItem = class("command.removeTreeItem", NodeCommand)
command.removeTreeItem.__index = command.removeTreeItem

function command.removeTreeItem:ctor(tree,name)
	self.super.ctor(self,tree)
	self._param = name
end

function command.removeTreeItem:redo()
	self._temp = self._object._nodes[self._param]
	self._object:removeItem(self._param)
end

function command.removeTreeItem:undo()
	self._object:addItem(self._param,self._temp.P)
end

return command.removeTreeItem