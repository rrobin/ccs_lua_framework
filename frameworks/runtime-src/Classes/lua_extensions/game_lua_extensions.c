#include "game_lua_extensions.h"

#if __cplusplus
extern "C" {
#endif

#ifndef WP8
	// filesystem
#include "lfs.h"
#endif

	static luaL_Reg luax_exts[] = {
#ifndef WP8
		{"lfs", luaopen_lfs},
#endif
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