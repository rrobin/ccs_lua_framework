uber = uber or {}
--[[
	ver 2.0.0 完全升级到cocos2dx-v2.2.3
	ver 2.0.1 升级GameObject读取ActionInfo
	ver 2.0.2 修改了本地文件存在与否的判断函数,增加了一些对老版本兼容的接口
	ver 3.0.0 基于cocos2dx-3.2alpha0
			  原本的ccs库更名为ccui,现在的ccs库为骨骼动画
			  更新了c++类的扩展方式
			  添加了deprecate模块
			  修改了display模块
			  	-去掉了2.x版本的ShaderExten模块,采用3.x的ShaderEx
			  	-增加了display.addShader函数
			  	-支持对jpg+I8 mask这样的组合方式创建sprite
			  	-增加了一个sprite自动根据文件名来创建对象的函数:AutoCreate(filename)
			  增加了audio模块
			  增加Opengl模块
			  增加helper模块
	ver 3.0.1 升级到cocos2dx-3.2rc0
			  display模块
			  	-废除shaderEx,增加spriteEx
			  	-NodeEx添加了对于shader的扩展
			  ccs模块
			  	-增加了armatureEx,封装了对armature的Bone添加滤镜
]]
uber.ver  = "3.0.1"
cclog("uber.ver : ".. uber.ver)
local CURRENT_MODULE_NAME = ...
uber.PACKAGE_NAME = string.sub(CURRENT_MODULE_NAME, 1, -6)
local p = uber.PACKAGE_NAME
local config = 
{
	deprecated = false,	-- 支持过时模块 (默认关闭)
	opengl  = true,		-- Opengl模块
	network = true,		-- 网络模块
	display = true,		-- 图像加强模块
	audio = true,		-- 声音模块
	dbc = true,			-- dbc数据模块
	int = true,			-- 国际化模块
	iap = true,			-- 内付费模块
}
require(p..".helper.extern")
if frameworkConfig ~= nil then
	uber.config = clone(frameworkConfig)
	config = uber.config
end

-- 必然支持的模块
import(".helper.shortcuts")
import(".cc.Cocos2d")
import(".ccui.init")
import(".ccs.StudioConstants")
import(".opengl.OpenglConstants")

if config.deprecated then
	import(".deprecated.DeprecatedEnum")
	import(".deprecated.DeprecatedOpenglEnum")
	import(".deprecated.DeprecatedClass")
	import(".deprecated.Deprecated")

end

if config.network then
	import(".network.network")
end

if config.opengl then
	import(".opengl.Opengl")
	import(".opengl.DrawPrimitives")
end

if config.display then
	import(".display.display")
	import(".ccs.armatureEx")
end

if config.audio then
	import(".audio.AudioEngine")
end

if config.int then
	import(".helper.International")
end

if config.dbc then
	import(".helper.bytebuffer")
	uber.dbc = import(".dbc.DBCStores") -- 直接使用dbc很容易和自定义的local变量搞混,所以使用一个2级命名空间
end

if config.iap then
	cclog("uber's iap module coming soon..")
end

uber.TimingBegin = function()
	uber.beginTime = getMSTime()
end
uber.TimingEnd = function(output)
	uber.endTime = getMSTime()
	cclog(output..uber.endTime-uber.beginTime)
end