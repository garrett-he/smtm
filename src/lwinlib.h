#ifndef __LWINLIB_H__
#define __LWINLIB_H__

#include "lua.h"

LUAMOD_API int luaopen_win(lua_State* L);

void luaconst_win(lua_State* L);

#endif // __LWINLIB_H__