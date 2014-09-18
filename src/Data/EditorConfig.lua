local EditorConfig = class("EditorConfig")
EditorConfig.__index = EditorConfig

function EditorConfig:ctor()
	self._filepath = lfs.currentdir()
	local t = fs.Browse(lfs.currentdir(),"Editor.config",1)
	if not t then
		cclog("没有找到编辑器配置文件!")
		self:mkConfig()
		return
	end
	if #t > 1 then
		assert(false,"不可能发生!")
	end
	self:Load(lfs.currentdir().."/Editor.config")
end

function EditorConfig:mkConfig()
	self._config = {}
	local config = self._config
	config["Recently"] = stack.new(5)
	config["last"] = nil
	self:Save()
end

function EditorConfig:Save()
	local config = {}
	config["Recently"] = self._config["Recently"]._values
	config["last"] = self._config["last"]
	local json_str = json.encode(config)
	local f = io.open(self._filepath.."/Editor.config","w+")
	if f then
		f:write(json_str)
		f:close()
	end
end

function EditorConfig:Load(filePath)
	local f = io.open(filePath)
	if f then
		local json_str = f:read("*a")
		json_str = json.decode(json_str)
		local s = json_str["Recently"]
		if not self._config then
			self._config = {}
			self._config["Recently"] = stack.new(5)
			self._config["last"] = json_str["last"]
		end
		for _,v in pairs(s) do
			self._config["Recently"]:push(v)
		end
		f:close()
	end
end

function EditorConfig:getRecentlyProj()
	return self._config["Recently"]
end

function EditorConfig:getLastProj()
	return self._config["last"]
end

function EditorConfig:addProj(project)
	local p = {}
	p.workpath = project.workpath
	p.name = project.name
	self._config["Recently"]:push(p)
end

function EditorConfig:openProj(project)
	local p = {}
	p.workpath = project.workpath
	p.name = project.name
	self._config["last"] = p
end

return EditorConfig