require("frameworkConfig")
require("framework.init")
stack = require("Common.stack")
vector = require("Common.vector")
require("command.init")
require("config")

brtFilter = require("filter.brightness")
hueFilter = require("filter.hue")

ccs.registerTriggerClass("brightShader",brtFilter.new)
ccs.registerTriggerClass("hueShader",hueFilter.new)

SceneManager = require("SceneEditor.Manager").new()
--require("opcodes")
sharedFileUtils:addSearchPath("res")
sharedFileUtils:addSearchPath("res/Editor")
sharedFileUtils:addSearchPath("res/test")
--sharedFileUtils:addSearchPath("res/dbc")

sharedDirector:getOpenGLView():setFrameSize(config.width,config.height)
sharedDirector:getOpenGLView():setDesignResolutionSize(config.designWidth,config.designHeight,config.policy)
sharedDirector:setDisplayStats(config.fps)
sharedDirector:setAnimationInterval(1.0/config.interval)
cc.init()


