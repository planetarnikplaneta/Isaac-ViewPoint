
#include <Windows.h>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <string>

struct lua_State;
typedef int (__cdecl *lua_CFunction)(lua_State*);

#include "libzhl.h"
#include "HookSystem.h"

// --------------------------------------------------
// Lua table registration
// --------------------------------------------------

namespace lua
{
    LIBZHL_API void TableAssoc(
        lua_State* L,
        const std::string& name,
        lua_CFunction fn
    );
}

// --------------------------------------------------
// Constants
// --------------------------------------------------

static constexpr int PLANET_PL_PRE_DRAW_STRING = 1496;

static constexpr int LUA_TTABLE = 5;
static constexpr int LUA_TFUNCTION = 6;
static constexpr int LUA_TSTRING = 4;

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

using LuaCreateTable = void (__cdecl*)(
    lua_State*, int, int
);

using LuaPushString = const char* (__cdecl*)(
    lua_State*, const char*
);

using LuaPushInteger = void (__cdecl*)(
    lua_State*, long long
);

using LuaSetGlobal = void (__cdecl*)(
    lua_State*, const char*
);

using LuaSetField = void (__cdecl*)(
    lua_State*, int, const char*
);

using LuaGetGlobal = int (__cdecl*)(
    lua_State*, const char*
);

using LuaGetField = int (__cdecl*)(
    lua_State*, int, const char*
);

using LuaRotate = void (__cdecl*)(
    lua_State*, int, int
);

using LuaType = int (__cdecl*)(
    lua_State*, int
);

using LuaToLString = const char* (__cdecl*)(
    lua_State*, int, size_t*
);

using LuaGetTop = int (__cdecl*)(
    lua_State*
);

using LuaSetTop = void (__cdecl*)(
    lua_State*, int
);

using LuaKFunction = int (__cdecl*)(
    lua_State*, int, intptr_t
);

using LuaPCallK = int (__cdecl*)(
    lua_State*,
    int,
    int,
    int,
    intptr_t,
    LuaKFunction
);

// --------------------------------------------------
// Global state
// --------------------------------------------------

static lua_State* g_LuaState = nullptr;

static LuaCreateTable g_LuaCreateTable = nullptr;
static LuaPushString g_LuaPushString = nullptr;
static LuaPushInteger g_LuaPushInteger = nullptr;
static LuaSetGlobal g_LuaSetGlobal = nullptr;
static LuaSetField g_LuaSetField = nullptr;
static LuaGetGlobal g_LuaGetGlobal = nullptr;
static LuaGetField g_LuaGetField = nullptr;
static LuaRotate g_LuaRotate = nullptr;
static LuaType g_LuaType = nullptr;
static LuaToLString g_LuaToLString = nullptr;
static LuaGetTop g_LuaGetTop = nullptr;
static LuaSetTop g_LuaSetTop = nullptr;
static LuaPCallK g_LuaPCallK = nullptr;

static bool g_InStringCallback = false;
static bool g_CallbackErrorLogged = false;

// --------------------------------------------------
// Initialize Lua API
// --------------------------------------------------

static bool InitializeLuaAPI()
{
    HMODULE luaModule = GetModuleHandleA("Lua5.3.3r.dll");

    if (!luaModule)
        return false;

    g_LuaCreateTable = reinterpret_cast<LuaCreateTable>(
        GetProcAddress(luaModule, "lua_createtable")
    );

    g_LuaPushString = reinterpret_cast<LuaPushString>(
        GetProcAddress(luaModule, "lua_pushstring")
    );

    g_LuaPushInteger = reinterpret_cast<LuaPushInteger>(
        GetProcAddress(luaModule, "lua_pushinteger")
    );

    g_LuaSetGlobal = reinterpret_cast<LuaSetGlobal>(
        GetProcAddress(luaModule, "lua_setglobal")
    );

    g_LuaSetField = reinterpret_cast<LuaSetField>(
        GetProcAddress(luaModule, "lua_setfield")
    );

    g_LuaGetGlobal = reinterpret_cast<LuaGetGlobal>(
        GetProcAddress(luaModule, "lua_getglobal")
    );

    g_LuaGetField = reinterpret_cast<LuaGetField>(
        GetProcAddress(luaModule, "lua_getfield")
    );

    g_LuaRotate = reinterpret_cast<LuaRotate>(
        GetProcAddress(luaModule, "lua_rotate")
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
        g_LuaCreateTable &&
        g_LuaPushString &&
        g_LuaPushInteger &&
        g_LuaSetGlobal &&
        g_LuaSetField &&
        g_LuaGetGlobal &&
        g_LuaGetField &&
        g_LuaRotate &&
        g_LuaType &&
        g_LuaToLString &&
        g_LuaGetTop &&
        g_LuaSetTop &&
        g_LuaPCallK;
}

// --------------------------------------------------
// Planet.Test()
// --------------------------------------------------

static int Lua_Planet_Test(lua_State* L)
{
    if (!g_LuaPushString)
        return 0;

    g_LuaPushString(
        L,
        "Native plugin is working!"
    );

    return 1;
}

static int Lua_Planet_PLANTE(lua_State* L)
{
    if (!g_LuaPushString)
        return 0;

    g_LuaPushString(
        L,
        "PLANTE!"
    );

    return 1;
}

// --------------------------------------------------
// Create global Planet table
// --------------------------------------------------

static void RegisterPlanetTable(lua_State* L)
{
    g_LuaCreateTable(L, 0, 2);

    lua::TableAssoc(
        L,
        std::string("Test"),
        Lua_Planet_Test
    );
    
    lua::TableAssoc(
        L,
        std::string("PLANTE"),
        Lua_Planet_PLANTE
    );
    
    g_LuaPushInteger(
        L,
        PLANET_PL_PRE_DRAW_STRING
    );

    g_LuaSetField(
        L,
        -2,
        "PL_PRE_DRAW_STRING"
    );

    g_LuaSetGlobal(
        L,
        "Planet"
    );
}

// --------------------------------------------------
// Log callback errors
// --------------------------------------------------

static void LogCallbackError(
    int errorCode,
    const char* message,
    size_t length
)
{
    FILE* file = fopen("C:\\MyNativeMod.log", "a");

    if (!file)
        return;

    fprintf(
        file,
        "Isaac.RunAdditiveCallback error: %d\n",
        errorCode
    );

    if (message)
    {
        fprintf(
            file,
            "%.*s\n",
            static_cast<int>(length),
            message
        );
    }

    fclose(file);
}

// --------------------------------------------------
// Call Isaac.RunAdditiveCallback
// --------------------------------------------------

static std::string ProcessString(const char* original)
{
    if (!original)
        return "";

    if (!g_LuaState || g_InStringCallback)
        return original;

    if (!g_LuaGetGlobal ||
        !g_LuaGetField ||
        !g_LuaRotate ||
        !g_LuaPushInteger ||
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

    const int originalStackTop = g_LuaGetTop(g_LuaState);

    g_InStringCallback = true;

    // Get Isaac table.
    g_LuaGetGlobal(
        g_LuaState,
        "Isaac"
    );

    if (g_LuaType(g_LuaState, -1) != LUA_TTABLE)
    {
        g_LuaSetTop(g_LuaState, originalStackTop);
        g_InStringCallback = false;
        return currentText;
    }

    // Get Isaac.RunAdditiveCallback.
    g_LuaGetField(
        g_LuaState,
        -1,
        "RunAdditiveCallback"
    );

    if (g_LuaType(g_LuaState, -1) != LUA_TFUNCTION)
    {
        g_LuaSetTop(g_LuaState, originalStackTop);
        g_InStringCallback = false;
        return currentText;
    }

    // Stack:
    // Isaac table
    // RunAdditiveCallback function
    //
    // Move the function before the table, then remove the table.

    g_LuaRotate(
        g_LuaState,
        -2,
        1
    );

    g_LuaSetTop(
        g_LuaState,
        g_LuaGetTop(g_LuaState) - 1
    );

    // Arguments:
    // 1. Callback ID
    // 2. Current string

    g_LuaPushInteger(
        g_LuaState,
        PLANET_PL_PRE_DRAW_STRING
    );

    g_LuaPushString(
        g_LuaState,
        currentText.c_str()
    );

    const int result = g_LuaPCallK(
        g_LuaState,
        2,
        1,
        0,
        0,
        nullptr
    );

    if (result != 0)
    {
        if (!g_CallbackErrorLogged)
        {
            g_CallbackErrorLogged = true;

            size_t length = 0;

            const char* errorMessage = g_LuaToLString(
                g_LuaState,
                -1,
                &length
            );

            LogCallbackError(
                result,
                errorMessage,
                length
            );
        }
    }
    else if (g_LuaType(g_LuaState, -1) == LUA_TSTRING)
    {
        size_t length = 0;

        const char* replacement = g_LuaToLString(
            g_LuaState,
            -1,
            &length
        );

        if (replacement)
        {
            currentText.assign(
                replacement,
                length
            );
        }
    }

    // Restore the original Lua stack.
    g_LuaSetTop(
        g_LuaState,
        originalStackTop
    );

    g_InStringCallback = false;

    return currentText;
}

// --------------------------------------------------
// LuaEngine::RegisterClasses
// --------------------------------------------------

HOOK_METHOD_PRIORITY(
    LuaEngine,
    RegisterClasses,
    101,
    () -> void
)
{
    super();

    g_LuaState = *reinterpret_cast<lua_State**>(
        reinterpret_cast<unsigned char*>(this) + 0x18
    );

    if (!g_LuaState)
        return;

    if (!InitializeLuaAPI())
        return;

    RegisterPlanetTable(g_LuaState);
}

// --------------------------------------------------
// Font::DrawString hook
// --------------------------------------------------

HOOK_METHOD_PRIORITY(
    Font,
    DrawString,
    100,
    (const char* str, Vector pos, Vector scale,
     KColor* color, FontSettings* settings) -> void
)
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
