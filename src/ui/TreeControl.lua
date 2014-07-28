TreeControl = class("TreeControl",function(s,name,handle) return ccui.dragPanel({size = s,colorType = ccui.LayoutBackGroundColorType.solid, color = cc.c3b(255,255,255), opacity = 220}) end)
TreeControl.__index = TreeControl

TreeNode = function()
return
{
	P 		= nil,		-- 父节点		Parent
	B		= nil,		-- 兄弟节点		Brother
	C		= nil,		-- 首孩子节点	Child
	E 		= false,	-- 是否展开		Extend
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
function TreeControl:addItem(name,parent,pos)
	local len = #self._data
	local index = pos or len+1
	local pNode = nil

	if parent and type(parent) ~= "string" then
		cclog("error2")
		return -1
	end

	if parent and self._nodes[parent] == nil then
		cclog("error3")
		return -1
	end

	if index < 1 then
		cclog("error1")
		return -1
	end

	if parent then
		pNode = self._nodes[parent]
		len = pNode.N
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
		self._Ccount = self._Ccount + 1
		node.name = "Child"..self._Ccount
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
			for i=1,index do
				if cNode.B == nil then
					break
				end
				
				cNode = self._nodes[cNode.B]
			end
			if index ~= len then
				node.B = cNode.B
			end
			cNode.B = node.name
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
	local node = self._nodes[name]
	if node then
		local parent = node.P
		if parent then -- 有父节点
			if parent.C == name then -- 是父节点的首孩子节点
				parent.C = node.B 	 -- 指向node的兄弟节点
			end
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

		-- 将自己的孩子从nodes表里删除
		function deleteNode(node)
			if node == nil then return end
			self._nodes[node.name] = nil
			if node.C then
				local child = self._nodes[node.C]
				deleteNode(child)
			end

			if Node.B then
				local brother = self._nodes[node.B]
				deleteNode(brother)
			end
		end
		local child = self._nodes[node.C]
		deleteNode(child)
		self._nodes[name] = nil
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
				--self._nodes[self._SelectItem].W:getChild("Label"):getVirtualRenderer():setShowBound(false)
			end	
			self._SelectItem = node.name
			--node.W:getChild("Label"):getVirtualRenderer():setShowBound(true)
			self:onSelected()
		end})
	self:addChild(widget)
	widget:setVisible(false)
	SET_POS(widget,20*node.D+5,10)
	node.W = widget
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
		if c == nil then
			parent.W:getChild("extendBtn"):setVisible(false)
		end
		while c ~= nil
			do
				local s = ""
				for i=1,c.D do
					s = s.."-"
				end
				cclog(s..c.value.."  H:"..c.H)
				printCNodes(c)
				c.W:setVisible(true)
				c = self._nodes[c.B]
		end
	end

	function printBNodes(root)
		while root ~= nil
		do
			cclog(root.value.."  H:"..root.H)
			if root.E == true then
				printCNodes(root)
			end
			root.W:setVisible(true)
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

function TreeControl:onSelected()
	if self._handle then
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

