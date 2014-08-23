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

--- 添加单快捷键键值和回调函数
--@param key 保存单一键值字符串
--eg. key = "KEY_ALT"
--@param func 回调函数
--@param type 组合键,现在可与alt,ctrl,shift,alt+ctrl,alt+shift,ctrl+shift,alt+ctrl+shift组合
function KeyShortcuts:add(key,func,rfunc,type)
	local keycode = cc.KeyCode[key]
	if not self._keys[type] then
		self._keys[type] = {}
	end
	self._keys[type][keycode] = { press = func, release = rfunc }
end

function KeyShortcuts:callFunc(type,key)
	if self._keys[type] and self._keys[type][key] and self._keys[type][key].press then
		self._keys[type][key].press()
	end
end

function KeyShortcuts:callReleaseFunc(type,key)
	if self._keys[type] and self._keys[type][key] and self._keys[type][key].release  then
		self._keys[type][key].release()
	end
end

return KeyShortcuts
