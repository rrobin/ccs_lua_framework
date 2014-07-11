local ui = ccui
local Slider = ui.Slider

function Slider:addSliderEvent(func)
	while true
    do
        if not func then
        local defaultCallbacks = 
        {
            [ui.SliderEventType.percentChanged] = handler(self,self.onChanged),
        }
        self.Sliderlistener = defaultCallbacks
    	else 
    		self.Sliderlistener = { [ui.SliderEventType.percentChanged] = func,}
    	end
        handle = function(uiwidget,event)
            if self.Sliderlistener[event] then
               self.Sliderlistener[event](uiwidget)
            end
        end
        self:addEventListener(handle)
        break
    end
end

function Slider:onChanged(slider)
end