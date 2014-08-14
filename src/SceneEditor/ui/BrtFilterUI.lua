local BrtFilterUI = class("BrtFilterUI", function()
	return ccui.loadWidget("Brightness.ExportJson")
	end)
BrtFilterUI.__index = BrtFilterUI

function BrtFilterUI:ctor()
	self._text = self:getChild("BrightnessLabel")
	self._slider = self:getChild("Slider")
	self._slider:addSliderEvent(handler(self,self.update))
	self._slider:addTouchEvent({[ccui.TouchEventType.ended]=handler(self,self.modifyB)})
	self._object = nil
	self._info = nil
end

function BrtFilterUI:setProperty(object,info)
	cclog("BrtFilterUI setProperty")
	cclog("info.Filter.name:"..info.Filter.name)
	if info.Filter.name ~= "brightShader" or not info.Filter.brightness then
		cclog("not Filter")
		info.Filter = brtFilter.new()
	end
	self._info = info
	self._brightness = info.Filter.brightness
	self._object = object
	self._object:setShader("brightShader")
	self:updateUI()
end

function BrtFilterUI:updateUI()
	cclog("Brightness update UI")
	cclog("brightness :"..self._brightness)
	self._object:setUniform("brightness",self._brightness)
	local text = string.format("%.1f",self._brightness)
	self._text:setString(text)
	local percent = math.floor((self._brightness+1)/2*100)
	cclog("percent:"..percent)
	self._slider:setPercent(percent)
end

function BrtFilterUI:modifyB()
	local percent = self._slider:getPercent()
	local delta = self._brightness - ((percent/100*2)-1)
	local m = 
	{
		tips = "设置明度",
	}
	m.b = self._brightness
	m.init = function()
			CC_SAFE_RETAIN(self._object)
			CC_SAFE_RETAIN(self._text)
			CC_SAFE_RETAIN(self._slider)
		end
	m.redo = function()
			m.b = m.b - delta
			cclog("redo brt:"..m.b)
			self._brightness = m.b
			self._info.Filter.brightness = m.b
			self:updateUI()
		end
	m.undo = function()
			m.b = m.b + delta
			cclog("undo brt:"..m.b)
			self._brightness = m.b
			self._info.Filter.brightness = m.b
			self:updateUI()
		end
	m.destory = function()
			CC_SAFE_RELEASE(self._object)
			CC_SAFE_RELEASE(self._text)
			CC_SAFE_RELEASE(self._slider)
		end
	local cmd = CustomCommand.new(m)
	Do(cmd)
end

function BrtFilterUI:update(slider)
	local percent = slider:getPercent()
	local brt = (percent/100*2)-1
	self._object:setUniform("brightness",brt)
	local text = string.format("%.1f",brt)
	self._text:setString(text)
end

function BrtFilterUI:cleanup()
	self._info = nil
	self._object = nil
	cclog("cleanup info.Filter")
end

return BrtFilterUI