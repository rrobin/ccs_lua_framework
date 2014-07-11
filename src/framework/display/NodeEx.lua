local c = cc
local Node = c.Node

function Node:load(character)
	if display.GameCache.preload(character) then
		self._info = display.GameCache.getCharacter(character)
	end
	assert(self._info)
	self:playAction("default")
end

function Node:playAction(action,looptimes)
	self:stopActionByTag(playActTag)
	local animation = self._info.animations[action]
	if not animation then
		cclog("not find action:"..action)
		return
	end
	local beginFrame = tolua.cast(animation:getFrames():objectAtIndex(0),"CCAnimationFrame")
	self:setDisplayFrame(beginFrame:getSpriteFrame())
	local animate = CCAnimate:create(animation)
	local action = nil
	if not looptimes or looptimes < 0 then
		action = CCRepeatForever:create(animate)
	else
		action = CCRepeat:create(animate,looptimes)
	end

	action:setTag(playActTag)
	self:runAction(action)
end