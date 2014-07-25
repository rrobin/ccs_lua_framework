local c = cc
local Layer = c.Layer
local ui = ccui
local helper = ui.Helper

function Layer:load(filename)
        local widget = ccui.loadWidget(filename)
        if widget then
            self:addChild(widget)
            if not self.group then
                self.group = {}
            end
        else
            assert(false,string.format("layer:load -invalid file :\"%s \" ",filename))
        end
        return self
end

function Layer:update( dt )
    
end

function Layer:getChild(name)
    while true
    do
    if not name then break end
    local children = self:getChildren()
    local uiwidget = nil
    for _,v in ipairs(children) do
        if string.find(tolua.type(v),"ccui.") ~= nil then
            if type(name) == "string" then
                uiwidget = helper:seekWidgetByName(v,name)
            elseif type(name) == "number" then
                uiwidget = helper:seekWidgetByTag(v,name)
            end
        end 
    end
    return uiwidget
    end
end

function Layer:insterGroup(groupId,...)
    local arg = {...}
    for i,v in ipairs(arg) do
        if v == nil then
            assert(false,string.format("CCSLayerExtend:insterGroup error : invalid checkBox :%d",i))
        elseif v:getDescription() ~= UI_CHECKBOX then
            assert(false,"CCSLayerExtend:insterGroup error : only support UICheckBox")
        elseif type(groupId) ~= "number" then
            assert(false,"CCSLayerExtend:insterGroup error : #1 groupId expected number")
        elseif groupId < 1 then
            assert(false,"CCSLayerExtend:insterGroup error : groupId must start at 1")
        else 
            if not self.group then self.group = {} end
            if self.group[groupId] == nil then
                self.group[groupId] = {}
            end
            self.group[groupId][#self.group[groupId]+1] = v
        end
    end
end

function Layer:GroupDefault(groupId,checkbox)
     if self.group then
        local group = self.group[groupId]
        if group then
            for i,v in ipairs(group) do
                if v ~= checkbox then
                    v:setSelectedState(false)
                else
                    v:setSelectedState(true)
                end
            end 
        end
    end
end

function Layer:GroupSelected(groupId,checkbox)
    if self.group then
        local group = self.group[groupId]
        if group then
            for i,v in ipairs(group) do
                if v ~= checkbox then
                    v:setSelectedState(false)
                else
                    v:setSelectedState(true)
                end
            end 
        end
    end
end

