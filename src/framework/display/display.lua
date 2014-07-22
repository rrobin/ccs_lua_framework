display = display or {}
cclog("required display module")
display.GameCache = import(".GameCache")
import(".NodeEx")
--cclog("shader extend will coming soon..")
import(".SpriteEx")
--[[
    display保存一份所有shaders的表
    sprite使用shader时,都在此表中来查找,并自己克隆维护一份shader结构表
    shader的结构表为=
    {
      n, -- shader的名称,用于检索
      v, -- shader的顶点着色器,可以是代码片段,也可以是代码文件名
      f, -- shader的像素着色器,同参数v
    }
]]

--d.shaders = {}
function display.addShader(shader)
    local name = shader.n
    local vsh = shader.v
    local fsh = shader.f
    local Progam = display.getShader(name)
    if Progam then return end
    local fileUtiles = cc.FileUtils:getInstance()
    if string.find(vsh,".vsh") ~= nil then
        vsh = fileUtiles:getStringFromFile( vsh )
    end

    if string.find(fsh,".fsh") ~= nil then
        fsh = fileUtiles:getStringFromFile( fsh )
    end
    Progam = cc.GLProgram:createWithByteArrays( vsh, fsh )
    local ProgamCache = cc.GLProgramCache:getInstance()
    ProgamCache:addGLProgram( Progam, name )
    cclog("add shader : ".. name)
end

function display.getShader(name)
    --return d.shaders[name]
    local ProgamCache = cc.GLProgramCache:getInstance()
    return ProgamCache:getGLProgram(name)
end