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

	local ObjList = layer:getChild("ListView_Obj")
	ObjList:setTouchEnabled(false)
	local ObjItem = ccui.loadWidget("ObjItem.ExportJson")
	local s = ObjItem:getSize()
	s.width = ObjList:getSize().width
	ObjItem:setSize(s)
	ObjList:setItemModel(ObjItem)
	self._ObjList = ObjList
	self._prevItem = nil
	ObjList:addListVeiwEvent({[ccui.ListViewEventType.onSelectedItem_end] = function(listView)
			local idx = listView:getCurSelectedIndex()
			local item = listView:getItem(idx)
			local sprite = self._objects[item:getChild("Label"):getString()]
			self:CMD_SelectSprite(sprite)
			self._prevItem = item
		end})

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

	local SceneBtn = layer:getChild("SceneBtn")
	local ObjBtn = layer:getChild("ObjBtn")
	SceneBtn:addTouchEvent({[ccui.TouchEventType.ended] = function()
			self._tree:setTouchEnabled(true)
			self._tree:setVisible(true)
			self._ObjList:setTouchEnabled(false)
			self._ObjList:setVisible(false)
		end})
	ObjBtn:addTouchEvent({[ccui.TouchEventType.ended] = function()
			self._tree:setTouchEnabled(false)
			self._tree:setVisible(false)
			self._ObjList:setTouchEnabled(true)
			self._ObjList:setVisible(true)
		end})
	

	self._curScene = {data=0,ui=0,treeNode = 0}
	self._curGround = {data=0,ui=nil,treeNode = 0,name=""}
	self._curLayer = {data=0,ui=0,treeNode = 0}
	self._Grounds = {}
	self._layers = {}
	self._objects = {}   -- 用来存储object对象列表
	self._ui = {}
	self.selectedType = -1 --´æ´¢½ÚµãÀàÐÍ
	self._object = nil
	self._ObjCount  = 0

	-- 设置快捷键
	local keyshortcut = KeyBoardManager:getShortcuts("SceneEditor")
	if not keyshortcut then
		keyshortcut = KeyShortcuts.new("SceneEditor")
		keyshortcut:add("KEY_Z",handler(self,self.undo),nil,ctrl_type)
		keyshortcut:add("KEY_Y",handler(self,self.redo),nil,ctrl_type)
		KeyBoardManager:add(keyshortcut)
	end
	KeyBoardManager:apply("SceneEditor")
end

---------------------------------------------------------

--- 			SceneEditor's command 				  ---

---------------------------------------------------------

function SceneEditorUI:CMD_SelectSprite(sprite)
	local prevObject = self._object

	if prevObject ~= sprite then -- 重复点击就不记录了
		local m = 
		{
			tips = "选择物件",
			init = function()
				CC_SAFE_RETAIN(prevObject)
				CC_SAFE_RETAIN(sprite)
			end,
			redo = function()
				if prevObject then
					prevObject:getVirtualRenderer():setDrawBound(false)
				end
				sprite:getVirtualRenderer():setDrawBound(true)
				self._object = sprite
				self:setupObjectPanel(self._object.data)
				self:setupFilter(self._object,self._object.data)
				self:updateObjList(self._object)

			end,
			undo = function()
				sprite:getVirtualRenderer():setDrawBound(false)
				local data = nil
				if prevObject then
					prevObject:getVirtualRenderer():setDrawBound(true)
					data = prevObject.data
				end
				self._object = prevObject
				self:setupObjectPanel(data)
				self:setupFilter(self._object,data)
				self:updateObjList(self._object)
			end,
			destory = function()
				CC_SAFE_RELEASE(prevObject)
				CC_SAFE_RELEASE(sprite)
			end,
		}
		local cmd = CustomCommand.new(m)
		Do(cmd)
	end
end

function SceneEditorUI:CMD_MoveObject(object,epos)
	local Pos_x = self._layer:getChild("Pos_x")
	local Pos_y = self._layer:getChild("Pos_y")
	local spos = object.data.Pos
	epos.x = math.floor(epos.x)
	epos.y = math.floor(epos.y)
	local delay = cc.pSub(epos,spos)
	if math.abs(delay.x) > 1 or math.abs(delay.y) > 1 then -- 精度到1像素
		local cmdtable = 
		{
			tips = "移动物件",
			init = function()
				CC_SAFE_RETAIN(object)
				CC_SAFE_RETAIN(Pos_x)
				CC_SAFE_RETAIN(Pos_y)
			end,
			undo = function()
				local pos = object:pos(cc.pMul(spos,self._designFactor))
				Pos_x:setText(string.format("%d",spos.x))
				Pos_y:setText(string.format("%d",spos.y))
				object.data.Pos = spos
			end,
			redo = function()
				object:pos(cc.pMul(cc.pAdd(spos,delay),self._designFactor))
				Pos_x:setText(string.format("%d",epos.x))
				Pos_y:setText(string.format("%d",epos.y))
				object.data.Pos = epos
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
end

function SceneEditorUI:CMD_ScaleObject(object,scale)
	local Scale_x = self._layer:getChild("Scale_X")
	local Scale_y = self._layer:getChild("Scale_Y")
	local oScale = object.data.Scale
	local cmdtable = 
	{
		tips = "缩放物件",
		init = function()
			CC_SAFE_RETAIN(object)
			CC_SAFE_RETAIN(Scale_x)
			CC_SAFE_RETAIN(Scale_y)
		end,
		undo = function()
			object:setScaleX(oScale.x*self._designFactor)
			object:setScaleY(oScale.y*self._designFactor)
			Scale_x:setText(string.format("%.2f",oScale.x))
			Scale_y:setText(string.format("%.2f",oScale.y))
			object.data.Scale = oScale
		end,
		redo = function()
			object:setScaleX(scale.x*self._designFactor)
			object:setScaleY(scale.y*self._designFactor)
			Scale_x:setText(string.format("%.2f",scale.x))
			Scale_y:setText(string.format("%.2f",scale.y))
			object.data.Scale = scale
		end,
		destory = function()
			CC_SAFE_RELEASE(object)
			CC_SAFE_RELEASE(Scale_x)
			CC_SAFE_RELEASE(Scale_y)
		end,
	}
	local cmd = CustomCommand.new(cmdtable)
	Do(cmd)
end

--------------------------------------------------------------------------
--------------------------------------------------------------------------
--------------------------------------------------------------------------

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
			local pos = self._object.data.Pos
			pos.x = tonumber(widget:getString())
			self:CMD_MoveObject(self._object,pos)
		end})

	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local pos = self._object.data.Pos
			pos.y = tonumber(widget:getString()) * self._designFactor
			self:CMD_MoveObject(self._object,pos)
		end})

	local Scale_x = self._layer:getChild("Scale_X")
	Scale_x:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local scale = cc.p(0,0)
			scale.x = tonumber(widget:getString())
			scale.y = self._object.data.Scale.y
			self:CMD_ScaleObject(self._object,scale)
		end})
	
	local Scale_y = self._layer:getChild("Scale_Y")
	Scale_y:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local scale = cc.p(0,0)
			scale.y = tonumber(widget:getString())
			scale.x = self._object.data.Scale.x
			self:CMD_ScaleObject(self._object,scale)
		end})

	local Rotate = self._layer:getChild("Rotate")
	Rotate:addTextFieldEvent({[ccui.TextFiledEventType.detach_with_ime] = 
		function(widget)
			local rotate = tonumber(widget:getString())
			cclog("旋转到"..rotate.."度")
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
		panel:setTouchEnabled(SceneObject.locked == false)
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
	Rotate:setText(SceneObject.Rotation)
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

function SceneEditorUI:updateObjList(object)
	local items = self._ObjList:getItems()
	for k,v in pairs(items) do
		v:getChild("Label"):getVirtualRenderer():setDrawBound(false)
		if object then
			cclog("24345768975432345679")
			if v:getChild("Label"):getString() == object.name then
				cclog("1231231224213")
				v:getChild("Label"):getVirtualRenderer():setDrawBound(true)
	            local lockBtn = v:getChild("LockBtn")    -- 锁定按钮
	            local visibleBtn = v:getChild("VisibleBtn")  -- 隐藏按钮
				if object.data.locked then
	            -- 更新按钮对象list锁定状态
	                lockBtn:loadTextureNormal("lock_16x16.png",ccui.TextureResType.plistType)
				else
	            	lockBtn:loadTextureNormal("unlock_16x16.png",ccui.TextureResType.plistType)
				end

				if object.data.visible then
		            -- 更新对象list隐藏状态
	                visibleBtn:loadTextureNormal("cd_16x16.png",ccui.TextureResType.plistType)
				else
	                visibleBtn:loadTextureNormal("cancel_16x16.png",ccui.TextureResType.plistType)
				end
			end
		end
	end
end



-- SceneOp
function SceneEditorUI:saveScene()
	-- body
	self._curScene.data._objCount = self._ObjCount 
	ProjectManager:save()
	EditorConfig:Save()
end

function SceneEditorUI:loadScene()
	local scene = SceneManager:findScene("newScene")
	if not scene then 
		ProjectManager:load(lfs.currentdir())
		scene = SceneManager:findScene("newScene")
	end 
	if not scene then
		return
	end
	self._ObjCount = scene._objCount
	local parent = self._tree:addItem("newScene")
	
	local function createGround(treeNode,ground,gname)
		for i=1,ground:LayerCount() do
			local l = ground:getLayer(i-1)
			local s = self._previewWindow:getSize()
			s.width = s.width*self._designFactor
			local panel = ccui.panel({size = s})
			local name = l._name
			self._layers[gname..name] = { ui = panel,lname = name} -- ui = panelL, lname = lName 
			self._ui[gname]:addChild(panel)
			node = self._tree:addItem(name,treeNode)
			for j=1,l:getObjectCount() do
				local obj = l:getObject(j-1)
				local sprite = ccui.image({image=obj.Filename,z=obj.zOrder})
				sprite:setScaleX(self._designFactor*obj.Scale.x)
				sprite:setScaleY(self._designFactor*obj.Scale.y)
				sprite:pos(cc.pMul(obj.Pos,self._designFactor))
				sprite:setFlippedX(obj.Flip.x)
				sprite:setFlippedY(obj.Flip.y)
				sprite:setRotation(obj.Rotation)
				sprite:setOpacity(obj.Opacity)
				sprite:addTouchEvent({[ccui.TouchEventType.began] = handler(self,self.touchSprite),
									[ccui.TouchEventType.moved] = handler(self,self.moveSprite),
									[ccui.TouchEventType.ended] = handler(self,self.stopSprite),
									[ccui.TouchEventType.canceled] = handler(self,self.stopSprite),
									})
				if obj.Filter then
					obj.Filter:ApplyTo(sprite)
				end
				panel:addChild(sprite)
				sprite.data = obj
				sprite.name = obj.name
				self._objects[sprite.name] = sprite
			end
		end

		self._Grounds[treeNode] = ground
	end
	self:addSceneUI(scene._width)	
	createGround(self._tree:addItem("背景",parent),scene._BackGround,"背景")
	--createGround(self._tree:addItem("地板",parent),scene._Floor,"地板")
	self._Grounds[self._tree:addItem("地板",parent)] = scene._Floor
	createGround(self._tree:addItem("前景",parent),scene._FrontGround,"前景")
	self._tree:Layout()
end

function SceneEditorUI:newScene()
	local scene = SceneManager:findScene("newScene")
	if scene then return end 
	scene = ProjectManager:newScene("newScene")
	local parent = self._tree:addItem("newScene")
	self._Grounds[self._tree:addItem("背景",parent)] = scene._BackGround
	self._Grounds[self._tree:addItem("地板",parent)] = scene._Floor
	self._Grounds[self._tree:addItem("前景",parent)] = scene._FrontGround
	self:addSceneUI(scene._width)
	self._tree:Layout()
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
	SceneManager:removeScene("newScene")
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
	if self._curGround.name == "背景" then
		local name = "层"..self._curGround.data.layerNo+1
        
		local node = nil    -- 为数节点内部名称：如child1
		local s = self._previewWindow:getSize()
		s.width = s.width*self._designFactor
		local panel = ccui.panel({size = s,touch = false})
		local layerData = nil
		local index = 0
		local nodeNo = nil
		local undotype = 0    -- 判断有没有执行undo语句块
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
			--nodeNo = self._tree:getNodePos(treeN)
			self._tree:removeItem(node)
			self._tree:Layout()
			undotype = 1
			--self._tree:print()
		end,            
			redo = function()

			if undotype == 1 then 
				cclog("---重做层 layer:"..layerData._name)
				index = self._curGround.data:addLayer(layerData,index)
				self._layers[self._curGround.name..name] = { ui = panel, lname = name }
				self._curGround.ui:addChild(panel)
			    node = self._tree:addItem(name,self._curGround.treeNode,nodeNo,node)
			    nodeNo = self._tree:getNodePos(node)
			else
				local l = GroundLayer.new(self._curGround.data,name)
				index = self._curGround.data:addLayer(l)
				layerData = self._curGround.data:getLayer(index)
				self._layers[self._curGround.name..name] = { ui = panel, lname = name }
				self._curGround.ui:addChild(panel)
                node = self._tree:addItem(name,self._curGround.treeNode)
                nodeNo = self._tree:getNodePos(node)
			end
			self._tree:Layout()
			--self._tree:print()
		end,
			destory = function()
			CC_SAFE_RELEASE(self._tree)
			CC_SAFE_RELEASE(panel)
		end
		}
		local cmd = CustomCommand.new(cmdt)
		Do(cmd)
	end
	self._tree:print()
end

function SceneEditorUI:removeLayer()
--	cclog("-----删除层前----")
--	self._tree:print()
    --local indexL = self._curLayer.ui.idx
    if self._curlayer.ui == 0 then return end
    local lName = self._curLayer.ui.lname
    --local layerN = self._curLayer.data._name
    local panelL = self._curLayer.ui.ui
    --local layerData = self._curGround.data:getLayer(lName)
    local layerData = self._curLayer.data
    local indexL = self._curGround.data:getIndex(lName)
    local treeN  = self._curLayer.treeNode
--    cclog("--lname:"..lName.."   indexl:"..indexL.."   treeN:"..treeN)
    local nodeNo = nil
    local cmdt = 
    {
        tips = "删除层",
        init = function()
			CC_SAFE_RETAIN(self._tree)
			CC_SAFE_RETAIN(panelL)
		end,
        undo = function()
			self._curGround.data:addLayer(layerData,indexL)
			self._layers[self._curGround.name..lName] ={ ui = panelL, lname = lName }
			self._curGround.ui:addChild(panelL)
			treeN = self._tree:addItem(lName,self._curGround.treeNode,nodeNo,treeN)
			cclog("treeN:"..treeN)
			self._curLayer.treeNode = treeN
			self._tree:Layout()
        end,
        redo = function()
            self._curGround.data:removeLayer(indexL)
            self._layers[self._curGround.name..lName] = nil
            self._curGround.ui:removeChild(panelL)
            nodeNo = self._tree:getNodePos(treeN)
            cclog("删除层：nodePos:"..nodeNo.."  treeNode:"..treeN.."  index:"..indexL)
            self._tree:removeItem(treeN)
            self._tree:Layout()   
            	cclog("-----删除层后----")
	self._tree:print()
        end,
			destory = function()
			CC_SAFE_RELEASE(self._tree)
			CC_SAFE_RELEASE(panelL)
		end
    }
	local cmd = CustomCommand.new(cmdt)
	Do(cmd)
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
	local filename = PlatformUtility:OpenFile("E:\\","Png;Jpg(*.png,*.Jpg)\0*.png;*.jpg;*.plist;*.ExportJson\0")
	local name = self._curLayer.data._name
	cclog("cur layer name:"..name)
	if filename == "" then return end
	self._ObjCount = self._ObjCount+1
	self:addImage(filename,name)
end

function SceneEditorUI:addObjItem(name,index)
	cclog("addObjItem index:"..index)
	self._ObjList:insertDefaultItem(index)
	local item = self._ObjList:getItem(index)
	item:getChild("Label"):setString(name)
	local lockBtn = item:getChild("LockBtn")
	local visibleBtn = item:getChild("VisibleBtn")

    local object = nil
    --循环对象编号寻找指定名字的对象
    for k,v in pairs(self._objects) do 
        if k == name then
           object = v
        end
    end
    if object then
        lockBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(btn)
			cclog("lock btn handler")

            local cmdt = {
                tips = "点击锁定按钮",
                init = function()
                	-- body
                
                end,
                undo = function()
                	-- body
					if object.data.locked then
                    	object.data.locked = false
        	        else
                        object.data.locked = true
        	        end
        	        self:updateObjList(object)
        	        object:setTouchEnabled(object.data.locked==false)
        	        self:setupObjectPanel(object.data)
                end,
                redo = function()
                	-- body
                	if object.data.locked then

                    	object.data.locked = false
        	        else
                        object.data.locked = true
        	        end
        	        self:updateObjList(object)
        	        object:setTouchEnabled(object.data.locked==false)
        	        self:setupObjectPanel(object.data)
                end,
                destory = function()

                end,
            }

           local cmd = CustomCommand.new(cmdt)
           Do(cmd)
		end,})

	    visibleBtn:addTouchEvent({[ccui.TouchEventType.ended] = 
		function(btn)

            local cmdt = {
                tips = "点击隐藏按钮",
                init = function()
                	-- body
                
                end,
                undo = function()
                	-- body
					if object.data.visible then
                    	object.data.visible = false
        	        else
                        object.data.visible = true
        	        end
        	        self:updateObjList(object)
        	        object:setVisible(object.data.visible)
                end,
                redo = function()
                	-- body
                	if object.data.visible then
                    	object.data.visible = false

        	        else
                        object.data.visible = true
        	        end
        	        self:updateObjList(object)
        	        object:setVisible(object.data.visible)
                end,
                destory = function()

                end,
            }

           local cmd = CustomCommand.new(cmdt)
           Do(cmd)
		end})
    end
end

function SceneEditorUI:removeObjItem(name)
	local items = self._ObjList:getItems()
    for k,v in pairs(items) do 
    	cclog("v:getChild('Label'):getString():"..v:getChild("Label"):getString())
    	if v:getChild("Label"):getString()  == name then
            self._ObjList:removeItem(k-1)
    	end
	end
end

function SceneEditorUI:addImage(filename,layername)

    local sprite = nil
    local objtype = -1 
    if string.find(filename,"%.plist") then 
        sprite = ccui.particle(filename)
        objtype = 2
    elseif string.find(filename,"%.ExportJson") then
    	sprite = ccui.animationNode(filename)
    	objtype = 3
    else
		sprite = ccui.image({image=filename})
		objtype = 0
	end

	local objInfo = clone(SceneObject)
	local pos = nil
	local prevObject = self._object

	local undotype = -1
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
			CC_SAFE_RETAIN(self._ObjList)
			if objtype == 2 then 
                sprite.name = "Particle"..self._ObjCount
			elseif objtype == 3 then
                sprite.name = "Animation"..self._ObjCount
			else
                sprite.name = "Object"..self._ObjCount
			end
			objInfo.name = sprite.name
			sprite.data = objInfo
		end,
		undo = function()
            self:removeObjItem(self._object.name)
			self._curLayer.data:removeObject(self._object.data)
			self._objects[self._object.name] = nil
			if self._object then
				self._object:getVirtualRenderer():setDrawBound(false)
			end
			self._layers[self._curGround.name..layername].ui:removeChild(sprite)

			self._object = prevObject
			local data = nil
			if prevObject then
				data = prevObject.data
				prevObject:getVirtualRenderer():setDrawBound(true) 
			end

			self:setupObjectPanel(data)
			self:setupFilter(self._object,data)
			undotype = 1
			self:updateObjList(self._object)
		end,
		redo = function()
			if prevObject then
				prevObject:getVirtualRenderer():setDrawBound(false)
			end
			self._object = sprite
			self._object.data = sprite.data
			self._object.name = sprite.name
			cclog(self._object.name)
			cclog(tostring(self._object.data))
			sprite:getVirtualRenderer():setDrawBound(true)
            cclog("self._curGround.name..layername:"..self._curGround.name..layername)
			self._layers[self._curGround.name..layername].ui:addChild(sprite)
			pos = self._curLayer.data:addObject(self._object.data)
			self._object.index = pos
			self._objects[self._object.name] = sprite
			self:setupObjectPanel(self._object.data)
			self:setupFilter(self._object,self._object.data)
			self:addObjItem(self._object.name,pos)
			self:updateObjList(self._object)
		end,
		destory = function()
			CC_SAFE_RELEASE(sprite)
			CC_SAFE_RELEASE(prevObject)
			CC_SAFE_RELEASE(self._ObjList)
		end,
	}
	local cmd = CustomCommand.new(cmdt)
	Do(cmd)
end

function SceneEditorUI:touchSprite(image)
	self:CMD_SelectSprite(image)
	self._spos = image:getTouchBeganPosition()
	if self._object then
		self._object.spos = self._object:pos()
		self._object.offset = cc.pSub(self._object.spos,self._spos)
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
	pos.x = math.floor(pos.x)
	pos.y = math.floor(pos.y)
	self._object:pos(pos)
	local Pos_x = self._layer:getChild("Pos_x")
	Pos_x:setText(string.format("%d",math.floor(pos.x/self._designFactor)))
	local Pos_y = self._layer:getChild("Pos_y")
	Pos_y:setText(string.format("%d",math.floor(pos.y/self._designFactor)))
	self._layer:getChild("preview_Scroll"):jumpToPercentHorizontal(self._offset.x)
end

function SceneEditorUI:stopSprite(image)
	local epos = image:getTouchEndPosition()
	if self._object then
		self._object:pos(self._object.spos)
		epos = cc.pAdd(epos,self._object.offset)
		epos = cc.p(epos.x/self._designFactor,epos.y/self._designFactor)
		self:CMD_MoveObject(self._object,epos)
	end
	self._layer:getChild("preview_Scroll"):scrollToPercentHorizontal(self._offset.x,0.01,false)
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
			  CC_SAFE_RETAIN(prevObject)
          end,

          undo = function()
          	self._object = prevObject
          	if prevObject then 
				local objInfotemp = prevObject.data
				self._layers[self._curGround.name..fn].ui:addChild(prevObject)
				self:setupObjectPanel(objInfotemp)
				self:setupFilter(self._object,objInfotemp)
				self._curLayer.data:addObject(objInfotemp,self._object.index)
				self:addObjItem(self._object.name,self._object.index)
				self:updateObjList(self._object)
				self._objects[self._object.name] = self._object
          	end
          end,
          redo = function()
	        self._curLayer.data:removeObject(self._object.data)
          	self._layers[self._curGround.name..fn].ui:removeChild(self._object)
          	self:setupObjectPanel(nil)
          	self:setupFilter(nil,nil)
          	self:removeObjItem(self._object.name)
          	self._objects[self._object.name] = nil
          	self._object = nil

          	self:updateObjList(self._object)
          end,
          destory = function()
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

	local prevTouchNode = self._selected   --记录前一个树节点

	self._selected = self._tree:getSelectedItem()
	--[[
    if prevTouchNode == nil then
        cclog(" self._selected.name:"..self._selected.name)
    else
    	cclog(" prevTouchNode.name:"..prevTouchNode.name.." self._selected.name:"..self._selected.name)
    end
    ]]
    local undotype = nil
    local curTouchNode = nil
--    self.touchNode = self._selected

	--local prevObject = self._object   -- 将当前对象赋值给前面对象

    local prevselectType = self.selectedType
	local prevScene = {} 
	local prevGround = {}
	local prevLayer = {}
    if self.selectedType >= 0 then
	    prevScene = self._curScene
	    prevScene.data = self._curScene.data
	    prevScene.treeNode = self._curScene.treeNode
    end 
    if self.selectedType >= 1 then
	    prevGround = self._curGround
	    prevGround.data = self._curGround.data
	    prevGround.treeNode = self._curGround.treeNode
	    prevGround.ui = self._curGround.ui
	    prevGround.name = self._curGround.name
	    prevGround.treeNode = self._curGround.treeNode
	end
    if self.selectedType >= 2 then
	    prevLayer.data = self._curLayer.data
		prevLayer.treeNode = self._curLayer.treeNode
		prevLayer.ui = self._curLayer.ui 
    end

	if self._selected == nil then return end
	local cmdt = 
	{
		tips = "选择树:"..self._selected.value,
		redo = function()
            local node = nil
		    if undotype == 1 then
				node = curTouchNode
            else
            	node = self._selected
		    end
			self._selectedType = -1
			
			while node ~= nil do
				 if node.P == nil then
				 	self._curScene.data = SceneManager:findScene(node.value)
				 	self._curScene.treeNode = node.name
				 	cclog("curScene:"..node.value)
				 	
				 	--self.curTouchNode = nil
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
				 	--self.curTouchNode = nil
				 	cclog("curGround:"..node.value)
				 end
				 node = node.P
				 self._selectedType = self._selectedType + 1
				 self.selectedType = self._selectedType
			end
            
            --当点击ground对象时
            if self._selectedType == 1 then
                for k,v in pairs(self._layers) do     -- 遍历层对象
                    if v.ui ~= nil then 
	                    if string.find(k,self._curGround.name) then
	                    	v.ui:setOpacity(255)
	                    	local childs = v.ui:getChildren()
	                    	for k1,v1 in pairs(childs) do
                                v1:setTouchEnabled(true)
	                    	end
	                    else
	                        v.ui:setOpacity(60)
	                        local childs = v.ui:getChildren()
	                    	for k1,v1 in pairs(childs) do
                                v1:setTouchEnabled(false)
	                    	end
	                    end
	                end
                end
            end

	        if self._selectedType == 2 then

                if undotype == 1 then
                    self._curLayer.data = self._curGround.data:getLayer(curTouchNode.value)
					cclog("选择层名为:"..self._curLayer.data._name)
					self._curLayer.treeNode = curTouchNode.name
					self._curLayer.ui = self._layers[self._curGround.name..curTouchNode.value]
					self:setupLayerPanel(self._curLayer.data)
	                cclog("  self._curLayer.treeNode:"..self._curLayer.treeNode)

	                for k,v in pairs(self._layers) do     -- Ñ¡ÖÐ²ã¸ßÁÁÏÔÊ¾
	                    if k == self._curGround.name..curTouchNode.value then
	                    	v.ui:setOpacity(255)
	                    	local childs = v.ui:getChildren()
	                    	for k1,v1 in pairs(childs) do
                                v1:setTouchEnabled(true)
	                    	end
	                    else
	                        v.ui:setOpacity(60)
	                        local childs = v.ui:getChildren()
	                    	for k1,v1 in pairs(childs) do
                                v1:setTouchEnabled(false)
	                    	end
	                    end 
	                end                   
                else
	                self._curLayer.data = self._curGround.data:getLayer(self._selected.value)
					cclog("选择层名为:"..self._curLayer.data._name)
					self._curLayer.treeNode = self._selected.name
					self._curLayer.ui = self._layers[self._curGround.name..self._selected.value]
					self:setupLayerPanel(self._curLayer.data)
	                cclog("  self._curLayer.treeNode:"..self._curLayer.treeNode)

	                for k,v in pairs(self._layers) do     -- 遍历层对象
	                	cclog("点击层 self._curGround.name..self._selected.value:"..self._curGround.name..self._selected.value)
	                    if v.ui ~= nil then 
		                    if k == self._curGround.name..self._selected.value then
		                    	v.ui:setOpacity(255)
		                    	--v.ui:setTouchEnabled(true)
		                    	local childs = v.ui:getChildren()
		                    	for k1,v1 in pairs(childs) do
                                    v1:setTouchEnabled(true)
		                    	end
		                    else
		                        v.ui:setOpacity(60)
		                        --v.ui:setTouchEnabled(false)
		                        local childs = v.ui:getChildren()
		                    	for k1,v1 in pairs(childs) do
                                    v1:setTouchEnabled(false)
		                    	end
		                    end
		                end
                    end
                end
				
			    --删除对象结构panel
                self._ObjList:removeAllItems()
                
                --重新生成objList
                for i=0,self._curLayer.data._objectsVector:count()-1 do  --遍历当前层所有对象
                    local objdata = self._curLayer.data._objectsVector:at(i)
                    for k,v in pairs(self._objects) do
                    	--cclog("  k:"..k.." v.data.Filename:"..v.data.Filename)
                        if v.data == objdata then
                            self:addObjItem(k,i)
                        end
                    end
                end
                
                --默认显示当前层的第一个对象
                --[[if self._curLayer.data._objectsVector:count() > 0 then
                    cclog("-----当前层有对象")
                    local imagedata = self._curLayer.data:getObject(0)
                    for k,v in pairs(self._objects) do 
	    				if v.data == imagedata then
	    					self._object = v
	    					self._object.data = imagedata
	            			break
	    				end
    			    end

                    --self._object = self._objects[imagedata.name]
                    --self._object.

    			    if prevObject then
					    prevObject:getVirtualRenderer():setDrawBound(false)
					end
					self._object:getVirtualRenderer():setDrawBound(true)
					self:setupObjectPanel(self._object.data)
					self:setupFilter(self._object,self._object.data)
                end]]
                
            end

			if self._selectedType > 2 then

            end
           --[[ if undotype ~=1 then 
            self.touchNode = clone(self._selected)
            curTouchNode = self.touchNode
            cclog("self.touchNode:"..self.touchNode.name)
            end]]

            --如果执行了撤销操作，则更换树节点方框标示
            if undotype == 1 then
                if prevTouchNode ~= nil then
                	cclog("重做前节点  prevTouchNode:"..prevTouchNode.name.."  curTouchNode:"..curTouchNode.name)
                    self._tree:selectNode(prevTouchNode.name,curTouchNode.name)
                else
                	self._tree:selectNode(nil,curTouchNode.name)
                end
                self._selected = curTouchNode
            else
            	 if prevTouchNode ~= nil then
                	cclog("前节点  prevTouchNode:"..prevTouchNode.name.."  self._selected:"..self._selected.name)
                    self._tree:selectNode(prevTouchNode.name,self._selected.name)
                else
                	self._tree:selectNode(nil,self._selected.name)
                end
                curTouchNode = self._selected
            end

		end,
	    undo = function()
            if prevselectType >= 0 then 
                self._curScene.data = prevScene.data
				self._curScene.treeNode = prevScene.treeNode

			 	--[[self._curGround.data = nil
			 	self._curGround.treeNode =  nil
			 	self._curGround.ui =  nil
			 	self._curGround.name = nil

                self._curLayer.data = nil
                self._curLayer.data = nil
			    self._curLayer.treeNode = nil
			    self._curLayer.ui = nil ]]
            end
            if prevselectType >= 1 then

                    if self._curGround.ui ~= nil then
				 		--self._curGround.ui:setVisible(false)
				 	end
				 	--cclog("prevGround treeNode:"..prevGround.treeNode.." prevGround name:"..prevGround.name)
				 	self._curGround = prevGround
				 	prevGround.data = self._Grounds[prevGround.treeNode]
				 	self._curGround.data = prevGround.data
				 	self._curGround.treeNode =  prevGround.treeNode
				 	self._curGround.ui =  prevGround.ui --self._ui[prevTouchNode.value]
				 	self._curGround.name = prevGround.name
                    cclog("self._curGround.treeNode:"..self._curGround.treeNode)

                   --[[ self._curLayer.data = nil
                    self._curLayer.data = nil
				    self._curLayer.treeNode = nil
				    self._curLayer.ui = nil ]]

            end
            if prevselectType >= 2 then
	            self._curLayer.data = prevLayer.data
				self._curLayer.treeNode = prevLayer.treeNode
				self._curLayer.ui = prevLayer.ui
				self:setupLayerPanel(self._curLayer.data)
				if self._curLayer.data ~= nil then
                   cclog("self._curLayer.data._name:"..self._curLayer.data._name)
                end

                for k,v in pairs(self._layers) do     -- 显示该层对象
                	if k == self._curGround.name..prevTouchNode.value then
                    	v.ui:setOpacity(255)
                    	local childs = v.ui:getChildren()
                    	for k1,v1 in pairs(childs) do
                            v1:setTouchEnabled(true)
                    	end
                    else
                        v.ui:setOpacity(60)
                        local childs = v.ui:getChildren()
                    	for k1,v1 in pairs(childs) do
                            v1:setTouchEnabled(false)
                    	end
                    end
                end
                

                --删除对象结构panel
                self._ObjList:removeAllItems()
                
                --重新生成objList
                for i=0,self._curLayer.data._objectsVector:count()-1 do  --遍历当前层所有对象
                    local objdata = self._curLayer.data._objectsVector:at(i)
                    for k,v in pairs(self._objects) do
                        if v.data == objdata then
                            self:addObjItem(k,i)
                        end
                    end
                end

                --默认高亮显示图层中第一个对象
               --[[ if self._curLayer.data._objectsVector:count() > 0 then
                    self._object.data = self._curLayer.data:getObject(0)
                    for k,v in pairs(self._objects) do 
	    				if v.data == self._object.data then
	            			self._object = v
	    				end
    			    end
    			    if prevObject then
					    prevObject:getVirtualRenderer():setDrawBound(false)
					end
					self._object:getVirtualRenderer():setDrawBound(true)
					self:setupObjectPanel(self._object.data)
					self:setupFilter(self._object,self._object.data)
                end]]
            end
            
            if prevselectType == -1 then
                self._curScene.data = nil
				self._curScene.treeNode = nil
				self._curScene.ui = 0
 
			 	self._curGround.data = nil
			 	self._curGround.treeNode =  nil
			 	self._curGround.ui =  nil
			 	self._curGround.name = nil

	            self._curLayer.data = nil
				self._curLayer.treeNode = nil
				self._curLayer.ui = nil

            end
            
		    undotype = 1
		    if prevTouchNode == nil then
                self._tree:selectNode(self._selected.name)
            else
            	self._tree:selectNode(self._selected.name,prevTouchNode.name)
		    end

            if prevTouchNode == 1 then
                for k,v in pairs(self._layers) do     -- 遍历层对象
                    if v.ui ~= nil then 
	                    if string.find(k,self._curGround.name) then
	                    	v.ui:setOpacity(255)
	                    	local childs = v.ui:getChildren()
	                    	for k1,v1 in pairs(childs) do
                                v1:setTouchEnabled(true)
	                    	end
	                    else
	                        v.ui:setOpacity(60)
	                        local childs = v.ui:getChildren()
	                    	for k1,v1 in pairs(childs) do
                                v1:setTouchEnabled(false)
	                    	end
	                    end
	                end
                end

            end

          --[[  for k,v in pairs(self._layers) do
            	if prevTouchNode ~= nil then
                    if k == self._curGround.name..prevTouchNode.value then
                	    v.ui:setOpacity(255)
                    else
                        v.ui:setOpacity(20)
                    end
            	end  
            end ]]
            self._selected = prevTouchNode
            --[[if self._curLayer.data._objectsVector:count() > 0 then
                self._object.data = self._curLayer.data:getObject(0)
                for k,v in pairs(self._objects) do 
    				if v == self._object.data then
            			self._object = k
            			break
    				end
			    end
			    if prevObject then
				    prevObject:getVirtualRenderer():setDrawBound(false)
				end
				self._object:getVirtualRenderer():setDrawBound(true)
				self:setupObjectPanel(self._object.data)
				self:setupFilter(self._object,self._object.data)
            end]]

		end,
	}

	local cmd = CustomCommand.new(cmdt)
	Do(cmd)
	
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