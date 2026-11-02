#include <Windows.h>
#include <string>
#include <lua.hpp>

#include "libzhl.h"
#include "HookSystem.h"

namespace lua
{
    LIBZHL_API void TableAssoc(
        lua_State* L,
        const std::string& name,
        lua_CFunction fn
    );
}

class LuaEngine
{
public:
    void RegisterClasses();
};

using LuaCreateTable = void (__cdecl*)(lua_State*, int, int);
using LuaPushString = const char* (__cdecl*)(lua_State*, const char*);
using LuaSetGlobal = void (__cdecl*)(lua_State*, const char*);

static LuaPushString g_LuaPushString = nullptr;

static int Lua_MyNativeMod_Test(lua_State* L)
{
    if (!g_LuaPushString)
        return 0;

    g_LuaPushString(L, "Native plugin is working!");
    return 1;
}

HOOK_METHOD_PRIORITY(LuaEngine, RegisterClasses, 101, () -> void)
{
    super();

    lua_State* L = *reinterpret_cast<lua_State**>(
        reinterpret_cast<unsigned char*>(this) + 0x18
    );

    if (!L)
        return;

    HMODULE luaModule = GetModuleHandleA("Lua5.3.3r.dll");

    if (!luaModule)
        return;

    auto createTable = reinterpret_cast<LuaCreateTable>(
        GetProcAddress(luaModule, "lua_createtable")
    );

    g_LuaPushString = reinterpret_cast<LuaPushString>(
        GetProcAddress(luaModule, "lua_pushstring")
    );

    auto setGlobal = reinterpret_cast<LuaSetGlobal>(
        GetProcAddress(luaModule, "lua_setglobal")
    );

    if (!createTable || !g_LuaPushString || !setGlobal)
        return;

    createTable(L, 0, 1);

    lua::TableAssoc(
        L,
        std::string("Test"),
        Lua_MyNativeMod_Test
    );

    setGlobal(L, "MyNativeMod");
}

extern "C" __declspec(dllexport) int ModInit()
{
    return 0;
}
