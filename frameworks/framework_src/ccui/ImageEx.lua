local ui = ccui
local image = ui.ImageView
local d = display

function image:setShader(shaderName)
	local glprogram = d.getShader(shaderName)
    if glprogram and self:getGLProgram() ~= glprogram then
        cclog("setShader "..shaderName)
        self:getVirtualRenderer():setGLProgram(glprogram)
        self:getVirtualRenderer():setDirty(true)
    end
end

function image:setUniform(name,value)
	local GLProgramState = self:getVirtualRenderer():getGLProgramState()
	local GLProgram = GLProgramState:getGLProgram()
	local uniform = GLProgram:getUniform(name)
	if uniform then
		if uniform.type == gl.INT then
			assert(type(value) == "number")
			GLProgramState:setUniformInt(name,math.floor(value))
		elseif uniform.type == gl.FLOAT then
			assert(type(value) == "number")
			GLProgramState:setUniformFloat(name,value)
		elseif uniform.type == gl.FLOAT_VEC2 then
			assert(type(value) == "table")
			assert(value.x ~= nil and value.y ~= nil)
			GLProgramState:setUniformVec2(name,value)
		elseif uniform.type == gl.FLOAT_VEC3 then
			assert(type(value) == "table")
			assert(value.x ~= nil and value.y ~= nil and value.z ~= nil)
			GLProgramState:setUniformVec3(name,value)
		elseif uniform.type == gl.FLOAT_VEC4 then
			assert(type(value) == "table")
			assert(value.x ~= nil and value.y ~= nil and value.z ~= nil and value.w ~= nil)
			GLProgramState:setUniformVec4(name,value)
		elseif uniform.type == gl.FLOAT_MAT4 then
			assert(type(value) == "table")
			assert(#value == 16)
			GLProgramState:setUniformMat4(name,value)
		end
	else
		cclog("not find uniform : "..name)
	end
end