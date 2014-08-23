require('lfs')

module('fs',package.seeall)

local _chkdir
local _Browse
local _visit
local _rmdir
local _rmfiles

-- Public Functions
-- @param dir 		遍历的目标路径
-- @param filter	筛选器,使用lua的匹配表达式,"*"或者不填写为不筛选
-- @param deep 		遍历深度,不填写或者-1为全部遍历
-- @return table 	以数字为下标的文件名和以文件夹名为下标的嵌套表
-- eg.
-- {
--   "文件1",
--   "文件2",
--   "文件夹1" = { "文件3", "文件4", "文件夹2" = {...},}
-- }
function Browse(dir,filter,deep)
	if not _chkdir(dir) then return nil end
	local b = deep
	if b == nil then b = -1 end
	local curDeep = -1
	return _Browse(dir,filter,deep,curDeep)
end

--- 创建文件夹
-- @param dir  目标文件夹路径
-- @return 如果成功,返回true,如果错误,返回nil和一个错误信息
function mkdir(dir)
	if not _chkdir(dir) then
		return lfs.mkdir(dir)
	end
	return nil,"already exist directory:"..dir
end

--- 删除目标路径下的所有指定文件,可指定深度
-- @param dir 		需要删除文件的目标路径
-- @param filter	筛选器,使用lua的匹配表达式,"*"或者不填写为不筛选
-- @param deep 		遍历深度,不填写或者-1为全部遍历
-- @return 如果成功或者文件夹下没有指定文件,返回true,如果错误,返回nil和一个错误信息
function rmfiles(dir,filter,deep)
	local b = deep
	if b == nil then b = -1 end
	local files = Browse(dir,filter,b)
	if not files then return true end
	return _rmfiles(dir,files)
end

--- 删除目标路径下的所有文件夹和文件
-- @param dir 		目标路径
-- @return 如果成功,返回true,如果错误,返回nil和一个错误信息
function rmdir(dir)
	if _chkdir(dir) then
		return _rmdir(dir)
	end
	return nil,"not exist directory:"..dir
end

-- Prviate Functions
--- 计算深度
function _Browse(dir,filter,deep,curDeep)
	if deep < 0 then
		return _visit(dir,filter,deep,curDeep)
	else
		local cur_d = curDeep+1
		if deep > cur_d then
			return _visit(dir,filter,deep,cur_d)
		else
			return nil
		end  
	end
end

--- 遍历
function _visit(dir,filter,deep,curdeep)
	local iter,dir_obj = lfs.dir(dir)
	local t = nil
	while 1
		do
		local obj = dir_obj:next()
		if obj == nil then break end
		if obj ~= "." and obj ~= ".." then
			if t == nil then t = {} end
			local curDir = dir..'/'..obj
			local mode = lfs.attributes(curDir,"mode")
			if mode == "directory" then
				t[obj] = _Browse(curDir,filter,deep,curdeep)
			elseif mode == "file" then
				if not filter or filter == "*" or string.find(obj, filter) ~= nil then 
                	table.insert(t,obj)
            	end
			end
		end
		if t and table.nums(t) == 0 then
			t = nil
		end
	end
	return t
end

--- 检查文件夹是否存在
function _chkdir(dir)
	local iter,dir_obj = lfs.dir(dir)
	return dir_obj:next()
end

--- 删除文件夹或者文件
function _rmdir(dir)
	local iter,dir_obj = lfs.dir(dir)
	local err = nil
	local ret = nil
	while 1
		do
		local obj = dir_obj:next()
		if obj == nil then break end
		if obj ~= "." and obj ~= ".." then
			local curDir = dir..'/'..obj
			local mode = lfs.attributes(curDir,"mode")
			if mode == "directory" then
				ret,err = _rmdir(curDir)
			elseif mode == "file" then
                ret,err = os.remove(curDir)
			end
			if not ret then
				assert(false,err)
				break
			end
		end
	end
	ret,err = lfs.rmdir(dir)
	return ret,err
end

--- 删除指定路径下的文件
function _rmfiles(dir,files)
	local ret,err = nil,"invalid files"
	for k,v in pairs(files) do
		if type(v) == "table" then
			local curDir = dir.."/"..k
			ret,err = _rmfiles(curDir,v,filter)
		else
			local f = dir.."/"..v
			ret,err = os.remove(f)
		end
		if err then 
			assert(false,err)
			break 
		end
	end
	return ret,err
end