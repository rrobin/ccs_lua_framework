-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

require("init")

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    local shaders = { {v = "shaders/TPC_noMvp.vsh", f = "shaders/BanishShader.fsh", n = "BanishShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/FrozenShader.fsh", n = "FrozenShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/GrayScalingShader.fsh", n = "GrayScalingShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/IceShader.fsh", n = "IceShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/PoisonShader.fsh", n = "PoisonShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/StoneShader.fsh", n = "StoneShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/bright.fsh", n = "brightShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/outline.fsh", n = "outline"},
    --{v = "shaders/TPC_noMvp.vsh", f = "shaders/ghostlike_filterX.fsh", n = "ghostlike_filterX"},
    }
    for k,v in ipairs(shaders) do
        display.addShader(v)
    end
    require("MyApp"):new()
end

xpcall(main, __G__TRACKBACK__)
