local ui = ccui
local CheckBox = ui.CheckBox

function CheckBox:addCheckBoxEvent(params)
	while true
    do
        if params and type(params) ~= "table" then return end
        local defaultCallbacks = 
        {
            [ui.CheckBoxEventType.selected]     = handler(self,self.onSelected),
            [ui.CheckBoxEventType.unselected]   = handler(self,self.onUnSelected),
        }
        if params and table.nums(params) ~= 0 then
            table.merge(defaultCallbacks,params)
        end
        self.checkboxlistener = defaultCallbacks
        handle = function(uiwidget,event)
            if self.checkboxlistener[event] then
               self.checkboxlistener[event](uiwidget)
            end
        end
        self:addEventListener(handle)
        break
    end
end

function CheckBox:onSelected(checkbox)
end

function CheckBox:onUnSelected(checkbox)
end