#ifndef __LSMTMLIB_H__
#define __LSMTMLIB_H__

#define SMTM_VERSION "1.0.0"

#include "lua.h"

LUAMOD_API int (luaopen_smtm)(lua_State* L);

void luaconst_smtm(lua_State* L);

#endif // __LSMTMLIB_H__