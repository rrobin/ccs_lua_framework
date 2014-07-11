local ui = ccui
local helper = ui.Helper
local Widget = ui.Widget

function Widget:init(params)
    cclog(tolua.type(self))
    local enabled = params.enabled
    local visible = params.visible
    local touchable = true
    if params.touch ~= nil then
        touchable = params.touch
    end
    local bright    = params.bright
    local foucs     = params.foucs
    local zOrder    = params.z
    local tag       = params.tag
    local color     = params.color
    local size      = params.size
    local sizeType  = params.sType
    local positionType = params.pType
    local x            = params.x or 0
    local y            = params.y or 0
    local name         = params.name
    local listener     = params.listener

    local init = true
    
    while true
    do
        if enabled then
            init = (type(enabled) == "boolean")
            assert(init,"widget invaild params.enabled")
            if init == false then break end
            self:setEnabled(enabled)
        end

        if visible then
            init = (type(visible) == "boolean")
            assert(init,"widget invaild params.visible")
            if init == false then break end
            self:setVisible(visible)
        end

        if touchable then
            init = (type(touchable) == "boolean")
            assert(init,"widget invaild params.touch")
            if init == false then break end
            self:setTouchEnabled(touchable)
        end

        if bright then
            init = (type(bright) == "boolean")
            assert(init,"widget invaild params.bright")
            if init == false then break end
            self:setBright(bright)
        end

        if foucs then
            init = (type(foucs) == "boolean")
            assert(init,"widget invaild params.foucs")
            if init == false then break end
            self:setFocused(foucs)
        end

        if zOrder then
            init = (type(zOrder) == "number")
            assert(init,"widget invaild params.z")
            if init == false then break end
            self:setZOrder(zOrder)
        end
        
        if name then
            init = (type(name) == "string")
            assert(init,"widget invaild params.name")
            if init == false then break end
            self:setName(name)
        end

        if tag then
            init = (type(tag) == "number")
            assert(init,"widget invaild params.tag")
            if init == false then break end
            self:setTag(tag)
        end

        if color then
            init = (tolua.type(color) == "ccColor3B" or tolua.type(color) == "const ccColor3B")
            assert(init,"widget invalid params.color")
            if init == false then break end
            self:setColor(color)
        end

        if size then
            init = (tolua.type(size) == "CCSize" or tolua.type(size) == "const CCSize")
            assert(init,"widget invaild params.size")
            if init == false then break end
            self:setSize(size)
        end

        if sizeType then
            cclog(type(sizeType))
            self:setSizeType(sizeType)
        end

        if positionType then
            cclog(type(positionType))
            self:setPositionType(positionType)
        end

        SET_POS(self,x,y)

        if listener then
            init = (type(listener) == "table")
            assert(init,"widget invaild params.listener")
            if init == false then break end
            self:addTouchEvent(listener)
        end

        break
    end

    return init
end

function Widget:getChild(name)
    local child = nil
    while true
    do
    if not name then break end
    local uiwidget = nil
    if type(name) == "string" then
        uiwidget = helper:seekWidgetByName(self,name)
    elseif type(name) == "number" then
        uiwidget = helper:seekWidgetByTag(self,name)
    end
    if not uiwidget or not widget_table[uiwidget:getDescription()] then break end
    child = tolua.cast(uiwidget,widget_table[uiwidget:getDescription()].name)
    break
    end
    return child
end

function Widget:FadeToEx( duration, opacity )
    for i = 1,self:getChildren():count() do
        local child = tolua.cast(self:getChildren():objectAtIndex(i-1),widget_table[UI_WIDGET].name)
        if child then child:runAction(CCFadeTo:create(duration,opacity)) end
    end
end

function Widget:getPosition()
    return cc.p(self:getPositionX(),self:getPositionY())
end

function Widget:addTouchEvent(params)
    while true
    do
        if params and type(params) ~= "table" then return end
        local defaultCallbacks = 
        {
            [ui.TouchEventType.state_change_to_normal]     = handler(self,self.onPressStateChangedToNormal),
            [ui.TouchEventType.state_change_to_pressed]    = handler(self,self.onPressStateChangedToPressed),
            [ui.TouchEventType.state_change_to_disabled]   = handler(self,self.onPressStateChangedToDisabled),
        }
        if params and table.nums(params) ~= 0 then
            table.merge(defaultCallbacks,params)
        end
        self.listener = defaultCallbacks
        handle = function(uiwidget,event)
            if self.listener[event] then
               self.listener[event](uiwidget)
            end
        end
        self:addTouchEventListener(handle)
        break
    end
end

function Widget:onPressStateChangedToNormal(uiwidget)
end

function Widget:onPressStateChangedToPressed(uiwidget)
end

function Widget:onPressStateChangedToDisabled(uiwidget)
end

function Widget:getWidgetParent()
    return tolua.cast(self:getParent(),UI_WIDGET)
end

function Widget:setTouchEnable(enable,child)
    self:setTouchEnabled(enable)
    if child then
        local children = self:getChildren()
        for i=0,self:getChildrenCount()-1 do
            local widget = tolua.cast(children:objectAtIndex(i),UI_WIDGET)
            widget = widget_table[UI_WIDGET].extend(widget)
            widget:setTouchEnable(enable,child)
        end
    end
end