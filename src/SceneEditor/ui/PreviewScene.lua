local PreviewScene = class("PreveiwScene", function()
	return cc.Scene:create()
end)
PreviewScene.__index = PreviewScene

function PreviewScene:ctor()
	self.psize = {width=0,height=0}   --记录场景宽高
	local keyshortcut = KeyBoardManager:getShortcuts("PreviewScene")
	if not keyshortcut then
		keyshortcut = KeyShortcuts.new("PreviewScene")
		keyshortcut:add(single_type,"KEY_LEFT_ARROW",handler(self,self.onLeft),nil)
		keyshortcut:add(single_type,"KEY_RIGHT_ARROW",handler(self,self.onRight),nil)
		keyshortcut:add(single_type,"KEY_UP_ARROW",handler(self,self.onUp),nil)
		keyshortcut:add(single_type,"KEY_DOWN_ARROW",handler(self,self.onDown),nil)
		keyshortcut:add(single_type,"KEY_ESCAPE",handler(self,self.returnEditor),nil)
		KeyBoardManager:add(keyshortcut)
	end
	KeyBoardManager:apply("PreviewScene")
	--scheduleUpdateWithPriorityLua(onLefting,)
end

function PreviewScene:onLeft()
	cclog(" PreviewScene:onLeft:"..tostring(self))
	local pnode = self:getChildByTag(-555)
	local posx = pnode:getPositionX() - 1
	cclog("posx:"..posx)
	cclog("max value:"..-(tonumber(self.psize.width))/2)
	if posx <= -(tonumber(self.psize.width))/2 then posx = -(tonumber(self.psize.width))/2 end
	pnode:setPositionX(posx)
end

function PreviewScene:onRight()
	cclog(" PreviewScene:onRight:"..tostring(self))
	local pnode = self:getChildByTag(-555)
	local posx = pnode:getPositionX() + 1
	cclog("posx:"..posx)
	if posx >=0 then posx = 0 end
	--if posx 0 then posx 
	pnode:setPositionX(posx)
end

function PreviewScene:onUp()
	local pnode = self:getChildByTag(-555)
	local posy = pnode:getPositionY() + 1
	pnode:setPositionY(posy)
end

function PreviewScene:onDown()
	local pnode = self:getChildByTag(-555)
	local posy = pnode:getPositionY() - 1
	pnode:setPositionY(posy)
end

function PreviewScene:returnEditor()
	sharedDirector:getOpenGLView():setFrameSize(config.width,config.height)
	sharedDirector:getOpenGLView():setDesignResolutionSize(config.designWidth,config.designHeight,config.policy)
	--self:removeAllChildren()
	cc.popScene()
	--self:removeAllChildrenWithCleanup(true)
	SceneManager:removeScene("newScene_preview")
	KeyBoardManager:apply("SceneEditor")
end

function PreviewScene:loadSce(filename,prevsize) 
	cclog("-------加载sce文件--------")
	--ProjectManager:prevload(filename)
    cclog("prevsize width:"..prevsize.width.." height:"..prevsize.height)
    local scene = SceneManager:prevLoad(filename)
    if not scene then return end
    local widthtemp = tonumber(scene._width)
    --local heighttemp = widthtemp*2/3
    --local wh = {width = 1152,height = 768 }


    local scalerate = 0.5
    sharedDirector:getOpenGLView():setFrameSize(prevsize.width/2,prevsize.height/2)
	sharedDirector:getOpenGLView():setDesignResolutionSize(prevsize.width/2,prevsize.height/2,config.policy)

    local pnode = cc.ParallaxNode:create()
    local prevh = prevsize.height

    self.psize.width = widthtemp/2
    self.psize.height = prevh/2
    pnode:setContentSize(widthtemp/2,prevh/2)
	local function createChild(ground)
        for i=1,ground:LayerCount() do
        	--cclog(" ground layerCount:"..ground:LayerCount())
		    local l = ground:getLayer(i-1)
		    local ratio = l._ratio
		    local zOrder = l._zOrder
            --cclog("ratio x:"..ratio.x.."  y:"..ratio.y.." zorder:"..zOrder)
		    --cclog(" self:getSize width:"..self:getSize().width.." height:"..self:getSize().height)

		    local panel = ccui.panel({size = {width=widthtemp/2,height=prevh/2}})--cc.ParallaxNode:create()
		    panel:setTouchEnabled(true)
		    for j=1,l:getObjectCount() do
		    	--cclog(" l:getObjectCount:"..l:getObjectCount())
				local obj = l:getObject(j-1)
                local sprite = nil
                local objtype = -1
                --cclog(obj.Filename)
			    if string.find(obj.Filename,"%.plist") then 
			        sprite = ccui.particle(obj.Filename)
			        objtype = 2
			    elseif string.find(obj.Filename,"%.ExportJson") then
			    	sprite = ccui.animationNode(obj.Filename)
			    	objtype = 3
			    else
					sprite = ccui.image({image=obj.Filename,z=obj.zOrder})
					objtype = 0
				end
				--cclog("posx:"..obj.Pos.x.." y:"..obj.Pos.y)
				sprite:setScaleX(obj.Scale.x*scalerate)
				sprite:setScaleY(obj.Scale.y*scalerate)
				sprite:pos(obj.Pos.x*scalerate,obj.Pos.y*scalerate)
				sprite:setFlippedX(obj.Flip.x)
				sprite:setFlippedY(obj.Flip.y)
				sprite:setRotation(obj.Rotation)
				sprite:setOpacity(obj.Opacity)
				if obj.Filter then
					obj.Filter:ApplyTo(sprite)
				end
				panel:addChild(sprite)
			end
            local postemp = {x=0,y=0}
            pnode:addChild(panel,0,ratio,postemp)
		end
	end
    createChild(scene._BackGround)
    createChild(scene._Floor)
    createChild(scene._FrontGround)
    self:addChild(pnode,0,-555)
    --pnode:setTouchEnabled(true)
    cclog("end")
end


return PreviewScene