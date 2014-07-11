local GameCache = GameCache or {}
cclog("require GameCache module")

CharacterCache = 
{
	brightness = 1.0,
	animations = {},
}

CharacterInfo = 
{
	ver 		= 0,
	actions 	= {},
	offset		= {},
	images		= {},
}

ActionInfo = 
{
	frameCount = 0,
	frameIndex	= {},
	frames		= {},
	delayArray	= {},
	keyFrame	= 0,
}

ImageInfo = 
{
	x = 0,
	y = 0,
	w = 0,
	h = 0,
	ox = 0.0,
	oy = 0.0,
}

HueInfo = 
{
	hue 		= 1.0,
	saturation 	= 1.0,
	brightness	= 1.0,
	limit		= false,
	lmax		= 0.0,
	lmin		= 0.0,
	rmin		= 0.0,
	rmax		= 0.0,
}

GameCache._CharacterCaches = {}
GameCache._CharacterInfo = {}
GameCache._HueScheme = {}

--[[ 
	getCharacterFile
	通过角色名和文件名返回文件所在全路径
	比如:希望查找战士的attack.act文件,那么character传入("warrior"),filename传入("attack.act")
	会在 resourceSearchPath/Character/warrior/attack.act 查找
]]
function GameCache.getCharacterFile(character,filename)
	if not character or not filename then return nil end
	return cc.getFullPath("Character/"..character.."/"..filename)
end

function GameCache.getCharacterData(character)
	local info = GameCache._CharacterInfo[character]
	if not info then
		local filename = GameCache.getCharacterFile(character,character..".chr")
		if filename == nil then
			cclog("GameCache.getCharacterData falied, character :"..tostring(character))
			return nil
		end
		--cclog(filename)
		local infoData = cc.getFileData(filename)
		if infoData:empty() then
			cclog("file:"..filename.." size = 0!")
			return nil
		end

		info = clone(CharacterInfo)

		--版本号
		info.ver = infoData:getU32()

		--偏移点
		for i=1,11 do
			info.offset[i] = { x = infoData:getFloat(), y = infoData:getFloat() }
		end

		--每个动作的帧信息
		local count = infoData:getU32()
		for i=1,count do
			local actionInfo = clone(ActionInfo)
			local actionName = infoData:getStr()
			actionInfo.frameCount 	= infoData:getU16()
			assert(actionInfo.frameCount ~= 0) 
			actionInfo.frameIndex	= readU16Array(infoData,actionInfo.frameCount)
			actionInfo.frames		= readU16Array(infoData,actionInfo.frameCount)
			actionInfo.delayArray	= readU16Array(infoData,actionInfo.frameCount)
			actionInfo.keyFrame		= infoData:getU16()
			info.actions[actionName] = actionInfo
		end

		--图片信息
		local bigImgCount = infoData:getU32()
		for i=1,bigImgCount do
			info.images[i] = {}
			local imgCount = infoData:getU16()
			for j=1,imgCount do
				local imageInfo = clone(ImageInfo)
				imageInfo.x = infoData:getU16()
				imageInfo.y = infoData:getU16()
				imageInfo.w = infoData:getU16()
				imageInfo.h = infoData:getU16()
				imageInfo.ox = infoData:getFloat()
				imageInfo.oy = infoData:getFloat()
				info.images[i][j] = imageInfo
			end
		end
	end
	return info
end

function GameCache.getHueScheme(character)
	local scheme = GameCache._HueScheme[character]
	if not scheme then
		local filename = GameCache.getCharacterFile(character,character..".hue")
		local hueData = cc.getFileData(filename)
		if hueData:empty() then
			return nil
		end
		scheme = {}
		local count = hueData:getU32()
		for i=1,count do
			scheme[hueName] = {}
			local hueInfo = scheme[hueName]
			local hueName = hueData:getStr()	
			hueInfo = clone(HueInfo)
			hueInfo.hue = hueData:getFloat()
			hueInfo.saturation 	= hueData:getFloat()
			hueInfo.brightness 	= hueData:getFloat()
			hueInfo.limit		= hueData:getU8()
			hueInfo.lmax 		= hueData:getFloat()
			hueInfo.lmin		= hueData:getFloat()
			hueInfo.rmin		= hueData:getFloat()
			hueInfo.rmax		= hueData:getFloat()
		end
		GameCache._HueScheme[character] = scheme
	end
	return scheme
end

function GameCache.preload(character,scheme)
	local fullkey = character
	local hue = nil
	if scheme == "" then
		scheme = nil
	end
	if scheme and string.len(scheme) ~= 0 then
		fullkey = fullkey.."."..scheme
		hue = GameCache.getHueScheme(character)
	end

	if GameCache.getCharacter(fullkey) then
		return true
	end

	local info = GameCache.getCharacterData(character)
	
	if info == nil then
		return false
	end 

	local cache = clone(CharacterCache)
	GameCache._CharacterCaches[fullkey] = cache

	if hue then
		cache.brightness = hue[scheme].brightness
	end
	
	for k,v in pairs(info.actions) do
		if v.frameCount > 0  then
			local frameArray = CCArray:createWithCapacity(v.frameCount)
			for i=1,v.frameCount do
				local imageInfo = info.images[v.frameIndex[i]+1][v.frames[i]+1]
				local path = GameCache.getCharacterFile(character,character.."_"..v.frameIndex[i]..".png")
				local spriteFrame = cc.SpriteFrame:create(path,cc.rect(imageInfo.x,imageInfo.y,imageInfo.w,imageInfo.h),false,cc.p(imageInfo.ox,imageInfo.oy),cc.size(imageInfo.w,imageInfo.h))
				spriteFrame:getTexture()
				local animFrame = CCAnimationFrame:new()
				animFrame:initWithSpriteFrame(spriteFrame,v.delayArray[i],nil)
				animFrame:autorelease()
				frameArray:addObject(animFrame)
			end
			local animation = CCAnimation:create(frameArray,1/1000,1)
			animation:setRestoreOriginalFrame(true)
			CC_SAFE_RETAIN(animation)
			cache.animations[k] = animation
		end
	end

	return true
end

function GameCache.getCharacter(character)
	local cache = GameCache._CharacterCaches[character]
	return cache
end

return GameCache