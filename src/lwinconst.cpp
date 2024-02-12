#include <Windows.h>
#include "lua.h"
#include "lwinlib.h"

void luaconst_win(lua_State* L) {

    /* Windows messages */
    lua_pushinteger(L, WM_HOTKEY);
    lua_setglobal(L, "WM_HOTKEY");

    /* The modifiers of hotkey */
    lua_pushinteger(L, MOD_ALT);
    lua_setglobal(L, "MOD_ALT");

    lua_pushinteger(L, MOD_CONTROL);
    lua_setglobal(L, "MOD_CONTROL");

    lua_pushinteger(L, MOD_SHIFT);
    lua_setglobal(L, "MOD_SHIFT");

    lua_pushinteger(L, MOD_LEFT);
    lua_setglobal(L, "MOD_LEFT");

    lua_pushinteger(L, MOD_RIGHT);
    lua_setglobal(L, "MOD_RIGHT");

    lua_pushinteger(L, MOD_ON_KEYUP);
    lua_setglobal(L, "MOD_ON_KEYUP");

    lua_pushinteger(L, MOD_IGNORE_ALL_MODIFIER);
    lua_setglobal(L, "MOD_IGNORE_ALL_MODIFIER");
}