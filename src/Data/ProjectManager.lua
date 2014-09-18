SimulatorType = 
{
   IPhone4 = 1,		-- 480x320
   IPhone4HD = 2, 	-- 960x640
   IPhone5 = 3,		-- 1136x640
   IPhone6 = 4,		--
   IPad	   = 5,		-- 1024x768
   IPadHD  = 6,		-- 2048x1536
}

SimulatorSize =
{
 	{width = 480,height = 320},		-- ip4
 	{width = 960,height = 640},		-- ip4HD
 	{width = 1136,height = 640},	-- ip5
 	{width = 480,height = 320},		-- ip6
 	{width = 1024,height = 768},	-- ipad
 	{width = 2048,height = 1536},	-- ipadHD
}

SimulatorDesignFactor = 
{
	1,			-- ip4
	0.5,		-- ip4HD
	0.5,		-- ip5
	0.5,		-- ip6
	0.5,		-- ipad
	0.5, 		-- ipadHD
}

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
	ptype = SimulatorType.IPhone4HD,       --iphone 机型
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

    cclog(" p:"..p.." ss:"..#ss)
	jsonData["Scenes"] = ss
    --jsonData["width"] = self._project.width
    --jsonData["height"] = self._project.height
    
    jsonData["ptype"] = self._project.ptype
    
	if ss then 
		for _,v in pairs(ss) do
			SceneManager:Save(p,v.name,v.ext)
		end
	end
    cclog(" after scenemanager save")
	local json_str = json.encode(jsonData)
	local filePath = p.."/"..self._project.name..self._project.ext
	cclog("ProjectManager save:"..filePath)
	local file = io.open(filePath,"w+")
	if file then
		file:write(json_str) 
		file:close()
	end
end

function ProjectManager:load(path)
	cclog(" ProjectManager load :"..path)
	local p = path or self._project.workpath

	local t = fs.Browse(path,"%"..self._project.ext,-1)
	if not t then
		assert(false,"在目录"..path.."下没有找到项目文件")
	end
	if #t > 1 then
		assert(fasle,"找到多个项目文件")
	end
	self._project.workpath = p
	local fname = string.ipextension(t[1])
	self._project.name = fname
	local file = io.open(p.."/"..t[1])

	if file then
		local json_str = file:read("*a")
		cclog(" json_str:"..json_str)
		json_str = json.decode(json_str,1)
		local ss = json_str["Scenes"]

		--self._project.width = json_str["width"]
        --self._project.height = json_str["height"]

        self._project.ptype = json_str["ptype"]

        self._project.Scenes = ss   -- 加载时重新赋值
		for k,v in pairs(ss) do
            --SceneManager:Load(p.."/"..v.name..v.ext)
            SceneManager:Load(p.."/Scenes/"..v.name..v.ext)
		end
		file:close()
	else
		assert(false,"没有找到目标文件")
	end
	EditorConfig:openProj(self._project)
	return self._project
end

function ProjectManager:newScene(name,width)
	local s = clone(scene)
	s.name = name
	self._project.Scenes[#self._project.Scenes+1] = s
	if width then 
        return SceneManager:addScene(name,width)
    else
    	return SceneManager:addScene(name,960*2) 
	end
	
end


function ProjectManager:prevload(path)
	cclog(" ProjectManager prevload ")
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
		cclog(" json_str:"..json_str)
		json_str = json.decode(json_str,1)
		local scenes = json_str["Scenes"]
		local ss = scenes[1]
		self._project.Scenes = ss   -- 加载时重新赋值
		--[[for k,v in pairs(ss) do
			SceneManager:Load(p.."/"..v.name..v.ext)
		end]]
		--SceneManager:prevLoad(p.."/"..ss.name..ss.ext)
		file:close()
	else
		assert(false,"没有找到目标文件")
	end
end



return ProjectManager