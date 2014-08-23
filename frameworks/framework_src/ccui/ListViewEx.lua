local ui = ccui
local ListView = ui.ListView

function ListView:addListVeiwEvent(params)
    while true
    do
        if params and type(params) ~= "table" then return end
        local defaultCallbacks = 
        {
            [ui.ListViewEventType.onSelectedItem_start] = handler(self,self.onSelectedItemStart),
            [ui.ListViewEventType.onSelectedItem_end] = handler(self,self.onSelectedItemEnd),
        }
        self.listViewlistener = defaultCallbacks
        if params and table.nums(params) ~= 0 then
            table.merge(defaultCallbacks,params)
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

function ListView:onSelectedItemStart(listView)
end

function ListView:onSelectedItemEnd(listView)
end