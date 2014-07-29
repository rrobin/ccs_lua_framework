local ui = ccui
local TextField = ui.TextField

function TextField:addTextFieldEvent(params)
	while true
    do
        if params and type(params) ~= "table" then return end
        local defaultCallbacks = 
        {
            [ui.TextFiledEventType.attach_with_ime]  = handler(self,self.onAttach),
            [ui.TextFiledEventType.detach_with_ime]  = handler(self,self.onDetach),
            [ui.TextFiledEventType.insert_text]	     = handler(self,self.onInsertText),
            [ui.TextFiledEventType.delete_backward]  = handler(self,self.onDeleteBackWard),
        }
        if params and table.nums(params) ~= 0 then
            table.merge(defaultCallbacks,params)
        end
        self.TextFieldlistener = defaultCallbacks
        handle = function(uiwidget,event)
            if self.TextFieldlistener[event] then
               self.TextFieldlistener[event](uiwidget)
            end
        end
        self:addEventListener(handle)
        break
    end
end

function TextField:onAttach(textField)
end

function TextField:onDetach(textField)
end

function TextField:onInsertText(textField)
end

function TextField:onDeleteBackWard(textField)
end

function TextField:setString(string)
    self:setText(string)
end

function TextField:getString()
    return self:getStringValue()
end