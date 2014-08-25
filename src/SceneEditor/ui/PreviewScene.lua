local PreviewScene = class("PreveiwScene", function()
	return cc.Scene:create()
end)

function PreviewScene:ctor()
	sharedDirector:getOpenGLView():setFrameSize(960,640)
	sharedDirector:getOpenGLView():setDesignResolutionSize(960,640,config.policy)
	local keyshortcut = KeyBoardManager:getShortcuts("PreviewScene")
	if not keyshortcut then
		keyshortcut = KeyShortcuts.new("PreviewScene")
		keyshortcut:add(single_type,"KEY_LEFT_ARROW",handler(self,self.onLeft),nil)
		keyshortcut:add(single_type,"KEY_RIGHT_ARROW",handler(self,self.onRight),nil)
		keyshortcut:add(single_type,"KEY_ESCAPE",handler(self,self.returnEditor),nil)
		KeyBoardManager:add(keyshortcut)
	end
	KeyBoardManager:apply("PreviewScene")
end

function PreviewScene:onLeft()
end

function PreviewScene:onRight()
end

function PreviewScene:returnEditor()
	sharedDirector:getOpenGLView():setFrameSize(config.width,config.height)
	sharedDirector:getOpenGLView():setDesignResolutionSize(config.designWidth,config.designHeight,config.policy)
	cc.popScene(self)
end

return PreviewScene