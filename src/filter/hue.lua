local HueFilter = class("HueFilter")
HueFilter.__index = HueFilter

function HueFilter:ctor()
	self.name = "hueShader"
	self.HSL = cc.Vertex3F(0,0,0) -- [-1,1]
end

function HueFilter:getJsonData()
	local data = {}
	data["name"] = self.name
	data["HSL"] = pArray(self.HSL)
	return data
end

function HueFilter:serialize(jsonValue)
	self.HSL = jsonValue["HSL"]
end

function HueFilter:ApplyTo(object)
	object:setShader(self.name)
	object:setUniform("u_dHSL",self.HSL)
end

return HueFilter
