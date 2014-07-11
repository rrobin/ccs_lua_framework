INT = INT or {}
cclog("required international module")
if not cc then
	cclog("international must be before required lib_cocos2dx.lua!")
end

INT.localeIndex = LOCALE_INDEX -- 这里是在c++里直接定义本地语言版本
if INT.localeIndex == nil then
	cclog("invaild index LOCALE_INDEX == nil")
	INT.localeIndex = 4
end

localeNames = 
{
	"en",
	"ko",
	"fr",
	"de",
	"zh",
	"zhTW",
	"es",
	"exMX",
	"ru",
}

function INT.getLocaleIndex()
	return INT.localeIndex
end

function INT.getLocaleName()
	if INT.localeIndex then
		return localeNames[INT.localeIndex+1]
	else
		return ""
	end
end

function INT.localeFilePath(path)
	if INT.getLocaleName() ~= "" then
       	local s,e = string.find(path,".ExportJson")
       	if s and e then
       	else
       		s,e = string.find(path,".csb")
       	end
        local subStr = string.sub(path,0,s-1)
        local intPath = subStr .. "_" .. INT.getLocaleName() .. ".ExportJson"
        local fullpath = cc.getFullPath(intPath)
        if fullpath and cc.isFileExist(fullpath) then
        	return intPath
        end
        intPath = subStr .. "_" .. INT.getLocaleName() .. ".csb"
        fullpath = cc.getFullPath(intPath)
    	if fullpath and cc.isFileExist(fullpath) then
      		return intPath
    	end
    end
    return path
end

cclog("locale index : "..INT.getLocaleName())