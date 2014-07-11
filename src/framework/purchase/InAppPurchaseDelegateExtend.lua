InAppPurchaseDelegateExtend = class("InAppPurchaseDelegateExtend")
InAppPurchaseDelegateExtend.__index = InAppPurchaseDelegateExtend

function InAppPurchaseDelegateExtend.extend(target)
	local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, InAppPurchaseDelegateExtend)
    return target
end

function InAppPurchaseDelegateExtend:handleIAPEvent(enabled,handler)
	if enabled then
		if not handler then
			handler = function(event,content)
				if event == IAP_EVENT_QUERY_FINISH then
					self:onQueryProductFinish()
				elseif event == IAP_EVENT_PURCHASE_FINISH then
					self:onPurchaseFinish(content)
				elseif event == IAP_EVENT_PURCHASE_FAILED then
					self:onPurchaseFailed(content)
				end
			end
			self:registerScriptHandler(handler)
		end
	else
		self:unregisterScriptHandler()
	end
end

function InAppPurchaseDelegateExtend:onQueryProductFinish()
	-- body
end

function InAppPurchaseDelegateExtend:onPurchaseFinish(content)
	-- body
end

function InAppPurchaseDelegateExtend:onPurchaseFailed(desc)
	-- body
end