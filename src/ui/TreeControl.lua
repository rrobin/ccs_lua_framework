TreeControl = class("TreeControl",function(s,name,handle) return ccui.dragPanel({size = s,colorType = ccui.LayoutBackGroundColorType.solid, color = cc.c3b(255,255,255), opacity = 220}) end)
TreeControl.__index = TreeControl

TreeNode = function()
return
{
	P 		= nil,		-- 父节点		Parent
	B		= nil,		-- 兄弟节点		Brother
	C		= nil,		-- 首孩子节点	Child
	E 		= true,		-- 是否展开		Extend
	N 		= 0,		-- 孩子数量		Number
	H		= 0,		-- 高度			Height		
	D		= 0,		-- 深度			Depth
	name 	= "",		-- 检索用名字
	value 	= "",		-- 记录控件的名字
	W 		= nil,		-- UIWidget的指针
}
end


function TreeControl:ctor(size,name,handle)
	if not name or type(name) ~= "string" then
		cclog("TreeContorl need a name, must be a string type!")
		return
	end
	self._name = name
	self._data = {}
	self._Pcount = 0
	self._Ccount = 0
	self._nodes = {}
	self._handle = handle
end

function TreeControl:destory()
end

--[[
-- 添加一个节点
]]
function TreeControl:addItem(name,parent,pos,tnname)   --tnname树节点内部名字
	local len = #self._data
	local pNode = nil

	if parent and type(parent) ~= "string" then
		cclog("error2")
		return -1
	end

	if parent and self._nodes[parent] == nil then
		cclog("err or3")
		return -1
	end

	if parent then
		pNode = self._nodes[parent]
		len = pNode.N
		cclog("parent name:"..pNode.value)
	end

	local index = pos or len+1

	if index < 1 then
		cclog("error1")
		return -1
	end

	if index > len then
		index = len+1
	end

	local node = TreeNode()
	if not parent then
		self._Pcount = self._Pcount + 1
		node.name = "Root"..self._Pcount
		--node.E = true
		if name then
			node.value = name
		else
			node.value = node.name
		end
	else
		if tnname == nil then    --当没传名字，取默认名字
		    self._Ccount = self._Ccount + 1
		    node.name = "Child"..self._Ccount
        else
        	node.name = tnname
		end
		if name then
			node.value = name
		else
			node.value = node.name
		end
	end
	self._nodes[node.name] = node
	if pNode == nil then
		if len > 0 then
			local k=1
			if index <= len then
				local prev = self._nodes[self._data[index-1]]
				if prev then
					prev.B = node.name
				end
				node.B = self._data[index]
				k = index
			else
				self._nodes[self._data[len]].B = node.name
			end
			for i=k,len do
				self._nodes[self._data[i]].H = self._nodes[self._data[i]].H + 1
			end
		end

		table.insert(self._data,index,node.name)
	else
		local cNode = nil
		if pNode.C then
			cNode = self._nodes[pNode.C]
		end
		
		if cNode == nil then
			pNode.C = node.name
		else
			local step = 0
			local prevNode = cNode
			cclog("index :"..index)
			cclog("cNode.name : " ..cNode.value)
			while cNode.B ~= nil
				do
				 if step == index-2 or index-2 < 0 then break end
				 cNode = self._nodes[cNode.B]
				 cclog("get Node:"..cNode.value)
				 step = step+1
			end 

			if index == 1 then
				pNode.C = node.name
				node.B = cNode.name
			else
				node.B = cNode.B
				cNode.B = node.name
				if node.B then
					cclog(cNode.value .. "->"..node.value.."->"..self._nodes[node.B].value)
				else
					cclog(cNode.value .. "->"..node.value)
				end
			end
		end
		node.P = pNode
		node.D = pNode.D + 1
		pNode.N = pNode.N + 1

	end
	self:createItem(node)
	return node.name
end

--[[
	删除一个节点
]]
function TreeControl:removeItem(name)
	--cclog("------- 删除节点前---".."\n")
	--self:print()
--	cclog("--------name:"..name)
	local node = self._nodes[name]
	cclog("删除节点名字："..node.name)
	if node then
		node.W:removeFromParent()
		-- 将自己的孩子从nodes表里删除
		function deleteNode(node)
			if node == nil then return end
			node.W:removeSelf(true)
			self._nodes[node.name] = nil
			if node.C then
				local child = self._nodes[node.C]
				deleteNode(child)
			end

			if node.B then
				local brother = self._nodes[node.B]
				deleteNode(brother)
			end
		end
		local child = self._nodes[node.C]
		deleteNode(child)

        local parent = node.P
		if parent then -- 有父节点
			if parent.C == name then -- 是父节点的首孩子节点
				parent.C = node.B 	 -- 指向node的兄弟节点
			else
				--[[
				local namePos = self:getNodePos(name)
				cclog("------namePos:"..namePos)
				namePos = namePos-2
				local nodeTemp = self._nodes[parent.C]         -- 寻找node节点中的前一个兄弟节点
				for i=1,namePos do
					if nodeTemp ~= nil then
                        nodeTemp = self._nodes[nodeTemp.B]
                        cclog("-----nodeTemp.name"..i..":"..nodeTemp.value.."\n")
                    end
				end
				]]
				local tempNode = self._nodes[parent.C]
				while tempNode ~= nil
					do
						if tempNode.B == name then break end
						tempNode = self._nodes[tempNode.B]
				end
				tempNode.B = node.B
			end
			parent.N = parent.N - 1
		else	-- 没有父节点,则是RootNode
			local prev = nil
			for k,v in ipairs(self._data) do
				if v == name then
					if prev then
						prev.B = self._data[k+1]
					end
					table.remove(self._data,k)		-- 从Root节点表里删除自己
					break
				end
				prev = self._nodes[v]
			end
		end
		self._nodes[name] = nil
		self._SelectItem = nil
		--cclog("------- 删除节点后---".."\n")
	    --self:print()
		
	end
end

function TreeControl:createItem(node)
	local widget = ccui.loadWidget("Item.ExportJson")
	--widget:getChild("extendBtn"):setPressedActionEnabled(true)
	widget:getChild("extendBtn"):addTouchEvent({[ccui.TouchEventType.ended] = 
		function(uiwidget)
			self:extend(node.name)
			if uiwidget:getRotation() == 0 then
				uiwidget:setRotation(90)
			else
				uiwidget:setRotation(0)
			end
		end})
	widget:getChild("Label"):setString(node.value)
	widget:getChild("Label"):addTouchEvent({[ccui.TouchEventType.ended] = function(uiwidget)
			if self._SelectItem then
				cclog("--------------- self._SelectItem -------------------"..self._SelectItem)
				self._nodes[self._SelectItem].W:getChild("Label"):getVirtualRenderer():setDrawBound(false)
			end	
			self._SelectItem = node.name
			node.W:getChild("Label"):getVirtualRenderer():setDrawBound(true)
			self:onSelected()
		end})
	self:addChild(widget)
	widget:setVisible(false)
	SET_POS(widget,20*node.D+5,10)
	node.W = widget
end


function TreeControl:selectNode(prevnodename,curnodename)
	if prevnodename then		
        self._nodes[prevnodename].W:getChild("Label"):getVirtualRenderer():setDrawBound(false)
	end
	if curnodename then
		self._nodes[curnodename].W:getChild("Label"):getVirtualRenderer():setDrawBound(true)
	end

end


function TreeControl:extend(name)
	local node = self._nodes[name]
	function disableC(node)
		local c = self._nodes[node.C]
		while c ~= nil
			do
				c.W:setVisible(false)
				c.W:getChild("Label"):setTouchEnabled(false)
				disableC(c)
				c = self._nodes[c.B]
		end
	end
	if node.E == true then
		node.E = false
		disableC(node)
	else
		node.E = true
	end
	self:Layout()
end

function TreeControl:Layout()
	local len = #self._data
	function calcH(node,h)
		if node.B then 
			h = calcH(self._nodes[node.B],h)
		end
		if node.E then
			if node.C then
				h = calcH(self._nodes[node.C],h)
			end
		end
		if node.C == nil then
			node.W:getChild("extendBtn"):setVisible(false)
		else
			node.W:getChild("extendBtn"):setVisible(true)
		end
		node.W:setVisible(true)
		node.W:getChild("Label"):setTouchEnabled(true)
		SET_POS(node.W,node.D*20+5,h)
		--cclog("Layout :"..node.value)
		return h + 40
	end

	local h = calcH(self._nodes[self._data[1]],10)
	self:setInnerContainerSize(cc.size(self:getSize().width,h))
end

function TreeControl:print()
	cclog("=========TreeControl data =========")
	--cclog(table.concat(self._data,"\n"))
	local temp = self._nodes[ self._data[1] ]

	function printCNodes(parent)
		local c = self._nodes[parent.C]
		while c ~= nil
			do
				local s = ""
				for i=1,c.D do
					s = s.."-"
				end
				if c.B ~= nil then
				    cclog(s..c.value.."  NAME:"..c.name.."  H:"..c.H.." D:"..c.D.."  c.B:"..c.B)
			    else
			    	cclog(s..c.value.."  NAME:"..c.name.."  H:"..c.H.." D:"..c.D)
			    end
				printCNodes(c)
				c = self._nodes[c.B]
		end
	end

	function printBNodes(root)
		while root ~= nil
		do
			cclog(root.value.."  H:"..root.H.." D:"..root.D)
			if root.E == true then
				printCNodes(root)
			end
			root = self._nodes[root.B]
		end
	end

	printBNodes(temp)
end

function TreeControl:getSelectedItem()
	if self._SelectItem then
		return self._nodes[self._SelectItem]
	end
	return nil
end

function TreeControl:getNodePos(name)
	local node = self._nodes[name]
	if node == nil then return -1 end
	if node.P == nil then
		if node.B == nil then
			return #self._data
		else
			for idx,v in ipairs(self._data) do
				if v == name then
					--cclog("node idx:"..idx)
					return idx
				end
			end
			assert(false)
		end
	else
		local first = self._nodes[node.P.C]
		if first == node then return 1 end
		local function getIndex(c,n,i)
			if c.B ~= n then
				--cclog(".....c.B:"..c.B)
				i = i+1
				return getIndex(self._nodes[c.B],n,i)
			end
			return i
		end
		local idx = getIndex(first,name,2)
		return idx
	end
end

function TreeControl:onSelected()
	if self._handle then
		cclog("--onSelected:"..self._name)
		self._handle(self._name)
	end
	return self
end

function TreeControl:clear()
	self._data = {}
	self._Pcount = 0
	self._Ccount = 0
	self._nodes = {}
	self:removeAllChildren()
end

return TreeControl

