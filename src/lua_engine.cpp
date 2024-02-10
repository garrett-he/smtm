/**
 * Copyright (C) 2019 Garrett HE <garrett.he@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <exception>
#include "lua_engine.h"

using namespace smtm;

LuaEngine::LuaEngine(void) {
    if (!(L = luaL_newstate())) {
        throw std::exception("lua state memory allocation error.");
    }

    luaL_openlibs(L);
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