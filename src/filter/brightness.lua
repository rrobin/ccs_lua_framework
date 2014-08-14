local BrightnessFilter = class("BrightnessFilter")
BrightnessFilter.__index = BrightnessFilter

function BrightnessFilter:ctor()
	self.name = "brightShader"
	self.brightness = 0.0 -- [-1,1]
end

function BrightnessFilter:getJsonData()
	local data = {}
	data["name"] 		= self.name
	data["brightness"] 	= self.brightness
	return data
end

function BrightnessFilter:serialize(jsonValue)
	self.brightness = jsonValue["brightness"]
end

function BrightnessFilter:ApplyTo(object)
	object:setShader(self.name)
	object:setUniform("brightness",self.brightness)
end

return BrightnessFilter