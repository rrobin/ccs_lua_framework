local SceneEditorUI = class("SceneEditorUI", function() return cc.Scene:create() end)
SceneEditorUI.__index = SceneEditorUI

require("ui.command.addTreeItem")
require("SceneEditor.command.DeleteLayer")
require("SceneEditor.command.DeleteScene")
require("SceneEditor.command.NewLayer")
require("SceneEditor.command.NewScene")
require("SceneEditor.command.RenameScene")
require("SceneEditor.command.modifyObject")
local BrtFilterUI = import(".BrtFilterUI")
local HueFilterUI = import(".HueFilterUI")

function SceneEditorUI:ctor()
	local layer = ccui.loadLayer("SceneEditor.ExportJson")
	self:addChild(layer)
	self._layer = layer
	local newSceneBtn = layer:getChild("NewSceneBtn")
	newSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.newScene)})

	local openSceneBtn = layer:getChild("OpenSceneBtn")
	openSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.loadScene)})

	local saveSceneBtn = layer:getChild("SaveSceneBtn")
	saveSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.saveScene)})

	local delSceneBtn = layer:getChild("DelSceneBtn")
	delSceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.delScene)})

	local newLayerBtn = layer:getChild("NewLayerBtn")
	newLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.addLayer)})

	local delLayerBtn = layer:getChild("DelLayerBtn")
	delLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.removeLayer)})

	local tileLayerBtn = layer:getChild("TileBtn")
	tileLayerBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.tileLayer)})

	local undoBtn = layer:getChild("UndoBtn")
	undoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.undo)})

	local redoBtn = layer:getChild("RedoBtn")
	redoBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.redo)})

	local addObjBtn = layer:getChild("AddObjBtn")
	addObjBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.addObject)})

	local delObjBtn = layer:getChild("DelObjBtn")
	delObjBtn:addTouchEvent({[ccui.TouchEventType.ended] = handler(self,self.removeObject)})

	local flierProPanel = self._layer:getChild("FlierProPanel")
	flierProPanel:setTouchEnabled(false)
	flierProPanel:setVisible(false)

	self._previewWindow = layer:getChild("preview_Win")
	self._designFactor = self._previewWindow:getSize().width/960
	self._center = cc.s2p(self._previewWindow:getSize())
	self._center.x = self._center.x/2
	self._center.y = self._center.y/2
	self:initObjectPanel()
    self:initLayerPanel()
	local treePanel = layer:getChild("TreePanel")
	self._tree = require("ui.TreeControl").new(treePanel:getSize(),"MainTree",handler(self,self.touchTree))
	local Layout = treePanel:getLayoutParameter()
	self._tree:setLayoutParameter(Layout)
	--self._tree:pos(treePanel:pos())
	layer:getChild("ScenePanel"):removeChild(treePanel)
	layer:getChild("ScenePanel"):addChild(self._tree)

	self._curScene = {data=0,ui=0,treeNode = 0}
	self._curGround = {data=0,ui=nil,treeNode = 0,name=""}
	self._curLayer = {data=0,ui=0,treeNode = 0}
	self._Grounds = {}
	self._layers = {}
	self._ui = {}
	self._object = nil
end

function SceneEditorUI:initLayerPanel()
	local function setText(widget,string)
          widget:setString(string)
	end
    local Rx = self._layer:getChild("RatioX")    -- 图层x速率
    Rx:addTextFieldEvent({
    	[ccui.TextFiledEventType.detach_with_ime] = 
    	    function(widget)
                local preXValue = self._curLayer.data._ratio.x  -- 先前zorder值
                local XValue = tonumber(widget:getString())

                local rwpanel = 
				{
					tips = "设置文本框",
					init = function()
						CC_SAFE_RETAIN(widget)
					end,
					redo = function()
					    if XValue ~= nil then
					    	self._curLayer.data._ratio.x = XValue
					    	setText(widget,string.format("%d",XValue))
					    end
					end,
					undo = function()
					    if preXValue ~= nil then
                            self._curLayer.data._ratio.x = preXValue
                            setText(widget,string.format("%d",preXValue))
                        end
					end,
					destory = function()
						CC_SAFE_RELEASE(widget)
					end,
				}
				local rwcmd = CustomCommand.new(rwpanel)   -- 重写面板数据
				Do(rwcmd)
    	    end
    })

    local Ry = self._layer:getChild("RatioY")    -- 图层y速率
    Ry:addTextFieldEvent({
    	[ccui.TextFiledEventType.detach_with_ime] = 
    	    function(widget)
                local preYValue = self._curLayer.data._ratio.y  -- 先前zorder值
                local YValue = tonumber(widget:getString())

                local rwpanel = 
				{
					tips = "设置文本框",
					init = function()
						CC_SAFE_RETAIN(widget)
					end,
					redo = function()
					    if YValue ~= nil then
					    	self._curLayer.data._ratio.y = YValue
					    	setText(widget,string.format("%d",YValue))
					    end
					end,
					undo = function()
					    if preYValue ~= nil then
                            self._curLayer.data._ratio.y = preYValue
                            setText(widget,string.format("%d",preYValue))
                        end
					end,
					destory = function()
						CC_SAFE_RELEASE(widget)
					end,
				}
				local rwcmd = CustomCommand.new(rwpanel)   -- 重写面板数据
				Do(rwcmd)
    	    end
    })

	local LayerZorder = self._layer:getChild("LayerZorder") -- 图层层次
    LayerZorder:addTextFieldEvent({
    	[ccui.TextFiledEventType.detach_with_ime] = 
    	    function(widget)
                local prezoValue = self._curLayer.data._zOrder  -- 先前zorder值
                local zoValue = tonumber(widget:getString())
                cclog("aa")
                if self._curLayer.ui == nil then
                    cclog("----------- ui 为空 initLayerPanel ------------")
                end
                local reordercmd = cc.reorderCommand.new(self._curLayer.ui,zoValue) --重新排列层
                --local reorderdatacmd = command.modifyObject.new()  --重新刷新层数据
                -- local cmd2 = command.modifyObject.new(self._object.data,6,z)

                local rwpanel = 
				{
					tips = "设置文本框",
					init = function()
						CC_SAFE_RETAIN(widget)
					end,
					redo = function()
					    if zoValue ~= nil then
					    	cclog("--------layerpanel zorder ----------")
					    	self._curLayer.data._zOrder = zoValue
					    	setText(widget,string.format("%d",zoValue))
					    end
					end,
					undo = function()
					    if prezoValue ~= nil then
					    	cclog("-------layerpanel prezorder -------")
                            self._curLayer.data._zOrder = prezoValue
                            setText(widget,string.format("%d",prezoValue))
                        end
					end,
					destory = function()
						CC_SAFE_RELEASE(widget)
					end,
				}
				local rwcmd = CustomCommand.new(rwpanel)   -- 重写面板数据
				Do(reordercmd,rwcmd)
			end
	})
	self:setupLayerPanel(nil)
end


function SceneEditorUI:setupLayerPanel(groundLayer)

	local panel = self._layer:getChild("LayerProPanel")

	if groundLayer == nil then
		panel:setTouchEnabled(false)
		panel:setVisible(false)
		return 
	else
		panel:setTouchEnabled(true)
		panel:setVisible(true)
	end
	local ratiox = self._layer:getChild("RatioX")
	ratiox:setString(groundLayer._ratio.x)
	local ratioy = self._layer:getChild("RatioY")
	ratioy:setText(string.format("%d",groundLayer._ratio.y))
	local layerZorder = self._layer:getChild("LayerZorder")
	layerZorder:setText(string.format("%d",groundLayer._zOrder))

end



function SceneEditorUI:initObjectPanel()
	--local filename = layer:getChild("ObjFile_Label")
	local Pos_x = self._layer:getChild("Pos_x")
	local function setText(widget,string)
		widget:setString(string)
	end
	Pos_x:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local pos = self._object:pos()
			pos.x = tonumber(widget:getString())
			local cmd1 = cc.MoveCommand.new(self._object,cc.p(pos.x*self._designFactor,pos.y))
			local cmd2 = command.modifyObject.new(self._object.data,1,pos)
			local org = self._object.data.Pos.x
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(widget)
				end,
				redo = function()
					setText(widget,string.format("%d",pos.x))
				end,
				undo = function()
					setText(widget,string.format("%d",org))
				end,
				destory = function()
					CC_SAFE_RELEASE(widget)
				end,
			}
			local cmd3 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3)
		end})
	--Pos_x:setText("")
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local pos = self._object:pos()
			pos.y = tonumber(widget:getString())
			local cmd1 = cc.MoveCommand.new(self._object,cc.p(pos.x,pos.y*self._designFactor))
			local cmd2 = command.modifyObject.new(self._object.data,1,pos)
			local org = self._object.data.Pos.y
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(widget)
				end,
				redo = function()
					setText(widget,string.format("%d",pos.y))
				end,
				undo = function()
					setText(widget,string.format("%d",org))
				end,
				destory = function()
					CC_SAFE_RELEASE(widget)
				end,
			}
			local cmd3 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3)
		end})
	--Pos_y:setText("")
	local Scale_x = self._layer:getChild("Scale_X")
	Scale_x:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local scale = cc.p(0,0)
			scale.x = tonumber(widget:getString())
			scale.y = self._object:getScaleY()
			local cmd1 = cc.ScaleCommand.new(self._object,scale.x*self._designFactor,scale.y)
			scale.y = scale.y/self._designFactor
			local cmd2 = command.modifyObject.new(self._object.data,2,scale)
			local org = self._object.data.Scale.x
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(widget)
				end,
				redo = function()
					setText(widget,string.format("%f",scale.x))
				end,
				undo = function()
					setText(widget,string.format("%f",org))
				end,
				destory = function()
					CC_SAFE_RELEASE(widget)
				end,
			}
			local cmd3 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3)
		end})
	--Scale_x:setText("")
	local Scale_y = self._layer:getChild("Scale_Y")
	Scale_y:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local scale = cc.p(0,0)
			scale.y = tonumber(widget:getString())
			scale.x = self._object:getScaleX()
			local cmd1 = cc.ScaleCommand.new(self._object,scale.x,scale.y*self._designFactor)
			scale.x = scale.x/self._designFactor
			local cmd2 = command.modifyObject.new(self._object.data,2,scale)
			local org = self._object.data.Scale.y
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(widget)
				end,
				redo = function()
					setText(widget,string.format("%f",scale.y))
				end,
				undo = function()
					setText(widget,string.format("%f",org))
				end,
				destory = function()
					CC_SAFE_RELEASE(widget)
				end,
			}
			local cmd3 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3)
		end})
	--Scale_y:setText("")
	local Rotate = self._layer:getChild("Rotate")
	Rotate:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local rotate = tonumber(widget:getString())
			local cmd1 = cc.RotateCommand.new(self._object,rotate)
			local cmd2 = command.modifyObject.new(self._object.data,3,rotate)
			local orotate = self._object:getRotation()
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(widget)
				end,
				redo = function()
					setText(widget,string.format("%d",rotate))
				end,
				undo = function()
					setText(widget,string.format("%d",orotate))
				end,
				destory = function()
					CC_SAFE_RELEASE(widget)
				end,
			}
			local cmd3 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3)
		end})
	--Rotate:setText("")
	local H_FlipBtn = self._layer:getChild("H_FlipBtn")
	H_FlipBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(button)
			local b = self._object:isFlippedX() == false
			local flip = cc.p(b,self._object:isFlippedY())
			local cmd1 = cc.FlipCommand.new(self._object,cc.axis_x)
			local cmd2 = command.modifyObject.new(self._object.data,5,flip)
			Do(cmd1,cmd2)
		end})
	local V_FlipBtn = self._layer:getChild("V_FlipBtn")
	V_FlipBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(button)
			local b = self._object:isFlippedY() == false
			local flip = cc.p(self._object:isFlippedX(),b)
			local cmd1 = cc.FlipCommand.new(self._object,cc.axis_y)
			local cmd2 = command.modifyObject.new(self._object.data,5,flip)
			Do(cmd1,cmd2)
		end})
	local Slider_51 = self._layer:getChild("Slider_51")
	local OpacityLabel = self._layer:getChild("OpacityLabel")
	Slider_51:addSliderEvent(function(slider)
			local percent = slider:getPercent()
			local opacity = math.floor(255*percent/100)
			self._object:setOpacity(opacity)
			OpacityLabel:setString(tostring(opacity))
		end)
	local orgOpacity = 255
	Slider_51:addTouchEvent({[ccui.TouchEventType.began]=
		function()
			orgOpacity = self._object:getOpacity()
		end,
		[ccui.TouchEventType.ended] =
		function(slider)
			local percent = slider:getPercent()
			local opacity = math.floor(255*percent/100)
			self._object:setOpacity(orgOpacity)
			local cmd1 = cc.OpacityCommand.new(self._object,opacity)
			local cmd2 = command.modifyObject.new(self._object.data,4,opacity)
			local m =
			{
				tips = "改变透明度",
				init = function()
					CC_SAFE_RETAIN(OpacityLabel)
					CC_SAFE_RETAIN(slider)
				end,
			 	redo = function()
			 		OpacityLabel:setString(tostring(opacity))
			 		slider:setPercent(percent)
			 	end,
			 	undo = function()
			 		OpacityLabel:setString(tostring(orgOpacity))
			 		slider:setPercent(math.floor(orgOpacity/255*100))
			 	end,
			 	destory = function()
			 		CC_SAFE_RELEASE(OpacityLabel)
			 		CC_SAFE_RELEASE(slider)
			 	end,
			}
			local cmd3 = CustomCommand.new(m)
			Do(cmd1,cmd2,cmd3)
		end})
	local zOrder = self._layer:getChild("zOrder")
	zOrder:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local z = tonumber(widget:getString())
			local cmd1 = cc.reorderCommand.new(self._object,z)
			local cmd2 = command.modifyObject.new(self._object.data,6,z)
			local oz = self._object:getLocalZOrder()
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(widget)
				end,
				redo = function()
					setText(widget,string.format("%d",z))
				end,
				undo = function()
					setText(widget,string.format("%d",oz))
				end,
				destory = function()
					CC_SAFE_RELEASE(widget)
				end,
			}
			local cmd3 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3)
		end})

	local ApplyBtn = self._layer:getChild("ApplyBtn")
	ApplyBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function()
			local pos = cc.p(0,0)
			pos.x = tonumber(Pos_x:getString())
			pos.y = tonumber(Pos_y:getString())
			local cmd1 = cc.MoveCommand.new(self._object,cc.pMul(pos,self._designFactor))
			local cmd2 = command.modifyObject.new(self._object.data,1,pos)
			local scale = {x=1,y=1}
			scale.x = tonumber(Scale_x:getString())
			scale.y = tonumber(Scale_y:getString())
			local cmd3 = cc.ScaleCommand.new(self._object,scale.x*self._designFactor,scale.y*self._designFactor)
			local cmd4 = command.modifyObject.new(self._object.data,2,scale)
			local rotate = tonumber(Rotate:getString())
			local cmd5 = cc.RotateCommand.new(self._object,rotate)
			local cmd6 = command.modifyObject.new(self._object.data,3,rotate)
			local z = tonumber(zOrder:getString())
			local cmd7 = cc.reorderCommand.new(self._object,z)
			local cmd8 = command.modifyObject.new(self._object.data,6,z)

			local oPos = self._object.data.Pos
			local oScale = self._object.data.Scale
			local oRotate= self._object:getRotation()
			local oZ = self._object:getLocalZOrder()
			local t = 
			{
				tips = "设置文本框",
				init = function()
					CC_SAFE_RETAIN(Pos_x)
					CC_SAFE_RETAIN(Pos_y)
					CC_SAFE_RETAIN(Rotate)
					CC_SAFE_RETAIN(Scale_x)
					CC_SAFE_RETAIN(Scale_y)
					CC_SAFE_RETAIN(zOrder)
				end,
				redo = function()
					setText(Pos_x,string.format("%d",pos.x))
					setText(Pos_y,string.format("%d",pos.y))
					setText(Rotate,string.format("%d",rotate))
					setText(Scale_x,string.format("%.2f",scale.x))
					setText(Scale_y,string.format("%.2f",scale.y))
					setText(zOrder,string.format("%d",z))
				end,
				undo = function()
					setText(Pos_x,string.format("%d",oPos.x))
					setText(Pos_y,string.format("%d",oPos.y))
					setText(Rotate,string.format("%d",oRotate))
					setText(Scale_x,string.format("%.2f",oScale.x))
					setText(Scale_y,string.format("%.2f",oScale.y))
					setText(zOrder,string.format("%d",oZ))
				end,
				destory = function()
					CC_SAFE_RELEASE(Pos_x)
					CC_SAFE_RELEASE(Pos_y)
					CC_SAFE_RELEASE(Rotate)
					CC_SAFE_RELEASE(Scale_x)
					CC_SAFE_RELEASE(Scale_y)
					CC_SAFE_RELEASE(zOrder)
				end,
			}
			local cmd9 = CustomCommand.new(t)
			Do(cmd1,cmd2,cmd3,cmd4,cmd5,cmd6,cmd7,cmd8,cmd9)
		end})

	local function createFilterWindow(filter,object,data)
		if not filter or not filter.class then return end
		local flierProPanel = self._layer:getChild("FlierProPanel")
		flierProPanel:setTouchEnabled(true)
		flierProPanel:setVisible(true)
		local shaderPanel = filter.ui
		if not shaderPanel then
			cclog("new filter UI :"..filter.text)
			local filterClass = filter.class
			local Layout = flierProPanel:getLayoutParameter()
			shaderPanel = filterClass.new()
			CC_SAFE_RETAIN(shaderPanel)
			shaderPanel:setName("FlierProPanel")
			shaderPanel:setLayoutParameter(Layout)
			filter.ui = shaderPanel
		end
		if flierProPanel ~= shaderPanel then
			self._layer:getChild("ScenePanel"):removeChild(flierProPanel)
			self._layer:getChild("ScenePanel"):addChild(shaderPanel)
		end
		shaderPanel:setProperty(object,data)
	end

	self._FilterTable = 
	{
		["Null"] = { text = "无", func = function(_,object,data)
			if data then
				local flierProPanel = self._layer:getChild("FlierProPanel")
				flierProPanel:setTouchEnabled(false)
				flierProPanel:setVisible(false)
				if data.Filter then
					object:setShader(cc.SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP)
					data.Filter = nil
				end
			end
		end, class = nil},
		["brightShader"] = { text = "明度", func = createFilterWindow, class = BrtFilterUI},
		["hueShader"] = { text = "色调", func = createFilterWindow, class = HueFilterUI},
	}
	local FilterList = self._layer:getChild("FilterListView")
	local FilterBtn = self._layer:getChild("FilterButton")
	FilterList:setItemModel(FilterBtn)
	local i = 1
	for k,v in pairs(self._FilterTable) do
		FilterList:pushBackDefaultItem()
		local item = FilterList:getItem(i-1)
		item:setTag(i)
		item:addTouchEvent({[ccui.TouchEventType.ended] = function(button)
			FilterBtn:setTouchEnabled(true)
			FilterBtn:setVisible(true)
			FilterList:setTouchEnabled(false)
			FilterList:setVisible(false)
			local text = FilterBtn:getTitleText()
			local prevName = "Null"
			local filter = self._object.data.Filter
			if filter then
				prevName = filter.name
			end
			local m = 
			{
				tips = "设置滤镜"
			}
			m.filter = clone(filter)
			m.init = function()
					CC_SAFE_RETAIN(FilterBtn)
				end
			m.redo = function()
					if not self._object.data.Filter then
						self._object.data.Filter = {}
					end
					self._object.data.Filter.name = k
					self:setupFilter(self._object,self._object.data)
				end
			m.undo = function()
					self._object.data.Filter = clone(m.filter)
					self:setupFilter(self._object,self._object.data)
				end
			m.destory = function()
					CC_SAFE_RELEASE(FilterBtn)
				end
			local cmd = CustomCommand.new(m)
			Do(cmd)
		end,})
		item:setName("FilterItem"..i)
		item:setTitleText(v.text)
		i = i+1
	end
	FilterBtn:addTouchEvent({[ccui.TouchEventType.ended] =
		function(button)
			button:setTouchEnabled(false)
			button:setVisible(false)
			FilterList:setTouchEnabled(true)
			FilterList:setVisible(true)
		end
		})

	self:setupObjectPanel(nil)
	self:setupFilter(nil,nil)
end

function SceneEditorUI:setupObjectPanel(SceneObject)
	local panel = self._layer:getChild("ObjProPanel")

	if SceneObject == nil then
		panel:setTouchEnabled(false)
		panel:setVisible(false)
		return 
	else
		panel:setTouchEnabled(true)
		panel:setVisible(true)
	end

	local filename = self._layer:getChild("ObjFile_Label")
	filename:setString(SceneObject.Filename)
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:setText(string.format("%d",SceneObject.Pos.x))
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:setText(string.format("%d",SceneObject.Pos.y))
	local Scale_x = self._layer:getChild("Scale_X")
	Scale_x:setText(SceneObject.Scale.x)
	local Scale_y = self._layer:getChild("Scale_Y")
	Scale_y:setText(SceneObject.Scale.y)
	local Rotate = self._layer:getChild("Rotate")
	Rotate:setText(SceneObject.Rotate)
	--[[
	local H_FlipBtn = self._layer:getChild("H_FlipBtn")
	H_FlipBtn:setBright(SceneObject.FlipX==false)
	local V_FlipBtn = self._layer:getChild("V_FlipBtn")
	V_FlipBtn:setBright(SceneObject.FlipX==false)
	]]
	local Slider_51 = self._layer:getChild("Slider_51")
	Slider_51:setPercent(math.floor(SceneObject.Opacity/255*100))
	local OpacityLabel = self._layer:getChild("OpacityLabel")
	OpacityLabel:setString(tostring(SceneObject.Opacity))
	local zOder = self._layer:getChild("zOrder")
	zOder:setString(string.format("%d",SceneObject.zOrder))
end

function SceneEditorUI:setupFilter(object,data)
	local flierProPanel = self._layer:getChild("FlierProPanel")
	flierProPanel:setTouchEnabled(false)
	flierProPanel:setVisible(false)

	if object == nil then 	
		return 
	end

	local name = "Null"
	if data and data.Filter then
		name =  data.Filter.name
	end
	if data then
		cclog(data.Filename.." set filter : "..name)
	end
	local v = self._FilterTable[name]
	local FilterBtn = self._layer:getChild("FilterButton")
	cclog("text : "..v.text)
	FilterBtn:setTitleText(v.text)
	v.func(v,object,data)
end

-- SceneOp
function SceneEditorUI:saveScene()
	-- body
	SceneManager:Save(self._curScene.data._name,"e:\\output")
end

function SceneEditorUI:loadScene()
	local scene = SceneManager:Load("")
	if not scene then return end 
	local parent = self._tree:addItem("新场景")
	self._Grounds[self._tree:addItem("背景",parent)] = scene._BackGround
	self._Grounds[self._tree:addItem("地板",parent)] = scene._Floor
	self._Grounds[self._tree:addItem("前景",parent)] = scene._FrontGround
	self._tree:extend(parent)
	self:addSceneUI(960*2)
end

function SceneEditorUI:newScene()
	local scene = SceneManager:findScene("新场景")
	if scene then return end 
	scene = SceneManager:addScene("新场景",960*2)
	local parent = self._tree:addItem("新场景")
	self._Grounds[self._tree:addItem("背景",parent)] = scene._BackGround
	self._Grounds[self._tree:addItem("地板",parent)] = scene._Floor
	self._Grounds[self._tree:addItem("前景",parent)] = scene._FrontGround
	self._tree:extend(parent)
	self:addSceneUI(960*2)
	--[[
	local cmd1 = command.NewScene.new("新场景",960*2)
	local cmd2 = command.addTreeItem.new(self._tree,"新场景")
	local cmd3 = command.addTreeItem.new(self._tree,"背景","Root1")
	local cmd4 = command.addTreeItem.new(self._tree,"地板","Root1")
	local cmd5 = command.addTreeItem.new(self._tree,"前景","Root1")
	Do(cmd1,cmd2,cmd3,cmd4,cmd5)
	]]
end

function SceneEditorUI:delScene()
	SceneManager:removeScene("新场景")
	self._tree:removeItem(self._curScene)
	self._curScene = {data=0,ui=0,treeNode = 0}
	self._curGround = {data=0,ui=0,treeNode = 0}
	--[[
	local cmd1 = command.DeleteScene.new("新场景")
	local cmd2 = command.removeTreeItem.new(self._tree,self._selected)
	Do(cmd1,cmd2)
	]]
end

function SceneEditorUI:renameScene()
end

-- GroundLayerOp
function SceneEditorUI:addLayer()

	local layInfo = clone(LPData)

	if self._curGround.name == "背景" then
		local name = "层"..self._curGround.data:LayerCount()+1
        
		local node = nil
		local s = self:getSize()
		s.width = self._curScene.data._width/960*s.width
		local panel = ccui.panel({size = s})
		local index = 0 
		local cmdt = 
		{
			tips = "新建层",
			init = function()
			CC_SAFE_RETAIN(self._tree)
			CC_SAFE_RETAIN(panel)
		end,
			undo = function()
			self._curGround.data:removeLayer(index)
			self._layers[self._curGround.name..name] = nil
			self._curGround.ui:removeChild(panel)
			self._tree:removeItem(node)
			self._tree:Layout()
			self._tree:print()
		end,            
			redo = function()
			local l = GroundLayer.new(self._curGround.data,name)
			index = self._curGround.data:addLayer(l)

			self._layers[self._curGround.name..name] = panel
			self._curGround.ui:addChild(panel)
			node = self._tree:addItem(name,self._curGround.treeNode)
			self._tree:Layout()
			self._tree:print()
		end,
			destory = function()
			CC_SAFE_RELEASE(self._tree)
			CC_SAFE_RELEASE(panel)
		end
		}
		local cmd = CustomCommand.new(cmdt)
		Do(cmd)
	end
end

function SceneEditorUI:removeLayer()
    
end

function SceneEditorUI:renameLayer()
end

function SceneEditorUI:tileLayer()
end

-- SceneObjectOp
function SceneEditorUI:addObject()
	if self._curLayer.data == 0 then
		return 
	end
	local filename = PlatformUtility:OpenFile("E:\\","Png;Jpg(*.png,*.Jpg)\0*.png;*.jpg\0")
	local name = self._curLayer.data._name
	cclog("cur layer name:"..name)
	if filename == "" then return end
	self:addImage(filename,name)
end

function SceneEditorUI:addImage(filename,layername)
	local sprite = ccui.image({image=filename})
	local objInfo = clone(SceneObject)
	local pos = nil
	local prevObject = self._object
	local cmdt = 
	{
		tips = "添加场景物体",
		init = function()
			sprite:setScale(self._designFactor)
			sprite:pos(self._center)
			
			sprite:addTouchEvent({[ccui.TouchEventType.began] = handler(self,self.touchSprite),
									[ccui.TouchEventType.moved] = handler(self,self.moveSprite),
									[ccui.TouchEventType.ended] = handler(self,self.stopSprite),
									[ccui.TouchEventType.canceled] = handler(self,self.stopSprite),
									})
			CC_SAFE_RETAIN(sprite)
			CC_SAFE_RETAIN(prevObject)
			objInfo.Filename = filename
			objInfo.zOrder = sprite:getLocalZOrder()
			objInfo.Pos = cc.p(self._center.x/self._designFactor,self._center.y/self._designFactor)
		end,
		undo = function()
			self._curLayer.data:removeObject(pos)
			cclog("remove data pos : ".. pos)
			if self._object then
				self._object:getVirtualRenderer():setDrawBound(false)
			end
			self._object = prevObject
			local data = nil
			if prevObject then
				data = prevObject.data
				prevObject:getVirtualRenderer():setDrawBound(true)
				self._object.index = nil  
			end
			self._layers[self._curGround.name..layername]:removeChild(sprite)
			self:setupObjectPanel(data)
			self:setupFilter(self._object,data)
		end,
		redo = function()
			if prevObject then
				prevObject:getVirtualRenderer():setDrawBound(false)
			end
			self._object = sprite
			sprite:getVirtualRenderer():setDrawBound(true)
			self._layers[self._curGround.name..layername]:addChild(sprite)
			self:setupObjectPanel(objInfo)
			self:setupFilter(self._object,objInfo)
			pos = self._curLayer.data:addObject(objInfo)
			cclog("add data pos : ".. pos)
			self._object.data = objInfo
			self._object.index = pos
		end,
		destory = function()
			CC_SAFE_RELEASE(sprite)
			CC_SAFE_RELEASE(prevObject)
		end,
	}
	local cmd = CustomCommand.new(cmdt)
	Do(cmd)
end

function SceneEditorUI:touchSprite(image)
	local prevObject = self._object
	if prevObject ~= image then -- 重复点击就不记录了
		local m = 
		{
			tips = "选择物件",
			init = function()
				CC_SAFE_RETAIN(prevObject)
				CC_SAFE_RETAIN(image)
			end,
			redo = function()
				if prevObject then
					prevObject:getVirtualRenderer():setDrawBound(false)
				end
				image:getVirtualRenderer():setDrawBound(true)
				self._object = image
				self:setupObjectPanel(self._object.data)
				self:setupFilter(self._object,self._object.data)
			end,
			undo = function()
				image:getVirtualRenderer():setDrawBound(false)
				if prevObject then
					prevObject:getVirtualRenderer():setDrawBound(true)
				end
				self._object = prevObject
				local data = nil
				if self._object then
					data = self._object.data
				end
				self:setupObjectPanel(data)
				self:setupFilter(self._object,data)
			end,
			destory = function()
				CC_SAFE_RELEASE(prevObject)
				CC_SAFE_RELEASE(image)
			end,
		}
		local cmd = CustomCommand.new(m)
		Do(cmd)
	end
	self._spos = image:getTouchBeganPosition()
	if self._object then
		self._object.spos = self._object:pos()
	end
	local scrollview = self._layer:getChild("preview_Scroll")
	local inner_pos = scrollview:getInnerContainer():pos()
	self._offset = {x=100,y=100}
	local delta = scrollview:getInnerContainer():getSize().width - scrollview:getSize().width
	if delta > 0 then
		self._offset.x = -inner_pos.x/delta*100
	end
	delta = scrollview:getInnerContainer():getSize().height - scrollview:getSize().height
	if delta > 0 then
		self._offset.y = inner_pos.y/delta*100
	end
end

function SceneEditorUI:moveSprite(image)
	local mpos =image:getTouchMovePosition()
	local offset = cc.pSub(mpos,self._spos)
	local pos = cc.pAdd(self._object.spos,offset)
	self._object:pos(pos)
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:setText(string.format("%d",math.floor(pos.x/self._designFactor)))
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:setText(string.format("%d",math.floor(pos.y/self._designFactor)))
	self._layer:getChild("preview_Scroll"):jumpToPercentHorizontal(self._offset.x)
end

function SceneEditorUI:stopSprite(image)
	local epos = image:getTouchEndPosition()
	local Pos_x = self._layer:getChild("Pos_x")
	local Pos_y = self._layer:getChild("Pos_y")
	local object = self._object
	local delay = cc.pSub(epos,self._spos)
	--cclog("delay x:"..delay.x.." y:"..delay.y)
	if math.abs(delay.x) > 1 or math.abs(delay.y) > 1 then -- 精度到1像素
		local spos = self._object.spos
		local cmdtable = 
		{
			tips = "移动物件",
			init = function()
				CC_SAFE_RETAIN(object)
				CC_SAFE_RETAIN(Pos_x)
				CC_SAFE_RETAIN(Pos_y)
			end,
			undo = function()
				local pos = object:pos(spos)
				pos.x = math.floor(pos.x/self._designFactor)
				pos.y = math.floor(pos.y/self._designFactor)
				Pos_x:setText(string.format("%d",pos.x))
				Pos_y:setText(string.format("%d",pos.y))
				object.data.Pos = pos
			end,
			redo = function()
				local pos = object:pos(cc.pAdd(spos,delay))
				pos.x = math.floor(pos.x/self._designFactor)
				pos.y = math.floor(pos.y/self._designFactor)
				Pos_x:setText(string.format("%d",pos.x))
				Pos_y:setText(string.format("%d",pos.y))
				object.data.Pos = pos
			end,
			destory = function()
				CC_SAFE_RELEASE(object)
				CC_SAFE_RELEASE(Pos_x)
				CC_SAFE_RELEASE(Pos_y)
			end,
		}
		local cmd = CustomCommand.new(cmdtable)
		Do(cmd)
	end
	self._layer:getChild("preview_Scroll"):scrollToPercentHorizontal(self._offset.x,0.01,false)
	--cclog("stop sprite")
end

function SceneEditorUI:removeObject()
    local prevObject = self._object
    --local objInfot = clone(SceneObject)

    if self._curLayer.data == 0 or prevObject == nil then
   		return 
  	end
  	local fn = self._curLayer.data._name
    local cmdt = 
    {
          tips = "删除物体",
          init = function()
	          --CC_SAFE_RETAIN(sprite)
			  CC_SAFE_RETAIN(prevObject)
          end,

          undo = function()
          	self._object = prevObject
          	if prevObject then 
				local objInfotemp = prevObject.data
				self._layers[self._curGround.name..fn]:addChild(prevObject)
				self:setupObjectPanel(objInfotemp)
				self:setupFilter(self._object,objInfotemp)
                local indextemp = nil
				indextemp = self._curLayer.data:addObject(objInfotemp,self._object.index)
			    cclog("add data index : ".. self._object.index)
          	end
          end,
          redo = function()
	        self._curLayer.data:removeObject(self._object.index)
          	self._layers[self._curGround.name..fn]:removeChild(self._object)
          	self:setupObjectPanel(nil)
          	self:setupFilter(nil,nil)
          	self._object = nil
          end,
          destory = function()
                --CC_SAFE_RELEASE(sprite)
			    CC_SAFE_RELEASE(prevObject)
          end,
    }
	local cmd = CustomCommand.new(cmdt)
	Do(cmd)
end

--CommondOp
function SceneEditorUI:undo()
	Undo()
end

function SceneEditorUI:redo()
	Redo()
end

function SceneEditorUI:touchTree(tree_name)
	cclog("tree_name:"..tree_name)
	self._selected = self._tree:getSelectedItem()
	self._selectedType = -1
	local node = self._selected
	while node ~= nil
		do
		 if node.P == nil then
		 	self._curScene.data = SceneManager:findScene(node.value)
		 	self._curScene.treeNode = node.name
		 	cclog("curScene:"..node.value)
		 end
		 if self._Grounds[node.name] then
		 	if self._curGround.ui ~= nil then
		 		self._curGround.ui:setVisible(false)
		 	end
		 	self._curGround.data = self._Grounds[node.name]
		 	self._curGround.treeNode = node.name
		 	self._curGround.ui = self._ui[node.value]
		 	self._curGround.name = node.value
		 	self._curGround.ui:setVisible(true)
		 	cclog("curGround:"..node.value)
		 end
		 node = node.P
		 self._selectedType = self._selectedType + 1
	end

	if self._selectedType == 2 then
		local prevSelected = self._curlayer
		local cmdt = 
		{
			tips = "选择层:"..self._selected.value,
			redo = function()
				self._curLayer.data = self._curGround.data:getLayer(self._selected.value)
				self._curLayer.treeNode = self._selected.name
				self._curLayer.ui = self._layers[self._curGround.name..self._selected.value]
				self:setupLayerPanel(self._curLayer.data)
			end,
			undo = function()
				self._curlayer = prevSelected
				self:setupLayerPanel(self._curLayer.data)
			end,
		}

		local cmd = CustomCommand.new(cmdt)
		Do(cmd)
		
	elseif self._selectedType > 2 then

	end

	cclog("selectedType:"..self._selectedType)
end

-- for preview
function SceneEditorUI:addSceneUI(width)
	self._previewWindow:removeAllChildren()
	local winSize = self._previewWindow:getSize()
	local inner = self._previewWindow:getSize()
	inner.width = width * self._designFactor
	local scrollview = ccui.scrollView({size = winSize,innerSize = inner,
										direction = ccui.ScrollViewDir.horizontal,name = "preview_Scroll",})
	--image:pos(cc.s2p(image:getSize()))
	self._previewWindow:addChild(scrollview,1,0)
	local panel = ccui.panel({size=inner}) --,colorType = ccui.LayoutBackGroundColorType.gradient,color = cc.c3b(255,0,0),endColor = cc.c3b(125,0,0)
	self._ui["背景"] = panel
	panel:setVisible(false)
	scrollview:addChild(panel,1,1)
	panel = ccui.panel({size=inner})--,colorType = ccui.LayoutBackGroundColorType.gradient,color = cc.c3b(0,255,0),endColor = cc.c3b(0,125,0)
	self._ui["地板"] = panel
	panel:setVisible(false)
	scrollview:addChild(panel,2,2)
	panel = ccui.panel({size=inner}) --,colorType = ccui.LayoutBackGroundColorType.gradient,color = cc.c3b(0,0,255),endColor = cc.c3b(0,0,125)
	self._ui["前景"] = panel
	panel:setVisible(false)
	scrollview:addChild(panel,3,3)
end  

function SceneEditorUI:addLayerUI()
end

return SceneEditorUI