require("frameworkConfig")
require("framework.init")
stack = require("Common.stack")
vector = require("Common.vector")
require("config")
require("lfs")
cjson = require('cjson').new()
require('Common.fileSystem')
require('Common.LuaXml')

sharedFileUtils:addSearchPath("res")
sharedFileUtils:addSearchPath("res/Editor")

sharedDirector:getOpenGLView():setFrameSize(config.width,config.height)
sharedDirector:getOpenGLView():setDesignResolutionSize(config.designWidth,config.designHeight,config.policy)
sharedDirector:setDisplayStats(config.fps)
sharedDirector:setAnimationInterval(1.0/config.interval)
cc.init()


