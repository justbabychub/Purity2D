#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include <string>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <SFML/Graphics.hpp>
#include "movableobject.h"
#include "objectmanager.h"

namespace Purity
{
    class LuaManager
    {
    public:
        ~LuaManager();
        static LuaManager* getManager();

        lua_State* getState();

        void doFile(const std::string& luaFileName);

    private:
        LuaManager();

        lua_State* mLuaState;

        void initializeBindings();
        void initializeSFMLBindings();
    };
}

#endif // LUA_MANAGER_H