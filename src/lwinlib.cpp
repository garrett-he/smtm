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

#include <Windows.h>
#include "lua.h"
#include "lwinlib.h"

static int win_FindWindow(lua_State* L) {
    const char* className = luaL_optstring(L, 1, NULL);
    const char* windowName = luaL_optstring(L, 2, NULL);

    if (className == NULL && windowName == NULL) {
        return luaL_argerror(L, 1, "class or window name expected");
    }

    HWND hw = ::FindWindow(className, windowName);

    lua_pushinteger(L, (int)hw);

    return 1;
}

static int win_GetActiveWindow(lua_State* L) {
    HWND wnd = ::GetActiveWindow();

    lua_pushinteger(L, (int)wnd);

    return 1;
}

static int win_GetWindowThreadProcessId(lua_State* L) {
    DWORD pid;
    HWND hw = (HWND)luaL_optinteger(L, 1, 0);

    lua_pushinteger(L, ::GetWindowThreadProcessId(hw, &pid));
    lua_pushinteger(L, (int)pid);

    return 2;
}

static int win_OpenProcess(lua_State* L) {
    DWORD access = (DWORD)luaL_optinteger(L, 1, PROCESS_ALL_ACCESS);
    BOOL inherit = (BOOL)luaL_optinteger(L, 2, 0);
    DWORD pid = (DWORD)luaL_optinteger(L, 3, 0);
    HANDLE proc;

    proc = ::OpenProcess(access, inherit, pid);
    lua_pushinteger(L, (int)proc);

    return 1;
}

static int win_ReadProcessMemory(lua_State* L) {
    HANDLE proc = (HANDLE)luaL_optinteger(L, 1, 0);
    LPCVOID addr = (LPCVOID)luaL_optinteger(L, 2, 0);
    SIZE_T len = (SIZE_T)luaL_optinteger(L, 3, 1);
    void* buff = lua_newuserdata(L, len);
    SIZE_T nr = 0;

    lua_pushboolean(L, ReadProcessMemory(proc, addr, buff, len, &nr));
    lua_pushlightuserdata(L, buff);
    lua_pushinteger(L, nr);

    return 3;
}

static int win_WriteProcessMemory(lua_State* L) {
    HANDLE proc = (HANDLE)luaL_optinteger(L, 1, 0);
    LPVOID addr = (LPVOID)luaL_optinteger(L, 2, 0);
    void* buff = lua_touserdata(L, 3);
    SIZE_T len = (SIZE_T)luaL_optinteger(L, 4, 1);
    SIZE_T nw = 0;

    lua_pushboolean(L, WriteProcessMemory(proc, addr, buff, len, &nw));
    lua_pushinteger(L, nw);

    return 2;
}

static int win_GetMessage(lua_State* L) {
    MSG msg = { 0 };
    HWND wnd = (HWND)luaL_optinteger(L, 1, 0);
    UINT fmin = (UINT)luaL_optinteger(L, 3, 0);
    UINT fmax = (UINT)luaL_optinteger(L, 4, 0);

    lua_pushboolean(L, GetMessage(&msg, wnd, fmin, fmax));
    lua_pushinteger(L, (int)msg.hwnd);
    lua_pushinteger(L, (int)msg.message);
    lua_pushinteger(L, (int)msg.wParam);
    lua_pushinteger(L, (int)msg.lParam);
    lua_pushinteger(L, (int)msg.time);
    lua_pushinteger(L, (int)msg.pt.x);
    lua_pushinteger(L, (int)msg.pt.y);

    return 8;
}

static int win_RegisterHotKey(lua_State* L) {
    HWND wnd = (HWND)luaL_optinteger(L, 1, 0);
    int id = (int)luaL_optinteger(L, 2, 0);
    UINT mods = (UINT)luaL_optinteger(L, 3, 0);
    UINT vk = (UINT)luaL_optinteger(L, 4, 0);

    lua_pushboolean(L, RegisterHotKey(wnd, id, mods, vk));

    return 1;
}

static const luaL_Reg winlib[] = {
    { "GetActiveWindow", win_GetActiveWindow },
    { "FindWindow", win_FindWindow },
    { "GetWindowThreadProcessId", win_GetWindowThreadProcessId },
    { "OpenProcess", win_OpenProcess },

    { "ReadProcessMemory", win_ReadProcessMemory },
    { "WriteProcessMemory", win_WriteProcessMemory },

    { "GetMessage", win_GetMessage },
    { "RegisterHotKey", win_RegisterHotKey },

    { NULL, NULL }
};

LUAMOD_API int luaopen_win(lua_State* L) {
    luaL_newlib(L, winlib);

    return 1;
}