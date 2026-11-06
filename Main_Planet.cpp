
#include <Windows.h>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <string>

struct lua_State;
typedef int(__cdecl *lua_CFunction)(lua_State *);

#include "libzhl.h"
#include "HookSystem.h"

// --------------------------------------------------
// Lua table registration
// --------------------------------------------------

namespace lua
{
    LIBZHL_API void TableAssoc(
        lua_State *L,
        const std::string &name,
        lua_CFunction fn);
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

struct KColor
{
    float _red;
    float _green;
    float _blue;
    float _alpha;
    int _unk;

    KColor(
        float r = 1,
        float g = 1,
        float b = 1,
        float a = 1,
        int unk = 0)
        : _red(r),
          _green(g),
          _blue(b),
          _alpha(a),
          _unk(unk)
    {
    }
};

struct FontSettings;

class Font
{
public:
    void DrawString(
        const char *str,
        Vector pos,
        Vector scale,
        KColor *color,
        FontSettings *settings);
};

class LuaEngine
{
public:
    void RegisterClasses();
};

// --------------------------------------------------
// Lua API declarations
// --------------------------------------------------

using LuaCreateTable = void(__cdecl *)(
    lua_State *, int, int);

using LuaPushString = const char *(__cdecl *)(lua_State *, const char *);

using LuaPushInteger = void(__cdecl *)(
    lua_State *, long long);

using LuaPushNumber = void(__cdecl *)(
    lua_State *, double);

using LuaSetGlobal = void(__cdecl *)(
    lua_State *, const char *);

using LuaSetField = void(__cdecl *)(
    lua_State *, int, const char *);

using LuaGetGlobal = int(__cdecl *)(
    lua_State *, const char *);

using LuaGetField = int(__cdecl *)(
    lua_State *, int, const char *);

using LuaRotate = void(__cdecl *)(
    lua_State *, int, int);

using LuaType = int(__cdecl *)(
    lua_State *, int);

using LuaToLString = const char *(__cdecl *)(lua_State *, int, size_t *);

using LuaToNumberX = double(__cdecl *)(
    lua_State *, int, int *);

using LuaGetTop = int(__cdecl *)(
    lua_State *);

using LuaSetTop = void(__cdecl *)(
    lua_State *, int);

using LuaKFunction = int(__cdecl *)(
    lua_State *, int, intptr_t);

using LuaPCallK = int(__cdecl *)(
    lua_State *,
    int,
    int,
    int,
    intptr_t,
    LuaKFunction);

// --------------------------------------------------
// Global state
// --------------------------------------------------

static lua_State *g_LuaState = nullptr;

static LuaCreateTable g_LuaCreateTable = nullptr;
static LuaPushString g_LuaPushString = nullptr;
static LuaPushInteger g_LuaPushInteger = nullptr;
static LuaPushNumber g_LuaPushNumber = nullptr;

static LuaSetGlobal g_LuaSetGlobal = nullptr;
static LuaSetField g_LuaSetField = nullptr;

static LuaGetGlobal g_LuaGetGlobal = nullptr;
static LuaGetField g_LuaGetField = nullptr;

static LuaRotate g_LuaRotate = nullptr;
static LuaType g_LuaType = nullptr;

static LuaToLString g_LuaToLString = nullptr;
static LuaToNumberX g_LuaToNumberX = nullptr;

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

#define LOAD_LUA_FUNCTION(variable, name)            \
    variable = reinterpret_cast<decltype(variable)>( \
        GetProcAddress(luaModule, name))

    LOAD_LUA_FUNCTION(g_LuaCreateTable, "lua_createtable");
    LOAD_LUA_FUNCTION(g_LuaPushString, "lua_pushstring");
    LOAD_LUA_FUNCTION(g_LuaPushInteger, "lua_pushinteger");
    LOAD_LUA_FUNCTION(g_LuaPushNumber, "lua_pushnumber");

    LOAD_LUA_FUNCTION(g_LuaSetGlobal, "lua_setglobal");
    LOAD_LUA_FUNCTION(g_LuaSetField, "lua_setfield");

    LOAD_LUA_FUNCTION(g_LuaGetGlobal, "lua_getglobal");
    LOAD_LUA_FUNCTION(g_LuaGetField, "lua_getfield");

    LOAD_LUA_FUNCTION(g_LuaRotate, "lua_rotate");
    LOAD_LUA_FUNCTION(g_LuaType, "lua_type");

    LOAD_LUA_FUNCTION(g_LuaToLString, "lua_tolstring");
    LOAD_LUA_FUNCTION(g_LuaToNumberX, "lua_tonumberx");

    LOAD_LUA_FUNCTION(g_LuaGetTop, "lua_gettop");
    LOAD_LUA_FUNCTION(g_LuaSetTop, "lua_settop");

    LOAD_LUA_FUNCTION(g_LuaPCallK, "lua_pcallk");

#undef LOAD_LUA_FUNCTION

    return g_LuaCreateTable &&
           g_LuaPushString &&
           g_LuaPushInteger &&
           g_LuaPushNumber &&
           g_LuaSetGlobal &&
           g_LuaSetField &&
           g_LuaGetGlobal &&
           g_LuaGetField &&
           g_LuaRotate &&
           g_LuaType &&
           g_LuaToLString &&
           g_LuaToNumberX &&
           g_LuaGetTop &&
           g_LuaSetTop &&
           g_LuaPCallK;
}

// --------------------------------------------------
// Lua table helpers
// --------------------------------------------------

static void SetNumberField(
    lua_State *L,
    const char *name,
    double value)
{
    g_LuaPushNumber(L, value);
    g_LuaSetField(L, -2, name);
}

static double GetNumberField(
    lua_State *L,
    int table,
    const char *name,
    double fallback)
{
    g_LuaGetField(L, table, name);

    int isNumber = 0;

    double value = g_LuaToNumberX(
        L,
        -1,
        &isNumber);

    g_LuaSetTop(L, -2);

    return isNumber ? value : fallback;
}

static void PushVectorTable(
    lua_State *L,
    float x,
    float y)
{
    g_LuaCreateTable(L, 0, 2);

    SetNumberField(L, "x", x);
    SetNumberField(L, "y", y);
}

static void PushColorTable(
    lua_State *L,
    const KColor *color)
{
    g_LuaCreateTable(L, 0, 4);

    SetNumberField(L, "r", color->_red);
    SetNumberField(L, "g", color->_green);
    SetNumberField(L, "b", color->_blue);
    SetNumberField(L, "a", color->_alpha);
}

// --------------------------------------------------
// Planet.Test()
// --------------------------------------------------

static int Lua_Planet_Test(lua_State *L)
{
    if (!g_LuaPushString)
        return 0;

    g_LuaPushString(
        L,
        "Native plugin is working!");

    return 1;
}

// --------------------------------------------------
// Create global Planet table
// --------------------------------------------------

static void RegisterPlanetTable(lua_State *L)
{
    g_LuaCreateTable(L, 0, 2);

    lua::TableAssoc(
        L,
        std::string("Test"),
        Lua_Planet_Test);

    g_LuaPushInteger(
        L,
        PLANET_PL_PRE_DRAW_STRING);

    g_LuaSetField(
        L,
        -2,
        "PL_PRE_DRAW_STRING");

    g_LuaSetGlobal(
        L,
        "Planet");
}

// --------------------------------------------------
// Log callback errors
// --------------------------------------------------

static void LogCallbackError(
    int errorCode,
    const char *message,
    size_t length)
{
    FILE *file = fopen("C:\\MyNativeMod.log", "a");

    if (!file)
        return;

    fprintf(
        file,
        "Isaac.RunAdditiveCallback error: %d\n",
        errorCode);

    if (message)
    {
        fprintf(
            file,
            "%.*s\n",
            static_cast<int>(length),
            message);
    }

    fclose(file);
}

// --------------------------------------------------
// Call Isaac.RunAdditiveCallback
// --------------------------------------------------

static void ProcessDrawString(
    const char *text,
    Vector &pos,
    Vector &scale,
    KColor *color,
    std::string &replacement)
{
    if (!g_LuaState || g_InStringCallback || !color)
        return;

    const int originalTop = g_LuaGetTop(g_LuaState);

    g_InStringCallback = true;

    // Isaac.RunAdditiveCallback
    g_LuaGetGlobal(g_LuaState, "Isaac");
    g_LuaGetField(g_LuaState, -1, "RunAdditiveCallback");

    // Stack: Isaac, function
    // Move function before Isaac.
    g_LuaRotate(g_LuaState, -2, 1);

    // Remove Isaac.
    g_LuaSetTop(g_LuaState, -2);

    // Callback ID
    g_LuaPushInteger(
        g_LuaState,
        PLANET_PL_PRE_DRAW_STRING);

    // Data table
    g_LuaCreateTable(g_LuaState, 0, 4);

    // text
    g_LuaPushString(
        g_LuaState,
        text ? text : "");

    g_LuaSetField(
        g_LuaState,
        -2,
        "text");

    // pos
    PushVectorTable(
        g_LuaState,
        pos.x,
        pos.y);

    g_LuaSetField(
        g_LuaState,
        -2,
        "pos");

    // scale
    PushVectorTable(
        g_LuaState,
        scale.x,
        scale.y);

    g_LuaSetField(
        g_LuaState,
        -2,
        "scale");

    // color
    PushColorTable(
        g_LuaState,
        color);

    g_LuaSetField(
        g_LuaState,
        -2,
        "color");

    // Isaac.RunAdditiveCallback(callbackID, data)
    int errorCode = g_LuaPCallK(
        g_LuaState,
        2,
        1,
        0,
        0,
        nullptr);

    if (errorCode != 0)
    {
        size_t length = 0;

        const char *error = g_LuaToLString(
            g_LuaState,
            -1,
            &length);

        if (!g_CallbackErrorLogged)
        {
            LogCallbackError(
                errorCode,
                error,
                length);

            g_CallbackErrorLogged = true;
        }

        g_LuaSetTop(g_LuaState, originalTop);
        g_InStringCallback = false;
        return;
    }

    // Returned value must be a table.
    if (g_LuaType(g_LuaState, -1) == LUA_TTABLE)
    {
        const int result = g_LuaGetTop(g_LuaState);

        // --------------------------------------------------
        // Text
        // --------------------------------------------------

        g_LuaGetField(
            g_LuaState,
            result,
            "text");

        if (g_LuaType(g_LuaState, -1) == LUA_TSTRING)
        {
            const char *newText = g_LuaToLString(
                g_LuaState,
                -1,
                nullptr);

            if (newText)
                replacement.assign(newText);
        }

        g_LuaSetTop(g_LuaState, result);

        // --------------------------------------------------
        // Position
        // --------------------------------------------------

        g_LuaGetField(
            g_LuaState,
            result,
            "pos");

        if (g_LuaType(g_LuaState, -1) == LUA_TTABLE)
        {
            pos.x = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "x",
                    pos.x));

            pos.y = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "y",
                    pos.y));
        }

        g_LuaSetTop(g_LuaState, result);

        // --------------------------------------------------
        // Scale
        // --------------------------------------------------

        g_LuaGetField(
            g_LuaState,
            result,
            "scale");

        if (g_LuaType(g_LuaState, -1) == LUA_TTABLE)
        {
            scale.x = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "x",
                    scale.x));

            scale.y = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "y",
                    scale.y));
        }

        g_LuaSetTop(g_LuaState, result);

        // --------------------------------------------------
        // Color
        // --------------------------------------------------

        g_LuaGetField(
            g_LuaState,
            result,
            "color");

        if (g_LuaType(g_LuaState, -1) == LUA_TTABLE)
        {
            color->_red = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "r",
                    color->_red));

            color->_green = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "g",
                    color->_green));

            color->_blue = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "b",
                    color->_blue));

            color->_alpha = static_cast<float>(
                GetNumberField(
                    g_LuaState,
                    -1,
                    "a",
                    color->_alpha));
        }
    }

    g_LuaSetTop(g_LuaState, originalTop);

    g_InStringCallback = false;
}

// --------------------------------------------------
// LuaEngine::RegisterClasses
// --------------------------------------------------

HOOK_METHOD_PRIORITY(
    LuaEngine,
    RegisterClasses,
    101,
    ()->void)
{
    super();

    g_LuaState = *reinterpret_cast<lua_State **>(
        reinterpret_cast<unsigned char *>(this) + 0x18);

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
    (const char *str, Vector pos, Vector scale,
     KColor *color, FontSettings *settings)
        ->void)
{
    if (!str || !color || g_InStringCallback)
    {
        super(str, pos, scale, color, settings);
        return;
    }

    // Preserve the original color.
    KColor modifiedColor = *color;

    // Persistent replacement text.
    std::string replacement = str;

    ProcessDrawString(
        str,
        pos,
        scale,
        &modifiedColor,
        replacement);

    super(
        replacement.c_str(),
        pos,
        scale,
        &modifiedColor,
        settings);
}

// --------------------------------------------------
// Plugin entry point
// --------------------------------------------------

extern "C" __declspec(dllexport) int ModInit()
{
    return 0;
}
