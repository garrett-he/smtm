#include <string.h>
#include "lua.h"
#include "lsmtmlib.h"

void luaconst_smtm(lua_State* L) {
    lua_pushstring(L, SMTM_VERSION);
    lua_setglobal(L, "SMTM_VERSION");
}

static int smtm_udatatointeger(lua_State* L) {
    void* udata = lua_touserdata(L, 1);

    if (udata == NULL) {
        return luaL_argerror(L, 1, "argument is not a valid userdata");
    }

    lua_pushinteger(L, *((int*) udata));

    return 1;
}

static int smtm_udatatostring(lua_State* L) {
    void* udata = lua_touserdata(L, 1);

    if (udata == NULL) {
        return luaL_argerror(L, 1, "argument is not a valid userdata");
    }

    lua_pushstring(L, (char*) udata);

    return 1;
}

static int smtm_integertoudata(lua_State* L) {
    void* ud = lua_newuserdata(L, sizeof(int));
    *(lua_Integer*)ud = lua_tointeger(L, 1);

    lua_pushlightuserdata(L, ud);

    return 1;
}

static int smtm_stringtoudata(lua_State* L) {
    const char* src = lua_tostring(L, 1);
    size_t s = strlen(src) + 1;
    void* ud = lua_newuserdata(L, s);

    strcpy_s((char*)ud, s, src);
    lua_pushlightuserdata(L, ud);

    return 1;
}

static const luaL_Reg smtmlib[] = {
    {"udatatointeger", smtm_udatatointeger},
    {"udatatostring", smtm_udatatostring},
    {"integertoudata", smtm_integertoudata},
    {"stringtoudata", smtm_stringtoudata},
	{NULL, NULL}
};

LUAMOD_API int luaopen_smtm(lua_State* L) {
    luaL_newlib(L, smtmlib);
    luaconst_smtm(L);

    return 1;
}