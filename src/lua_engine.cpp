#include <exception>
#include "lua_engine.h"
#include "lwinlib.h"

using namespace smtm;

LuaEngine::LuaEngine(void) {
    if (!(L = luaL_newstate())) {
        throw std::exception("lua state memory allocation error.");
    }

    luaL_openlibs(L);
    luaopen_win(L);
}

LuaEngine::~LuaEngine(void) {
    lua_close(L);
}

void LuaEngine::RunScript(const std::string filename) {
    if (luaL_loadfile(L, filename.c_str())) {
        throw std::exception(lua_tostring(L, -1));
    }

    if (lua_pcall(L, 0, 0, 0)) {
        throw std::exception(lua_tostring(L, -1));
    }
}