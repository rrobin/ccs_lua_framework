local MessageBox = class("MessageBox",function()
 	return cc.Layer:create() 
end)
MessageBox.__index = MessageBox

function MessageBox:ctor()
	local layer = ccui.loadLayer("MessageBox.ExportJson")
	self._layer = layer
	self:addChild(layer)

 	local message = layer:getChild("Message")
	message:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(uiwidget)
	 		uiwidget:runAction(cc.RemoveSelf:create())
	end})
end

function MessageBox:setString(text)
	local mgsLabel = self._layer:getChild("MgsLabel")
	mgsLabel:setString(text)
end

return MessageBox
