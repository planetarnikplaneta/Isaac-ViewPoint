
#include <Windows.h>
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

struct lua_State;
typedef int (__cdecl *lua_CFunction)(lua_State*);

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

// --------------------------------------------------
// Minimal game class declarations
// --------------------------------------------------

struct Vector
{
    float x;
    float y;
};

struct KColor;
struct FontSettings;

class Font
{
public:
    void DrawString(
        const char* str,
        Vector pos,
        Vector scale,
        KColor* color,
        FontSettings* settings
    );
};

class LuaEngine
{
public:
    void RegisterClasses();
};

// --------------------------------------------------
// Lua API declarations
// --------------------------------------------------

using LuaCreateTable = void (__cdecl*)(lua_State*, int, int);
using LuaPushString = const char* (__cdecl*)(lua_State*, const char*);
using LuaSetGlobal = void (__cdecl*)(lua_State*, const char*);
using LuaPushValue = void (__cdecl*)(lua_State*, int);
using LuaLRef = int (__cdecl*)(lua_State*, int);
using LuaRawGetI = int (__cdecl*)(lua_State*, int, int);
using LuaType = int (__cdecl*)(lua_State*, int);
using LuaToLString = const char* (__cdecl*)(lua_State*, int, size_t*);
using LuaGetTop = int (__cdecl*)(lua_State*);
using LuaSetTop = void (__cdecl*)(lua_State*, int);

using LuaKFunction = int (__cdecl*)(
    lua_State*,
    int,
    intptr_t
);

using LuaPCallK = int (__cdecl*)(
    lua_State*,
    int,
    int,
    int,
    intptr_t,
    LuaKFunction
);

// Lua 5.3 constants
static constexpr int LUA_REGISTRYINDEX = -1001000;
static constexpr int LUA_TFUNCTION = 6;
static constexpr int LUA_TSTRING = 4;

// --------------------------------------------------
// Global state
// --------------------------------------------------

static lua_State* g_LuaState = nullptr;

static LuaPushString g_LuaPushString = nullptr;
static LuaPushValue g_LuaPushValue = nullptr;
static LuaLRef g_LuaLRef = nullptr;
static LuaRawGetI g_LuaRawGetI = nullptr;
static LuaType g_LuaType = nullptr;
static LuaToLString g_LuaToLString = nullptr;
static LuaGetTop g_LuaGetTop = nullptr;
static LuaSetTop g_LuaSetTop = nullptr;
static LuaPCallK g_LuaPCallK = nullptr;

static std::vector<int> g_StringCallbacks;

static bool g_InStringCallback = false;

// --------------------------------------------------
// MyNativeMod.Test()
// --------------------------------------------------

static int Lua_MyNativeMod_Test(lua_State* L)
{
    if (!g_LuaPushString)
        return 0;

    g_LuaPushString(L, "Native plugin is working!");

    return 1;
}

// --------------------------------------------------
// MyNativeMod.AddCallback(function)
// --------------------------------------------------

static int Lua_MyNativeMod_AddCallback(lua_State* L)
{
    if (!g_LuaType ||
        !g_LuaPushValue ||
        !g_LuaLRef)
    {
        return 0;
    }

    if (g_LuaType(L, 1) != LUA_TFUNCTION)
        return 0;

    // Copy the function and store it in the Lua registry.
    g_LuaPushValue(L, 1);

    const int reference = g_LuaLRef(
        L,
        LUA_REGISTRYINDEX
    );

    g_StringCallbacks.push_back(reference);

    return 0;
}

// --------------------------------------------------
// Initialize Lua API
// --------------------------------------------------

static bool InitializeLuaAPI()
{
    HMODULE luaModule = GetModuleHandleA("Lua5.3.3r.dll");

    if (!luaModule)
        return false;

    g_LuaPushString = reinterpret_cast<LuaPushString>(
        GetProcAddress(luaModule, "lua_pushstring")
    );

    g_LuaPushValue = reinterpret_cast<LuaPushValue>(
        GetProcAddress(luaModule, "lua_pushvalue")
    );

    g_LuaLRef = reinterpret_cast<LuaLRef>(
        GetProcAddress(luaModule, "luaL_ref")
    );

    g_LuaRawGetI = reinterpret_cast<LuaRawGetI>(
        GetProcAddress(luaModule, "lua_rawgeti")
    );

    g_LuaType = reinterpret_cast<LuaType>(
        GetProcAddress(luaModule, "lua_type")
    );

    g_LuaToLString = reinterpret_cast<LuaToLString>(
        GetProcAddress(luaModule, "lua_tolstring")
    );

    g_LuaGetTop = reinterpret_cast<LuaGetTop>(
        GetProcAddress(luaModule, "lua_gettop")
    );

    g_LuaSetTop = reinterpret_cast<LuaSetTop>(
        GetProcAddress(luaModule, "lua_settop")
    );

    g_LuaPCallK = reinterpret_cast<LuaPCallK>(
        GetProcAddress(luaModule, "lua_pcallk")
    );

    return
        g_LuaPushString &&
        g_LuaPushValue &&
        g_LuaLRef &&
        g_LuaRawGetI &&
        g_LuaType &&
        g_LuaToLString &&
        g_LuaGetTop &&
        g_LuaSetTop &&
        g_LuaPCallK;
}

// --------------------------------------------------
// Execute registered string callbacks
// --------------------------------------------------

static std::string ProcessString(const char* original)
{
    if (!original || !g_LuaState || g_InStringCallback)
        return original ? original : "";

    if (g_StringCallbacks.empty())
        return original;

    if (!g_LuaRawGetI ||
        !g_LuaPushString ||
        !g_LuaType ||
        !g_LuaToLString ||
        !g_LuaGetTop ||
        !g_LuaSetTop ||
        !g_LuaPCallK)
    {
        return original;
    }

    std::string currentText(original);

    // Take a snapshot so callbacks can register more callbacks safely.
    const std::vector<int> callbacks = g_StringCallbacks;

    g_InStringCallback = true;

    const int originalStackTop = g_LuaGetTop(g_LuaState);

    for (int reference : callbacks)
    {
        // Push the registered Lua function.
        g_LuaRawGetI(
            g_LuaState,
            LUA_REGISTRYINDEX,
            reference
        );

        // Push the current string as its argument.
        g_LuaPushString(
            g_LuaState,
            currentText.c_str()
        );

        // Call function(text), expecting one result.
        const int result = g_LuaPCallK(
            g_LuaState,
            1,
            1,
            0,
            0,
            nullptr
        );

        if (result == 0 &&
            g_LuaType(g_LuaState, -1) == LUA_TSTRING)
        {
            size_t length = 0;

            const char* replacement = g_LuaToLString(
                g_LuaState,
                -1,
                &length
            );

            if (replacement)
            {
                currentText.assign(replacement, length);
            }
        }

        // Restore the stack before the next callback.
        g_LuaSetTop(g_LuaState, originalStackTop);
    }

    g_InStringCallback = false;

    return currentText;
}

// --------------------------------------------------
// LuaEngine::RegisterClasses hook
// --------------------------------------------------

HOOK_METHOD_PRIORITY(LuaEngine, RegisterClasses, 101, () -> void)
{
    super();

    g_LuaState = *reinterpret_cast<lua_State**>(
        reinterpret_cast<unsigned char*>(this) + 0x18
    );

    if (!g_LuaState)
        return;

    if (!InitializeLuaAPI())
        return;

    auto createTable = reinterpret_cast<LuaCreateTable>(
        GetProcAddress(
            GetModuleHandleA("Lua5.3.3r.dll"),
            "lua_createtable"
        )
    );

    auto setGlobal = reinterpret_cast<LuaSetGlobal>(
        GetProcAddress(
            GetModuleHandleA("Lua5.3.3r.dll"),
            "lua_setglobal"
        )
    );

    if (!createTable || !setGlobal)
        return;

    createTable(g_LuaState, 0, 2);

    lua::TableAssoc(
        g_LuaState,
        std::string("Test"),
        Lua_MyNativeMod_Test
    );

    lua::TableAssoc(
        g_LuaState,
        std::string("AddCallback"),
        Lua_MyNativeMod_AddCallback
    );

    setGlobal(g_LuaState, "MyNativeMod");
}

// --------------------------------------------------
// Font::DrawString hook
// --------------------------------------------------

HOOK_METHOD_PRIORITY(Font, DrawString, 100,
    (const char* str, Vector pos, Vector scale, KColor* color, FontSettings* settings) -> void)
{
    OutputDebugStringA(
        str ? str : "[Font::DrawString received nullptr]"
    );

    super(str, pos, scale, color, settings);
}
{
    if (!str || g_InStringCallback)
    {
        super(str, pos, scale, color, settings);
        return;
    }

    const std::string replacement = ProcessString(str);

    super(
        replacement.c_str(),
        pos,
        scale,
        color,
        settings
    );
}

// --------------------------------------------------
// Plugin entry point
// --------------------------------------------------

extern "C" __declspec(dllexport) int ModInit()
{
    return 0;
}
