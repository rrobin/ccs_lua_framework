import(".KeyConstants")
KeyShortcuts = import(".KeyShortcuts")

local KeyBoardManager = class("KeyBoardManager")
KeyBoardManager.__index = KeyBoardManager

function KeyBoardManager:ctor()
	self._solutions = {}
	self._using = nil
	self._type = single_type
	local eventDispatcher = sharedDirector:getEventDispatcher()
	local keyBoard = cc.EventListenerKeyboard:create()
	keyBoard:registerScriptHandler(handler(self,self.PressedKey),cc.Handler.EVENT_KEYBOARD_PRESSED)	
	keyBoard:registerScriptHandler(handler(self,self.ReleasedKey),cc.Handler.EVENT_KEYBOARD_RELEASED)
	eventDispatcher:addEventListenerWithFixedPriority(keyBoard,1)
end

function KeyBoardManager:add(keyshortcuts)
	assert(self._solutions[keyshortcuts._name] == nil,"已经存在的方案,采用新的"..keyshortcuts._name.."方案")
	self._solutions[keyshortcuts._name] = keyshortcuts
end

function KeyBoardManager:getShortcuts(name)
	return self._solutions[name]
end

function KeyBoardManager:apply(name)
	self._using = self:getShortcuts(name)
	return self._using ~= nil
end

function KeyBoardManager:PressedKey(keycode,event)
	--cclog("pressed key:%d",keycode)
	if cc.KeyCode["KEY_ALT"] == keycode then
		self._type = bor(self._type,alt_type)
	end

	if cc.KeyCode["KEY_CTRL"] == keycode then
		self._type = bor(self._type,ctrl_type)
	end

	if cc.KeyCode["KEY_SHIFT"] == keycode then
		self._type = bor(self._type,shift_type)
	end

	--cclog("press a_c_key:"..self._type)
	if self._using then
		local shortcut = self._using
		shortcut:callPFunc(self._type,keycode)
	end
end

function KeyBoardManager:ReleasedKey(keycode,event)
	--cclog("release key:%x",keycode)
	if cc.KeyCode["KEY_ALT"] == keycode then
		self._type = band(self._type,bnot(alt_type))
	end

	if cc.KeyCode["KEY_CTRL"] == keycode then
		self._type = band(self._type,bnot(ctrl_type))
	end

	if cc.KeyCode["KEY_SHIFT"] == keycode then
		self._type = band(self._type,bnot(shift_type))
	end

	--cclog("release a_c_key:"..self._type)
	if self._using then
		local shortcut = self._using
		shortcut:callRFunc(self._type,keycode)
	end
end

return KeyBoardManager