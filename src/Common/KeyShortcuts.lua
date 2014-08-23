----------------------------------------------------
-- 					快捷键模块					  --
----------------------------------------------------
local KeyShortcuts = class("KeyShortcuts")
KeyShortcuts.__index = KeyShortcuts

--@param name 快捷键方案名
function KeyShortcuts:ctor(name)
	self._name = name
	self._keys = {}
end

local log = 
{
	[single_type] = "",
	[alt_type] = "ALT+",
	[ctrl_type] = "CTRL+",
	[shift_type] = "SHIFT+",
	[a_c_type] = "ALT+CTRL+",
	[a_s_type] = "ALT+SHIFT+",
	[s_c_type] = "CTRL+SHIFT+",
	[a_c_s_type] = "ALT+CTRL+SHIFT+",
}

--- 添加单快捷键键值和回调函数
--@param key 保存单一键值字符串
--eg. key = "KEY_ALT"
--@param type 组合键,现在可与alt,ctrl,shift,alt+ctrl,alt+shift,ctrl+shift,alt+ctrl+shift组合
--@param pfunc press时的回调函数
--@param rfunc release时的回调函数
function KeyShortcuts:add(type,key,pfunc,rfunc)
	local keycode = cc.KeyCode[key]
	if not self._keys[type] then
		self._keys[type] = {}
	end
	cclog("添加快捷键:"..log[type]..key)
	self._keys[type][keycode] = { OnPressed = pfunc, OnReleased = rfunc }
end

function KeyShortcuts:callPFunc(type,key)
	if self._keys[type] and self._keys[type][key] and self._keys[type][key].OnPressed then
		cclog("按下快捷键:"..log[type]..cc.KeyCodeKey[key+1])
		self._keys[type][key].OnPressed()
	end
end

function KeyShortcuts:callRFunc(type,key)
	if self._keys[type] and self._keys[type][key] and self._keys[type][key].OnReleased  then
		cclog("放开快捷键:"..log[type]..cc.KeyCodeKey[key+1])
		self._keys[type][key].OnReleased()
	end
end

return KeyShortcuts
