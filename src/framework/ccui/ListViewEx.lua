local ui = ccui
local ListView = ui.ListView

function ListView:addListVeiwEvent(params)
    while true
    do
        if not func then
        local defaultCallbacks = 
        {
            [ui.ListViewEventType.onsSelectedItem] = handler(self,self.onsSelectedItem),
        }
        self.listViewlistener = defaultCallbacks
        else 
            self.listViewlistener = { [ccs.ListViewEventType.onsSelectedItem] = func,}
        end
        handle = function(uiwidget,event)
            if self.listViewlistener[event] then
               self.listViewlistener[event](uiwidget)
            end
        end
        self:addEventListener(handle)
        break
    end
end

function ListView:onsSelectedItem(listView)
end