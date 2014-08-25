local ProjectManager = class("ProjectManager")
ProjectManager.__index = ProjectManager

local f = sharedFileUtils

scene = 
{
	name = "newScene",
	ext = ".sce",
}

project= 
{
	workpath = lfs.currentdir(),
	name = "NewProject",
	ext = ".proj",
	Scenes = {},
}

function ProjectManager:ctor()
	self._project = clone(project)
end

-- Public Functions
function ProjectManager:newProject(name,workpath)
	local p = workpath or self._project.workpath
	local n = name or self._project.name
	self._project.workpath = p
	self._project.name = n
	EditorConfig:addProj(self._project)
end

function ProjectManager:save()
	local jsonData = {}
	local p = self._project.workpath
	local ss = self._project.Scenes

	jsonData["Scenes"] = ss
	if ss then 
		for _,v in pairs(ss) do
			SceneManager:Save(p,v.name,v.ext)
		end
	end

	local json_str = json.encode(jsonData)
	local filePath = p.."/"..self._project.name..self._project.ext
	local file = io.open(filePath,"w+")
	if file then
		file:write(json_str) 
		file:close()
	end
end

function ProjectManager:load(path)
	local p = path or self._project.workpath
	local t = fs.Browse(path,"%"..self._project.ext,-1)
	if not t then
		assert(false,"在目录"..path.."下没有找到项目文件")
	end
	if #t > 1 then
		assert(fasle,"找到多个项目文件")
	end
	self._project.workpath = p
	local file = io.open(p.."/"..t[1])
	if file then
		local json_str = file:read("*a")
		json_str = json.decode(json_str,1)
		local ss = json_str["Scenes"]
		for _,v in pairs(ss) do
			SceneManager:Load(p.."/"..v.name..v.ext)
		end
		file:close()
	else
		assert(false,"没有找到目标文件")
	end
	EditorConfig:openProj(self._project)
end

function ProjectManager:newScene(name)
	local s = clone(scene)
	s.name = name
	self._project.Scenes[#self._project.Scenes+1] = s
	return SceneManager:addScene(name,960*2)
end

return ProjectManager