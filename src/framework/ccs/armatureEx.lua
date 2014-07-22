local c = cc
local s = ccs
local armature = s.Armature
local d = display

function armature:setFilter(filter,...)
    local Progam = d.getShader(filter)
    if not Progam then
    	cclog("not find filter "..filter)
    	return
    end
    local args = {...}
    local boneNames = "*"
    if args[1] then
    	if #args > 1 then
	    	boneNames = {}
	    	for k,v in pairs(args) do
	    		boneNames[v] = true
	    	end
	    else
	    	boneNames = args[1]
	    end
    end

    local function BoneSetFilter(bone,filter)
    	local displayType = bone:getDisplayRenderNodeType()
        if displayType == s.DisplayType.sprite then
            local render = bone:getDisplayRenderNode()
            render:setShader(filter)
        end
    end

    if boneNames == "*" or type(boneNames) == "table" then
	    local bones = self:getBoneDic()
	    for name,bone in pairs(bones) do
	    	if boneNames == "*" or boneNames[name] ~= nil then
		        BoneSetFilter(bone,filter)
	    	end
	    end
	else
		local bone = self:getBone(boneNames)
		BoneSetFilter(bone,filter)
	end
end

function armature:setUniform(uniform,value,...)
	local args = {...}
    local boneNames = "*"
    if args[1] then
    	if #args > 1 then
	    	boneNames = {}
	    	for k,v in pairs(args) do
	    		boneNames[v] = true
	    	end
	    else
	    	boneNames = args[1]
	    end
    end

    local function BoneSetUniform(bone,name,value)
    	local displayType = bone:getDisplayRenderNodeType()
        if displayType == s.DisplayType.sprite then
            local render = bone:getDisplayRenderNode()
            render:setUniform(name,value)
        end
    end

    if boneNames == "*" or type(boneNames) == "table" then
	    local bones = self:getBoneDic()
	    for name,bone in pairs(bones) do
	    	if boneNames == "*" or boneNames[name] ~= nil then
		        BoneSetUniform(bone,uniform,value)
	    	end
	    end
	else
		local bone = self:getBone(boneNames)
		BoneSetUniform(bone,uniform,value)
	end
end