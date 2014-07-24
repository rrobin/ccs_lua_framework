local c = cc
local Sprite = c.Sprite
local d = display

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

local playActTag = 100

function Sprite:load(character)
	if display.GameCache.preload(character) then
		self._info = display.GameCache.getCharacter(character)
	end
	assert(self._info)
	self:playAction("default")
end

function Sprite:playAction(action,looptimes)
	local animation = self._info.animations[action]
	if not animation then
		--cclog("not find action:"..action)
		return
	end
	self:stopActionByTag(playActTag)
	local frames = animation:getFrames()
	local temp = frames[1]
	local frame = temp:getSpriteFrame()
	self:setSpriteFrame(frame)
	local animate = cc.Animate:create(animation)
	local action = nil
	if not looptimes or looptimes < 0 then
		action = cc.RepeatForever:create(animate)
	else
		action = cc.Repeat:create(animate,looptimes)
	end

	action:setTag(playActTag)
	self:runAction(action)
end