
#include <Windows.h>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <string>
#include <algorithm>

struct lua_State;
typedef int (__cdecl *lua_CFunction)(lua_State*);

#include "libzhl.h"
#include "HookSystem.h"

// ------------------------------------------------------------
// REPENTOGON Lua userdata API
// ------------------------------------------------------------

namespace lua
{
    enum class Metatables
    {
        FONT = 26,
        KCOLOR = 55
    };

    LIBZHL_API void* GetMetatableKey(Metatables metatable);

    LIBZHL_API void* CheckUserdata(
        lua_State* L,
        int index,
        Metatables metatable,
        std::string const& name
    );

    namespace luabridge
    {
        class LIBZHL_API UserdataPtr
        {
        public:
            static void push(
                lua_State* L,
                void* pointer,
                void const* key
            );
        };
    }
}

// ------------------------------------------------------------
// Lua API
// ------------------------------------------------------------

static constexpr int LUA_TNIL = 0;
static constexpr int LUA_TBOOLEAN = 1;
static constexpr int LUA_TNUMBER = 3;
static constexpr int LUA_TSTRING = 4;
static constexpr int LUA_TTABLE = 5;
static constexpr int LUA_TFUNCTION = 6;
static constexpr int LUA_TUSERDATA = 7;

using LuaCreateTable = void (__cdecl*)(lua_State*, int, int);
using LuaPushString = const char* (__cdecl*)(lua_State*, const char*);
using LuaPushInteger = void (__cdecl*)(lua_State*, long long);
using LuaPushNumber = void (__cdecl*)(lua_State*, double);
using LuaPushBoolean = void (__cdecl*)(lua_State*, int);
using LuaPushNil = void (__cdecl*)(lua_State*);
using LuaPushValue = void (__cdecl*)(lua_State*, int);
using LuaSetGlobal = void (__cdecl*)(lua_State*, const char*);
using LuaSetField = void (__cdecl*)(lua_State*, int, const char*);
using LuaGetGlobal = int (__cdecl*)(lua_State*, const char*);
using LuaGetField = int (__cdecl*)(lua_State*, int, const char*);
using LuaRotate = void (__cdecl*)(lua_State*, int, int);
using LuaType = int (__cdecl*)(lua_State*, int);
using LuaToString = const char* (__cdecl*)(lua_State*, int, size_t*);
using LuaToNumber = double (__cdecl*)(lua_State*, int, int*);
using LuaToBoolean = int (__cdecl*)(lua_State*, int);
using LuaGetTop = int (__cdecl*)(lua_State*);
using LuaSetTop = void (__cdecl*)(lua_State*, int);
using LuaPCallK = int (__cdecl*)(
    lua_State*, int, int, int, long long, lua_CFunction
);

static LuaCreateTable lua_createtable = nullptr;
static LuaPushString lua_pushstring = nullptr;
static LuaPushInteger lua_pushinteger = nullptr;
static LuaPushNumber lua_pushnumber = nullptr;
static LuaPushBoolean lua_pushboolean = nullptr;
static LuaPushNil lua_pushnil = nullptr;
static LuaPushValue lua_pushvalue = nullptr;
static LuaSetGlobal lua_setglobal = nullptr;
static LuaSetField lua_setfield = nullptr;
static LuaGetGlobal lua_getglobal = nullptr;
static LuaGetField lua_getfield = nullptr;
static LuaRotate lua_rotate = nullptr;
static LuaType lua_type = nullptr;
static LuaToString lua_tolstring = nullptr;
static LuaToNumber lua_tonumberx = nullptr;
static LuaToBoolean lua_toboolean = nullptr;
static LuaGetTop lua_gettop = nullptr;
static LuaSetTop lua_settop = nullptr;
static LuaPCallK lua_pcallk = nullptr;

static lua_State* g_LuaState = nullptr;

static constexpr int PLANET_PL_PRE_DRAW_STRING = 1496;

static bool g_LuaApiReady = false;
static thread_local bool g_InDrawString = false;

// ------------------------------------------------------------
// Isaac structures
// ------------------------------------------------------------

struct Vector
{
    float X;
    float Y;
};

struct KColor
{
    float Red;
    float Green;
    float Blue;
    float Alpha;
    int Unknown;
};

struct FontSettings
{
    int Align;
    int16_t MaxChars;
    uint16_t MaxLineWidth;
    int WrapMode;
    float LineHeightModifier;
    int MissingCharOverride;
    int Unknown1;
    int Unknown2;
};

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

// ------------------------------------------------------------
// Logging
// ------------------------------------------------------------

static void Log(const char* message)
{
    FILE* file = nullptr;

    fopen_s(&file, "C:\\MyNativeMod.log", "a");

    if (file)
    {
        fprintf(file, "%s\n", message);
        fclose(file);
    }

    OutputDebugStringA(message);
    OutputDebugStringA("\n");
}

static void LogLuaError(lua_State* L, const char* prefix)
{
    const char* error = lua_tolstring(L, -1, nullptr);

    char buffer[2048];

    sprintf_s(
        buffer,
        "%s: %s",
        prefix,
        error ? error : "Unknown Lua error"
    );

    Log(buffer);
}

// ------------------------------------------------------------
// Lua API initialization
// ------------------------------------------------------------

static bool InitializeLuaApi()
{
    HMODULE module = GetModuleHandleA("Lua5.3.3r.dll");

    if (!module)
        return false;

#define LOAD_LUA_FUNCTION(name) \
    name = reinterpret_cast<decltype(name)>(GetProcAddress(module, #name)); \
    if (!name) return false;

    LOAD_LUA_FUNCTION(lua_createtable)
    LOAD_LUA_FUNCTION(lua_pushstring)
    LOAD_LUA_FUNCTION(lua_pushinteger)
    LOAD_LUA_FUNCTION(lua_pushnumber)
    LOAD_LUA_FUNCTION(lua_pushboolean)
    LOAD_LUA_FUNCTION(lua_pushnil)
    LOAD_LUA_FUNCTION(lua_pushvalue)
    LOAD_LUA_FUNCTION(lua_setglobal)
    LOAD_LUA_FUNCTION(lua_setfield)
    LOAD_LUA_FUNCTION(lua_getglobal)
    LOAD_LUA_FUNCTION(lua_getfield)
    LOAD_LUA_FUNCTION(lua_rotate)
    LOAD_LUA_FUNCTION(lua_type)
    LOAD_LUA_FUNCTION(lua_tolstring)
    LOAD_LUA_FUNCTION(lua_tonumberx)
    LOAD_LUA_FUNCTION(lua_toboolean)
    LOAD_LUA_FUNCTION(lua_gettop)
    LOAD_LUA_FUNCTION(lua_settop)
    LOAD_LUA_FUNCTION(lua_pcallk)

#undef LOAD_LUA_FUNCTION

    g_LuaApiReady = true;
    return true;
}

// ------------------------------------------------------------
// Planet Lua global
// ------------------------------------------------------------

static int Lua_Planet_Test(lua_State* L)
{
    lua_pushstring(L, "Native plugin is working!");
    return 1;
}

static void RegisterPlanetTable(lua_State* L)
{
    lua_createtable(L, 0, 2);

    lua_pushstring(L, "PL_PRE_DRAW_STRING");
    lua_pushinteger(L, PLANET_PL_PRE_DRAW_STRING);
    lua_setfield(L, -2, "PL_PRE_DRAW_STRING");

    lua_pushstring(L, "Test");
    // Register Test as a C function.
    // The function is pushed using lua_pushcclosure below.
    lua_settop(L, lua_gettop(L) - 1);

    // Use the Lua C API directly to create the function closure.
    // lua_pushcclosure is resolved separately.
    HMODULE module = GetModuleHandleA("Lua5.3.3r.dll");

    using LuaPushCClosure = void (__cdecl*)(lua_State*, lua_CFunction, int);

    auto pushCClosure = reinterpret_cast<LuaPushCClosure>(
        GetProcAddress(module, "lua_pushcclosure")
    );

    if (pushCClosure)
    {
        lua_pushstring(L, "Test");
        pushCClosure(L, Lua_Planet_Test, 0);
        lua_setfield(L, -2, "Test");
    }

    lua_setglobal(L, "Planet");
}

// ------------------------------------------------------------
// Lua userdata helpers
// ------------------------------------------------------------

static void PushFont(lua_State* L, Font* font)
{
    lua::luabridge::UserdataPtr::push(
        L,
        font,
        lua::GetMetatableKey(lua::Metatables::FONT)
    );
}

static void PushColor(lua_State* L, KColor* color)
{
    lua::luabridge::UserdataPtr::push(
        L,
        color,
        lua::GetMetatableKey(lua::Metatables::KCOLOR)
    );
}

static Font* ReadFont(lua_State* L, int index)
{
    if (lua_type(L, index) != LUA_TUSERDATA)
        return nullptr;

    void* userdata = lua::CheckUserdata(
        L,
        index,
        lua::Metatables::FONT,
        "Font"
    );

    if (!userdata)
        return nullptr;

    // Userdata's native pointer is stored at offset 4.
    return *reinterpret_cast<Font**>(
        reinterpret_cast<unsigned char*>(userdata) + 4
    );
}

static KColor* ReadColor(lua_State* L, int index)
{
    if (lua_type(L, index) != LUA_TUSERDATA)
        return nullptr;

    void* userdata = lua::CheckUserdata(
        L,
        index,
        lua::Metatables::KCOLOR,
        "KColor"
    );

    if (!userdata)
        return nullptr;

    return *reinterpret_cast<KColor**>(
        reinterpret_cast<unsigned char*>(userdata) + 4
    );
}

// ------------------------------------------------------------
// Callback values
// ------------------------------------------------------------

struct DrawStringValues
{
    std::string Text;
    Font* FontObject = nullptr;

    float X = 0.0f;
    float Y = 0.0f;

    KColor Color{};

    int BoxWidth = 0;
    bool Center = false;
};

// ------------------------------------------------------------
// Run registered callbacks
// ------------------------------------------------------------

static void RunPreDrawStringCallbacks(
    lua_State* L,
    DrawStringValues& values
)
{
    if (!L || !g_LuaApiReady)
        return;

    const int originalTop = lua_gettop(L);

    // Isaac.GetCallbackIterator(1496)
    lua_getglobal(L, "Isaac");

    if (lua_type(L, -1) != LUA_TTABLE)
    {
        lua_settop(L, originalTop);
        return;
    }

    lua_getfield(L, -1, "GetCallbackIterator");

    if (lua_type(L, -1) != LUA_TFUNCTION)
    {
        lua_settop(L, originalTop);
        return;
    }

    lua_pushinteger(L, PLANET_PL_PRE_DRAW_STRING);

    if (lua_pcallk(L, 1, 1, 0, 0, nullptr) != 0)
    {
        LogLuaError(L, "GetCallbackIterator failed");
        lua_settop(L, originalTop);
        return;
    }

    if (lua_type(L, -1) != LUA_TFUNCTION)
    {
        lua_settop(L, originalTop);
        return;
    }

    // Stack:
    // [Isaac, iterator]
    const int iteratorIndex = lua_gettop(L);

    while (true)
    {
        // Call iterator().
        lua_pushvalue(L, iteratorIndex);

        if (lua_pcallk(L, 0, 1, 0, 0, nullptr) != 0)
        {
            LogLuaError(L, "Callback iterator failed");
            break;
        }

        // nil means there are no more callbacks.
        if (lua_type(L, -1) == LUA_TNIL)
            break;

        // Callback record.
        const int recordIndex = lua_gettop(L);

        if (lua_type(L, recordIndex) != LUA_TTABLE)
        {
            lua_settop(L, iteratorIndex);
            continue;
        }

        lua_getfield(L, recordIndex, "Mod");
        lua_getfield(L, recordIndex, "Function");

        // Stack:
        // [Isaac, iterator, record, Mod, Function]
        if (lua_type(L, -1) != LUA_TFUNCTION)
        {
            lua_settop(L, iteratorIndex);
            continue;
        }

        // Move Function before Mod.
        lua_rotate(L, -2, 1);

        // Stack:
        // [Isaac, iterator, record, Function, Mod]

        lua_pushstring(L, values.Text.c_str());
        PushFont(L, values.FontObject);

        lua_pushnumber(L, values.X);
        lua_pushnumber(L, values.Y);

        PushColor(L, &values.Color);

        lua_pushnumber(L, values.BoxWidth);
        lua_pushboolean(L, values.Center ? 1 : 0);

        // Arguments:
        // Mod, Text, Font, X, Y, Color, BoxWidth, Center
        //
        // Results:
        // Text, Font, X, Y, Color, BoxWidth, Center

        if (lua_pcallk(L, 8, 7, 0, 0, nullptr) != 0)
        {
            LogLuaError(L, "PL_PRE_DRAW_STRING callback failed");
            lua_settop(L, iteratorIndex);
            continue;
        }

        // Results begin at iteratorIndex + 2.
        const int result = iteratorIndex + 2;

        // Text
        if (lua_type(L, result) == LUA_TSTRING)
        {
            const char* text = lua_tolstring(L, result, nullptr);

            if (text)
                values.Text = text;
        }

        // Font
        if (lua_type(L, result + 1) == LUA_TUSERDATA)
        {
            Font* font = ReadFont(L, result + 1);

            if (font)
                values.FontObject = font;
        }

        // X
        if (lua_type(L, result + 2) == LUA_TNUMBER)
        {
            values.X = static_cast<float>(
                lua_tonumberx(L, result + 2, nullptr)
            );
        }

        // Y
        if (lua_type(L, result + 3) == LUA_TNUMBER)
        {
            values.Y = static_cast<float>(
                lua_tonumberx(L, result + 3, nullptr)
            );
        }

        // RenderColor
        if (lua_type(L, result + 4) == LUA_TUSERDATA)
        {
            KColor* color = ReadColor(L, result + 4);

            if (color)
                values.Color = *color;
        }

        // BoxWidth
        if (lua_type(L, result + 5) == LUA_TNUMBER)
        {
            double width = lua_tonumberx(L, result + 5, nullptr);

            width = std::clamp(width, 0.0, 65535.0);

            values.BoxWidth = static_cast<int>(width);
        }

        // Center
        if (lua_type(L, result + 6) == LUA_TBOOLEAN)
        {
            values.Center = lua_toboolean(L, result + 6) != 0;
        }

        // Remove record and results, preserve iterator.
        lua_settop(L, iteratorIndex);
    }

    lua_settop(L, originalTop);
}

// ------------------------------------------------------------
// LuaEngine hook
// ------------------------------------------------------------

HOOK_METHOD_PRIORITY(
    LuaEngine,
    RegisterClasses,
    101,
    () -> void
)
{
    super();

    lua_State* L = *reinterpret_cast<lua_State**>(
        reinterpret_cast<unsigned char*>(this) + 0x18
    );

    if (!L)
        return;

    if (!InitializeLuaApi())
    {
        Log("Failed to initialize Lua API");
        return;
    }

    g_LuaState = L;

    RegisterPlanetTable(L);

    Log("Planet native Lua API registered");
}

// ------------------------------------------------------------
// Font::DrawString hook
// ------------------------------------------------------------

HOOK_METHOD_PRIORITY(
    Font,
    DrawString,
    100,
    (const char* str, Vector pos, Vector scale,
     KColor* color, FontSettings* settings) -> void
)
{
    // Prevent recursive callback execution.
    // This also allows drawing through a different Font object.
    if (g_InDrawString)
    {
        super(str, pos, scale, color, settings);
        return;
    }

    if (!str || !color || !settings || !g_LuaState || !g_LuaApiReady)
    {
        super(str, pos, scale, color, settings);
        return;
    }

    g_InDrawString = true;

    DrawStringValues values;

    values.Text = str;
    values.FontObject = this;

    values.X = pos.X;
    values.Y = pos.Y;

    values.Color = *color;

    values.BoxWidth = settings->MaxLineWidth;
    values.Center = settings->Align == 1;

    RunPreDrawStringCallbacks(g_LuaState, values);

    pos.X = values.X;
    pos.Y = values.Y;

    *color = values.Color;

    settings->MaxLineWidth = static_cast<uint16_t>(
        std::clamp(values.BoxWidth, 0, 65535)
    );

    // TOP_LEFT = 0, TOP_CENTER = 1.
    settings->Align = values.Center ? 1 : 0;

    const char* finalText = values.Text.c_str();

    // If Lua returned a different Font object, dispatch through it.
    // The recursive hook sees g_InDrawString and calls the original
    // function directly, using the replacement Font as "this".
    if (values.FontObject && values.FontObject != this)
    {
        values.FontObject->DrawString(
            finalText,
            pos,
            scale,
            color,
            settings
        );
    }
    else
    {
        super(finalText, pos, scale, color, settings);
    }

    g_InDrawString = false;
}

// ------------------------------------------------------------
// REPENTOGON native plugin entry point
// ------------------------------------------------------------

extern "C" __declspec(dllexport) int ModInit()
{
    Log("Planet native plugin loaded");
    return 0;
}
