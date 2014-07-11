#ifndef GAME_MANUAL_H
#define GAME_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

LUA_API int register_all_game_manual(lua_State* tolua_S);
#endif