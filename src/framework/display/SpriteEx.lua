local c = cc
local Sprite = c.Sprite

function Sprite:setShader(shaderName)
    local glprogram = cc.GLProgramCache:getInstance():getGLProgram(shaderName)
    if glprogram then
        cclog("setShader "..shaderName)
        self:setGLProgram(glprogram)
        self:setDirty(true)
    end
end

function Sprite:AutoCreate(filename)

	local tag = -1
	local texture = nil
	while true
	do
		local Director = c.Director:getInstance()
		texture = Director:getTextureCache():getTextureForKey(filename)
		if texture then
			tag = 1
			break
		end
		-- find ".png"
		local s,e = string.find(filename,".png")
		if s then
			tag = 0
			break
		end

		-- find ".pvr"
		s,e = string.find(filename,".pvr")
		if s then
			tag = 0
			break
		end

		-- find ".jpg"
		s,e = string.find(filename,".jpg")
		if s then
			local maskfile = string.gsub(filename,".jpg",".mask")
			if c.isFileExist(maskfile) then
				texture = cc.openImage(filename,maskfile)
				tag = 1
				break
			else
				tag = 0
				break
			end
		end

		-- without extension
		filename = filename..".jpg"
	end

	if tag == 0 then
		return Sprite:create(filename)
	elseif tag == 1 then
		return Sprite:createWithTexture(texture)
	end	
end