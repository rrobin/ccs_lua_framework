local ui = ccui
local layout = ui.Layout

function layout:initlayout(params)
    if not params.size then params.size = ccs.DEFAULT_LAYOUT_SIZE end
    local color         = params.color
    local endColor      = params.endColor
    local colorType     = params.colorType
    local image         = params.image
    local scale9        = params.scale9
    local capInsets     = params.capInsets or ccs.DEFAULT_CAPINSETS
    local ltype         = params.type
    local clip          = params.clip
    local opacity       = params.opacity


    local init = true
   
    while true
    do
        init = self:init(params)
        if init == false then break end
    --[[
        init = (tolua.type(size) == "CCSize")
        assert(init,"layout invalid params.size")
        self:setSize(size)
    ]]
        if colorType then
            self:setBackGroundColorType(colorType)
            if colorType == LAYOUT_COLOR_GRADIENT then
                if color and endColor then
                    init = (type(color) == "table")
                    assert(init,"layout invalid params.color")
                    init = (tolua.type(endColor) == "ccColor3B")
                    assert(init,"layout invalid params.endColor")
                    if init == false then break end
                    self:setBackGroundColor(color,endColor)
                end
            else
                if color then
                    init = (type(color) == "table")
                    assert(init,"layout invalid params.color")
                    if init == false then break end
                    self:setBackGroundColor(color)
                end
            end
        end

        if image then
            self:setBackGroundImage(image)
        end

        if scale9 then
            self:setBackGroundImageScale9Enabled(scale9)
            self:setBackGroundImageCapInsets(capInsets)
        end

        -- layout 的布局方式
        if ltype then
            self:setLayoutType(ltype)
        end

        if clip then
            assert(type(clip) == "boolean", "layout invalid params.clip")
            self:setClippingEnabled(clip)
        end

        if opacity then
            assert(type(opacity) == "number", "layout invalid params.opacity")
            self:setBackGroundColorOpacity(opacity)
        end
--[[
        if listener then
            init = (type(listener) == "table")
            if init == false then break end
            self:addTouchEvent(listener)
        end

        SET_POS(self,x,y)
]]
        break
    end
    return init
end

-- ccsmenu extend
function layout:AutoLayout(margin,... )
    local args = {...}
    local type = self:getLayoutType()
    for i,button in ipairs(args) do
        assert(tolua.type(button) == widget_table[UI_BUTTON].name,"[layout.AutoLayout] need UIButton params")
        local lp = UILinearLayoutParameter:create()
        if type == LAYOUT_ABSOLUTE then
            return
        elseif type == LAYOUT_LINEAR_VERTICAL then
            lp:setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL)
            if i == 1 then
                lp:setMargin({0,0,0,margin/2})
            else
                lp:setMargin({0,margin/2,0,margin/2})
            end 
        elseif type == LAYOUT_LINEAR_HORIZONTAL then
            lp:setGravity(LINEAR_GRAVITY_CENTER_VERTICAL)
            if i == 1 then
                lp:setMargin({0,0,margin/2,0})
            else
                lp:setMargin({margin/2,0,margin/2,0})
            end 
        elseif type == LAYOUT_RELATIVE then
        end
        button:setLayoutParameter(lp)
        self:addChild(button)
    end
    self:doLayout()
end