local HueFilterUI = class("HueFilterUI", function()
	return ccui.loadWidget("Hue.ExportJson")
end)
HueFilterUI.__index = HueFilterUI

function HueFilterUI:ctor()
	self._object = nil
	self._info = nil
	self._hsl = nil
	self._HSlider = self:getChild("HueSlider")
	self._HSlider:addSliderEvent(handler(self,self.update))
	self._HSlider:addTouchEvent({[ccui.TouchEventType.ended]=handler(self,self.modifyH)})
	self._HText = self:getChild("HueLabel")
	self._SSlider = self:getChild("SatSlider")
	self._SSlider:addSliderEvent(handler(self,self.update))
	self._SSlider:addTouchEvent({[ccui.TouchEventType.ended]=handler(self,self.modifyS)})
	self._SText = self:getChild("SatLabel")
	self._LSlider = self:getChild("BrtSlider")
	self._LSlider:addSliderEvent(handler(self,self.update))
	self._LSlider:addTouchEvent({[ccui.TouchEventType.ended]=handler(self,self.modifyL)})
	self._LText = self:getChild("BrtLabel")
end

function HueFilterUI:setProperty(object,info)
	cclog("HueFilterUI setProperty")
	cclog("info.Filter.name:"..info.Filter.name)
	self._object = object
	self._info = info
	if info.Filter.name ~= "hueShader" or not info.Filter.HSL then
		cclog("not Filter")
		info.Filter = hueFilter.new()
	end
	self._hsl = info.Filter.HSL
	self._object:setShader("hueShader")
	self:updateUI()
end

function HueFilterUI:update(slider)
	local hsl = cc.Vertex3F(0,0,0)

	local percent = self._HSlider:getPercent()
	hsl.x = (percent/100*2-1)*180
	local text = string.format("%d",hsl.x)
	self._HText:setString(text)

	percent = self._SSlider:getPercent()
	hsl.y = percent/100*2-1
	text = string.format("%.1f",hsl.y)
	self._SText:setString(text)

	percent = self._LSlider:getPercent()
	hsl.z = percent/100*2-1
	text = string.format("%.1f",hsl.z)
	self._LText:setString(text)

	self._object:setUniform("u_dHSL",hsl)
end

function HueFilterUI:updateUI()
	local hsl = self._hsl
	cclog("hue update UI")
	cclog("hsl.x:"..hsl.x)
	cclog("hsl.y:"..hsl.y)
	cclog("hsl.z:"..hsl.z)
	self._object:setUniform("u_dHSL",hsl)
	local text = string.format("%d",hsl.x)
	self._HText:setString(text)
	local percent = math.floor((hsl.x/180+1)/2*100)
	self._HSlider:setPercent(percent)

	text = string.format("%.1f",hsl.y)
	self._SText:setString(text)
	percent = math.floor((hsl.y+1)/2*100)
	self._SSlider:setPercent(percent)

	text = string.format("%.1f",hsl.z)
	self._LText:setString(text)
	percent = math.floor((hsl.z+1)/2*100)
	self._LSlider:setPercent(percent)
end

function HueFilterUI:modifyHSL(_tips,_hsl)
	local hsl = self._hsl
	local _d = cc.Vertex3F(hsl.x-_hsl.x,hsl.y-_hsl.y,hsl.z-_hsl.z)
	local m = 
	{
		tips = _tips,
	}
	m.hsl = clone(self._hsl)
	m.init = function()
			CC_SAFE_RETAIN(self._HText)
			CC_SAFE_RETAIN(self._SText)
			CC_SAFE_RETAIN(self._LText)
			CC_SAFE_RETAIN(self._HSlider)
			CC_SAFE_RETAIN(self._SSlider)
			CC_SAFE_RETAIN(self._LSlider)
		end
	m.redo = function()
			m.hsl.x = m.hsl.x - _d.x
			m.hsl.y = m.hsl.y - _d.y
			m.hsl.z = m.hsl.z - _d.z
			self._hsl.x = m.hsl.x
			self._hsl.y = m.hsl.y
			self._hsl.z = m.hsl.z
			self:updateUI()
		end
	m.undo = function()
			m.hsl.x = m.hsl.x + _d.x
			m.hsl.y = m.hsl.y + _d.y
			m.hsl.z = m.hsl.z + _d.z
			self._hsl.x = m.hsl.x
			self._hsl.y = m.hsl.y
			self._hsl.z = m.hsl.z
			self:updateUI()
		end
	m.destory = function()
			CC_SAFE_RELEASE(self._HText)
			CC_SAFE_RELEASE(self._SText)
			CC_SAFE_RELEASE(self._LText)
			CC_SAFE_RELEASE(self._HSlider)
			CC_SAFE_RELEASE(self._SSlider)
			CC_SAFE_RELEASE(self._LSlider)
		end
	local cmd = CustomCommand.new(m)
	Do(cmd)
end

function HueFilterUI:modifyH(slider)
	local percent = slider:getPercent()
	local nHSL = clone(self._hsl)
	nHSL.x = ((percent/100*2)-1)*180
	self:modifyHSL("设置色调",nHSL)
end

function HueFilterUI:modifyS(slider)
	local percent = slider:getPercent()
	local nHSL = clone(self._hsl)
	nHSL.y = ((percent/100*2)-1)
	self:modifyHSL("设置饱和度",nHSL)
end

function HueFilterUI:modifyL(slider)
	local percent = slider:getPercent()
	local nHSL = clone(self._hsl)
	nHSL.z = ((percent/100*2)-1)
	self:modifyHSL("设置明度",nHSL)
end

function HueFilterUI:cleanup()
	self._object = nil
	self._info = nil
end

return HueFilterUI