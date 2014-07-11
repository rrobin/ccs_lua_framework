
function ccui.menu(params)
	local listener = params.listener
	local menu = ccui.panel(params)

	local function touchChild(point)
		local children = menu:getChildren()
		for k,v in ipairs(children) do
			local uiwidget = tolua.cast(v,widget_table[UI_WIDGET].name)
			if uiwidget:hitTest(point) then
				menu.focused = uiwidget
				return
			end
		end
		menu.focused = nil
	end

	local function TouchBegin(uiwidget)
		local point = menu:getTouchStartPos()
		touchChild(point)
		if menu.focused then
			menu.focused:onTouchBegan(point)
		end 
	end

	local function moveEvent(uiwidget)
		local point = menu:getTouchMovePos()
		if not menu.focused or menu.focused:hitTest(point) == false then
			if menu.focused then
				menu.focused:onTouchCancelled(point)
			end
			touchChild(point)
			if menu.focused then
				menu.focused:onTouchBegan(point)
			end
		elseif menu.focused and menu.focused:hitTest(point) then
			menu.focused:onTouchMoved(point)
		end
	end

	local function TouchEnded(uiwidget)
		local point = menu:getTouchEndPos()
		if menu.focused then
			menu.focused:onTouchEnded(point)
			menu.focused = nil
		end
	end
	defaultcallback = {[ccui.TouchEventType.moved] = moveEvent,
					  [ccui.TouchEventType.began] = TouchBegin,
					  [ccui.TouchEventType.ended] = TouchEnded}
	if listener then
		table.merge(defaultcallback,listener)
	end
	menu:addTouchEvent(defaultcallback)
	return menu
end

--[[自动调整孩子位置的menu]]

function ccui.autoAlignMenu(params)
	local listener = params.listener
	local AlignMenu = ccui.panel(params)

	local function WillAddChildAtIndex(index)
		local count = self:getChildren():count()
		for i = 1,count do
			local uiwidget = tolua.cast(children:objectAtIndex(i-1),widget_table[UI_WIDGET].name)
			local move = nil
			if index > i then
				move = CCMoveTo:create(0.3,uiwidget:getPosition().x - uiwidget:getSize().width/2,uiwidget:getPosition().y)
			else
				move = CCMoveTo:create(0.3,uiwidget:getPosition().x + uiwidget:getSize().width/2,uiwidget:getPosition().y)
			end
			uiwidget:runAction(move)
		end
	end
end