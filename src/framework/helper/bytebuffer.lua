u8 = u8 or {}
cclog("required bytebuffer module")
function u8:new(size)
    if type(size) == "number" then
        return U8Ptr:new(size)
    elseif type(size) == "string" then
        return U8Ptr:new(size,0)
    end
end

function u8:fromString(str,size)
    return U8Ptr:new(str,size)
end

function readU8Array(buffer,size)
	local arr = {}
	for i=1,size do
		arr[i] = buffer:getU8()
	end
	return arr
end

function readU16Array(buffer,size)
	local arr = {}
	for i=1,size do
		arr[i] = buffer:getU16()
	end
	return arr
end

function getU32(buffer)
	return buffer:getU32()
end

function getFloat(buffer)
	return buffer:getFloat()
end

function getByte(buffer)
	return buffer:getU8()
end

function getString(buffer)
	return buffer:getStr()
end