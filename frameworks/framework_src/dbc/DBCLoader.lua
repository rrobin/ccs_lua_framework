local DBCLoader = DBCLoader or {}

local DBCformat =
{
	["x"] = {handler = getU32,size = 4},
	["X"] = {handler = getU32,size = 4},
	["n"] = {handler = getU32,size = 4},
	["i"] = {handler = getU32,size = 4},
	["f"] = {handler = getFloat,size = 4},
	["b"] = {handler = getByte,size = 1},
	["s"] = {handler = getString,size = 4},
}

function DBCLoader.load(entry)
	local filename = cc.getFullPath(entry.filename)
	if cc.isFileExist(filename) == false then
         cclog("required dbc : "..entry.filename.." not found")
         return nil
    end
    local data = cc.getFileData(filename)
    filename = entry.filename
    entry.filename = nil		-- 删除filename字段
    local header = data:getU32()
    --cclog(string.format("dbc header %x",header))
    local recordCount = data:getU32()
    local fieldCount = data:getU32()
    local recordSize = data:getU32()
    local stringSize = data:getU32()

    local fmtLen = string.len(entry.fmt)
    local fmtTable = {}
    local oneRecordSize = 0
    local indexpos = -1
    for i=1,fmtLen do
    	fmtTable[i] = string.sub(entry.fmt,i,i)
    	if fmtTable[i] == "n" then
    		indexpos = oneRecordSize
    	end
    	oneRecordSize = oneRecordSize + DBCformat[fmtTable[i]].size
    end
    entry.fmt = nil 			-- 删除fmt字段

    if fieldCount ~= #fmtTable then
        cclog("dbc "..filename.." exist but have "..fieldCount.." fields instead "..#fmtTable)
        return nil
    end
--[[ 
    引入嵌套表之后,字段数就不应该直接用entry表的字段数来判断了,需要解析entry表内容,太麻烦...省略判断
    if #entry ~= #fmtTable then
        cclog("dbc "..filename.." entry have "..#entry.." keys instead "..#fmtTable)
        return nil
    end
]]
    local dbcStore = {}
    local count = recordCount
   
	local dbc_rpos = data:rpos()
	for i=1,recordCount do
		if indexpos >= 0 then
			data:rpos((i-1)*recordSize+indexpos+dbc_rpos)
			local ind = data:getU32()
			dbcStore[ind] = {}
			if ind > count then
				count = ind
			end
		else
			dbcStore[i] = {}
		end 
    end
    data:rpos(dbc_rpos)
    dbc_rpos = recordSize*recordCount+dbc_rpos  -- 记录读取到的string位置
    local temp_rpos = 0
    local fmt = ""
    function setValue(dstTable,srcTable,buffer,deep)
		local step = 0
        for k,v in ipairs(srcTable) do
            if type(v) == "table" then              -- 当前字段是一个表
				local tempTable = {}        
                if v.name then                      -- 表有名字,是一个数组
					dstTable[v.name] = tempTable
				else
                    dstTable[k-1] = tempTable       -- 表没名字,说明是一个结构体
                end
                step = step + setValue(tempTable,v,buffer,step+deep)
            else
				step = step + 1
                fmt = fmtTable[step+deep]
                if fmt == "s" then                  -- 当是字符串时跳到字符串保存位置
                    temp_rpos = buffer:rpos()
                    temp_rpos = DBCformat[fmt].size + temp_rpos
                    buffer:rpos(dbc_rpos)
                end
                if type(v) == "number" or v == "" then
					dstTable[k-1] = DBCformat[fmt].handler(buffer)
                else
					dstTable[v] = DBCformat[fmt].handler(buffer)
				end
                if fmt == "s" then                  -- 返回读取字符串之前位置,记录当前读取到的字符串位置,下次从该位置继续读取
                    dbc_rpos = buffer:rpos()
                    buffer:rpos(temp_rpos)
                end
            end
        end
        return step
    end

    for i=1,count do
    	if dbcStore[i] then
            setValue(dbcStore[i],entry,data,0)
    	end
    end

    return dbcStore
end

return DBCLoader