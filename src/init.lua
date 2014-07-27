require("frameworkConfig")
require("framework.init")
stack = require("Common.stack")
vector = require("Common.vector")
require("command.init")
require("config")
--require("opcodes")
sharedFileUtils:addSearchPath("res")
sharedFileUtils:addSearchPath("res/Editor")
--sharedFileUtils:addSearchPath("res/dbc")

sharedDirector:getOpenGLView():setFrameSize(config.width,config.height)
sharedDirector:getOpenGLView():setDesignResolutionSize(config.designWidth,config.designHeight,config.policy)
sharedDirector:setDisplayStats(config.fps)
cc.init()


