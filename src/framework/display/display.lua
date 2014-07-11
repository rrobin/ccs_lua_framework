display = display or {}
cclog("required display module")
display.GameCache = import(".GameCache")
import(".NodeEx")
--cclog("shader extend will coming soon..")
import(".SpriteEx")

function display.addShader(vsh,fsh,shaderName)
	local ProgamCache = cc.GLProgramCache:getInstance()
    local Progam = ProgamCache:getGLProgram(shaderName)
    if Progam then return end
    local fileUtiles = cc.FileUtils:getInstance()
    if string.find(vsh,".vsh") ~= nil then
        vsh = fileUtiles:getStringFromFile(vsh)
    end

    if string.find(fsh,".fsh") ~= nil then
        fsh = fileUtiles:getStringFromFile(fsh)
    end
    Progam = cc.GLProgram:createWithByteArrays(vsh, fsh)
    ProgamCache:addGLProgram(Progam,shaderName)
    cclog("add shader : "..shaderName)
end