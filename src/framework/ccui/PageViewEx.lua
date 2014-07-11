local ui = ccui
local PageView = ui.PageView

function PageView:addPageViewEvent(func)
	while true
    do
        if not func then
        local defaultCallbacks = 
        {
            [ui.PageViewEventType.turning] = handler(self,self.onTurning),
        }
        self.PageViewlistener = defaultCallbacks
    	else 
    		self.PageViewlistener = { [ui.PageViewEventType.turning] = func,}
    	end
        handle = function(uiwidget,event)
            if self.PageViewlistener[event] then
               self.PageViewlistener[event](uiwidget)
            end
        end
        self:addEventListener(handle)
        break
    end
end

function PageView:onTurning()
end