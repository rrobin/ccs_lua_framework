local ui = ccui
local ScrollView = ui.ScrollView

function ScrollView:addScrollViewEvent(params)
    while true
    do
        if params and type(params) ~= "table" then return end
        local defaultCallbacks = 
        {
            [ui.ScrollviewEventType.top]     			= handler(self,self.onTop),
            [ui.ScrollviewEventType.bottom]    		    = handler(self,self.onBottom),
            [ui.ScrollviewEventType.left]   			= handler(self,self.onLeft),
            [ui.ScrollviewEventType.right] 			    = handler(self,self.onRight),
            [ui.ScrollviewEventType.scrolling]			= handler(self,self.onScrolling),
            [ui.ScrollviewEventType.bounce_top]		    = handler(self,self.onBounceTop),
            [ui.ScrollviewEventType.bounce_bottom]		= handler(self,self.onBounceBottom),
            [ui.ScrollviewEventType.bounce_left]		= handler(self,self.onBounceLeft),
            [ui.ScrollviewEventType.bounce_right]		= handler(self,self.onBounceRight),
        }
        if params and table.nums(params) ~= 0 then
            table.merge(defaultCallbacks,params)
        end
        self.ScrollViewlistener = defaultCallbacks
        handle = function(uiwidget,event)
            if self.ScrollViewlistener[event] then
               self.ScrollViewlistener[event](uiwidget)
            end
        end
        self:addEventListener(handle)
        break
    end
end

function ScrollView:onTop(scrollView)
end

function ScrollView:onBottom(scrollView)
end

function ScrollView:onLeft(scrollView)
end

function ScrollView:onRight(scrollView)
end

function ScrollView:onScrolling(scrollView)
end

function ScrollView:onBounceTop(scrollView)
end

function ScrollView:onBounceBottom(scrollView)
end

function ScrollView:onBounceLeft(scrollView)
end

function ScrollView:onBounceRight(scrollView)
end