#ifndef __LUA_ENGINE_H__
#define __LUA_ENGINE_H__

#include <string>
#include <lua.hpp>

namespace smtm {
    class LuaEngine {
    public:
        LuaEngine(void);
        ~LuaEngine(void);

        void RunScript(const std::string filename);
    private:
        lua_State* L;
    };
}

#endif // __LUA_ENGINE_H__
