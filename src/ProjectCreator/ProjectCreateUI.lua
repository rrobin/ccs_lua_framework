local ProjectCreateUI = class("ProjectCreateUI", function() return cc.Scene:create() end)
ProjectCreateUI.__index = ProjcetCreateUI

local SceneEditor = require("SceneEditor.ui.SceneEditorUI")


function ProjectCreateUI:ctor()
	local layer = ccui.loadLayer("ProjectCreateUI.ExportJson")

	self._layer = layer
	self:addChild(layer)

	local creator = layer:getChild("ProjectCreatorPanel")
	creator:setVisible(false)
	creator:setTouchEnable(false)
	self._creator = creator

	local NameFrame = creator:getChild("NameFrame")
	local PathFrame = creator:getChild("PathFrame")
	local nameTextField = creator:getChild("NameTextField")
	local _prevWidget = nil
	local _again = false
	nameTextField:addTouchEvent({[ccui.TouchEventType.began] =  function(uiwidget)
		if _prevWidget == uiwidget then
			_again = true
		end
		NameFrame:loadTexture("exchange_pic021.png",ccui.TextureResType.plistType)
		_prevWidget = uiwidget
		end})
	nameTextField:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = function(uiwidget)
		if _again == false then
			NameFrame:loadTexture("exchange_pic02.png",ccui.TextureResType.plistType)
		else
			_again = false
		end
		end})
	local textField = creator:getChild("PathTextField")
	textField:addTouchEvent({[ccui.TouchEventType.began] =  function(uiwidget)
		if _prevWidget == uiwidget then
			_again = true
		end
		PathFrame:loadTexture("exchange_pic021.png",ccui.TextureResType.plistType)
		_prevWidget = uiwidget
		end})
	textField:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = function(uiwidget)
		if _again == false then
			PathFrame:loadTexture("exchange_pic02.png",ccui.TextureResType.plistType)
		else
			_again = false
		end
		end})

	local BrowseBtn = creator:getChild("BrowseBtn")
	BrowseBtn:addTouchEvent({[ccui.TouchEventType.ended] =  handler(self,self.Browse)})

	local SureBtn = creator:getChild("SureBtn")
	SureBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.createProject)})

	local CancelBtn = creator:getChild("CancelBtn")
	CancelBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.closeCreator)})

	local newProjectBtn = layer:getChild("NewBtn")
	newProjectBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.openCreator)})

	local openProjectBtn = layer:getChild("OpenBtn")
	openProjectBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.openProject)})

    self._projInfoList = {} -- 用来存储工程信息列表
     
    self:initRecentProj()
end


function ProjectCreateUI:initRecentProj()

    local projL = self._layer:getChild("ProjectList")
    local objItem = ccui.label({text="project"}) 
	projL:setItemModel(objItem) 
	local projnum = EditorConfig:getRecentlyProj():count()
	local recentProjs = EditorConfig:getRecentlyProj()._values

	local i = 1
	for j=1,projnum do
        if recentProjs[projnum+1-j] then
            local namev = recentProjs[projnum+1-j].name
            local pathv = recentProjs[projnum+1-j].workpath
            --local projInfo = {name=namev,path=pathv}
            self._projInfoList[namev] = pathv
            projL:pushBackDefaultItem()
            local item = projL:getItem(i-1)
            item:setTag(i)
            item:addTouchEvent({[ccui.TouchEventType.ended] = function(widget)
				local itemText = item:getString()
				for k,v in pairs(self._projInfoList) do
    				if k == itemText then
					    ProjectManager:load(v)
					    local scene = SceneEditor.new(k)
						cc.runScene(scene)
    				end
				end
				--[[local text = ptBtn:getTitleText()
	            ptBtn:setTitleText(v.text)
	            v.func()]]
			end})
			item:setString(namev)
			i = i+1
        end
	end

end

function ProjectCreateUI:Browse()
	local Path = PlatformUtility:OpenFolder(lfs.currentdir())
	local textField = self._creator:getChild("PathTextField")
	textField:setString(Path)
end

function ProjectCreateUI:createProject()
	cclog("---ProjectCreateUI:createProject---")
	local path = self._creator:getChild("PathTextField"):getString()
	local name = self._creator:getChild("NameTextField"):getString()
	local workpath = path.."\\"..name
	local err = fs.mkdir(workpath)

    local scenepath = workpath.."/Scenes"
    local errs = fs.mkdir(scenepath)
    local respath = workpath.."/Res"
    local errr = fs.mkdir(respath)
    

	if err ~= nil then
		ProjectManager:newProject(name,workpath)
		ProjectManager:save()
        local scene = SceneEditor.new(name)
		cc.runScene(scene)
	end
end

function ProjectCreateUI:openCreator()
	self._creator:setVisible(true)
	self._creator:setTouchEnable(true)
	local nameTextField = self._creator:getChild("NameTextField")
	nameTextField:setString("newProject")
	local textField = self._creator:getChild("PathTextField")
	textField:setString(lfs.currentdir())
end

function ProjectCreateUI:closeCreator()
	self._creator:setVisible(false)
	self._creator:setTouchEnable(false)
end

function ProjectCreateUI:openProject()

	--local filename = PlatformUtility:OpenFile("E:\\","Png;Jpg(*.png,*.Jpg)\0*.png;*.jpg;*.plist;*.ExportJson\0")
    --local filename = PlatformUtility:OpenFile("E:\\Tools\\3.xEditor","*.proj\0")
    local filename = PlatformUtility:OpenFolder(lfs.currentdir())
    local t = fs.Browse(filename,"%.proj",1)
    if not t then
		assert(false,"在目录"..path.."下没有找到项目文件")
	end
	if #t > 1 then
		assert(fasle,"找到多个项目文件")
	end
    --cclog(" open project t:"..t[1])
    ProjectManager:load(filename)
    local scene = SceneEditor.new(t[1])
	cc.runScene(scene)

end



return ProjectCreateUI