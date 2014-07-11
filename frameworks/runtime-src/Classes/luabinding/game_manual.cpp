#include "game_manual.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "gameEngine.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

static int tolua_Cocos2d_ByteBuffer_getU64(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getU64'", NULL);
#endif
		{
			uint64 tolua_ret = 0;
			*self >> tolua_ret;
			{
#ifdef __cplusplus
				void* tolua_obj = Mtolua_new((Guid)(tolua_ret));
				tolua_pushusertype(tolua_S,tolua_obj,"Guid");
				tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
				void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Guid));
				tolua_pushusertype(tolua_S,tolua_obj,"Guid");
				tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
			}
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getU64'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Cocos2d_ByteBuffer_getPackGuid(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getU64'", NULL);
#endif
		{
			uint64 tolua_ret = self->readPackGUID();
			{
#ifdef __cplusplus
				void* tolua_obj = Mtolua_new((Guid)(tolua_ret));
				tolua_pushusertype(tolua_S,tolua_obj,"Guid");
				tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
				void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Guid));
				tolua_pushusertype(tolua_S,tolua_obj,"Guid");
				tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
			}
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getU64'.",&tolua_err);
	return 0;
#endif
}

static void extendByteBuffer(lua_State* tolua_S)
{
	lua_pushfstring(tolua_S, "ByteBuffer");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S,-1))
	{
		tolua_function(tolua_S,"getU64",tolua_Cocos2d_ByteBuffer_getU64);
		tolua_function(tolua_S,"getPackGuid",tolua_Cocos2d_ByteBuffer_getPackGuid);
	}
}

int register_all_game_manual(lua_State* tolua_S)
{
	extendByteBuffer(tolua_S);
#ifdef LOCALE_INDEX
	tolua_open(tolua_S);
	tolua_module(tolua_S,NULL,0);
	tolua_beginmodule(tolua_S,NULL);
	tolua_constant(tolua_S,"LOCALE_INDEX",LOCALE_INDEX);
#ifdef VER_ID
	tolua_constant(tolua_S,"VER_ID",VER_ID);
#endif
#ifdef _DEBUG
	tolua_constant(tolua_S,"DEBUG",true);
#endif
	tolua_endmodule(tolua_S);
#endif
	return 0;
}