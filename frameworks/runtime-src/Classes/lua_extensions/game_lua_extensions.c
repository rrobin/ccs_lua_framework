#include "game_lua_extensions.h"

#if __cplusplus
extern "C" {
#endif

	// cjson
#include "cjson/lua_cjson.h"

#ifndef WP8
	// filesystem
#include "lfs.h"
#endif
//#include "LuaXML.h"

	static luaL_Reg luax_exts[] = {
		{"cjson", luaopen_cjson_safe},
#ifndef WP8
		{"lfs", luaopen_lfs},
#endif
		//{"LuaXML_lib",luaopen_LuaXML_lib},
		{NULL, NULL}
	};

	void game_lua_extensions(lua_State *L)
	{
		// load extensions
		luaL_Reg* lib = luax_exts;
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "preload");
		for (; lib->func; lib++)
		{
			lua_pushcfunction(L, lib->func);
			lua_setfield(L, -2, lib->name);
		}
		lua_pop(L, 2);
	}

#if __cplusplus
} // extern "C"
#endif