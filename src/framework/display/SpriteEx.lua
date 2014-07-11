local c = cc
local Sprite = c.Sprite

function Sprite:setShader(shaderName)
    local glprogram = cc.GLProgramCache:getInstance():getGLProgram(shaderName)
    if glprogram then
        cclog("setShader "..shaderName)
        self:setGLProgram(glprogram)
        self:setDirty(true)
    end
end