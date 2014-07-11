#ifndef __GAMELUABINDING_H
#define __GAMELUABINDING_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int tolua_game_open(lua_State* tolua_S);

#endif // __GAMELUABINDING_H