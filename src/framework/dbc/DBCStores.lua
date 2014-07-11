local dbc = dbc or {}
cclog("required dbc module")
if not u8 then
	cclog("dbc module depend on bytebuffer module!")
end
local dbcloader = import(".DBCLoader")

cclog("==================================================")
cclog(" define a global function 'Array' for dbc's entry")
Array = function(name,size,value)
    local t = {}
    t.name = name
    for i=1,size do
        t[i] = value
    end
    return t
end
cclog("==================================================")

function dbc.load(entry)
	return dbcloader.load(entry)
end

return dbc