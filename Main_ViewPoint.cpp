#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl/GL.h>

#include "libzhl.h"
#include "HookSystem.h"

#include "Core/Logger.h"
#include "Core/State.h"
#include "Core/Config.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Room/RoomExtractor.h"

using namespace ViewPoint;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "User32.lib")

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
    ViewPoint::UpdateRoomExtractor();

    if (wglGetCurrentContext())
    {
        HWND window = WindowFromDC(hdc);

        glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);

        RenderTriangleMesh(window);

        glPopAttrib();
    }

    return super(hdc);
}

// DLL ENTRY POINT

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

// MOD INITIALIZATION

extern "C" __declspec(dllexport) int ModInit()
{
    ViewPoint::ResetLogFile();

    ViewPoint::LogMessage(
        "Isaac: ViewPoint initialized.");

    LoadConfiguration();

    ViewPoint::LogMessage(
        ("Default model: " +
         std::string(DEFAULT_OBJECT)).c_str());

    ViewPoint::LogNumber(
        "Configured scene objects",
        g_ObjectConfigs.size());

    DiagnoseEmbeddedResources();

    return 0;
}
