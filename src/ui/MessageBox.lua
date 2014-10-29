local MessageBox = class("MessageBox",function()
 	return ccui.loadLayer("MessageBox.ExportJson")
end)
MessageBox.__index = MessageBox

function MessageBox:ctor()
 	local message = self:getChild("Message")
	message:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(uiwidget)
	 		uiwidget:runAction(cc.RemoveSelf:create())
	end})
end

function MessageBox:setString(text)
	local mgsLabel = self:getChild("MgsLabel")
	mgsLabel:setString(text)
end

return MessageBox
