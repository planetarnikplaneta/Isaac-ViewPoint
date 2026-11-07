#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl/GL.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cstddef>

#include "libzhl.h"
#include "HookSystem.h"

#include "Core/Logger.h"
#include "Core/Types.h"
#include "Core/State.h"
#include "Core/AssetPaths.h"
#include "Core/Config.h"
#include "Resources/ResourceManager.h"
#include "Models/OBJLoader.h"
#include "Models/Texture.h"
#include "Models/GpuMesh.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include "Graphics/Renderer.h"

using namespace ViewPoint;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "User32.lib")

#ifndef GL_CURRENT_PROGRAM
#define GL_CURRENT_PROGRAM 0x8B8D
#endif

#ifndef GL_ACTIVE_TEXTURE
#define GL_ACTIVE_TEXTURE 0x84E0
#endif

#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif
#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif

#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif

#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif

#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif

#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH 0x8B84
#endif

#ifndef GL_FLOAT
#define GL_FLOAT 0x1406
#endif

#ifndef GL_TRIANGLES
#define GL_TRIANGLES 0x0004
#endif

namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}

// REPENTOGON HOOK

HOOK_GLOBAL(
    OpenGL::wglSwapBuffers,
    (HDC hdc)->bool,
    __stdcall)
{
    if (wglGetCurrentContext())
    {
        HWND window = WindowFromDC(hdc);

        RenderTriangleMesh(window);
    }

    return super(hdc);
}

// DLL ENTRY POIN

BOOL WINAPI DllMain(
    HINSTANCE instance,
    DWORD reason,
    LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        g_Module = instance;

        DisableThreadLibraryCalls(instance);
    }

    return TRUE;
}

// MOD INITIALIZATIO

extern "C" __declspec(dllexport) int ModInit()
{
    // Reset the log before writing initialization data.
    ViewPoint::ResetLogFile();

    ViewPoint::LogMessage(
        "Isaac: ViewPoint initialized.");

    LoadConfiguration();

    ViewPoint::LogMessage(
        ("Default model: " +
         std::string(DEFAULT_OBJECT))
            .c_str());

    ViewPoint::LogNumber(
        "Configured scene objects",
        g_ObjectConfigs.size());

    DiagnoseEmbeddedResources();

    return 0;
}
