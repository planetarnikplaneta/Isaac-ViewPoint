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

#include "IsaacRepentance.h"
#include <cstdio>
#include <cmath>

using namespace ViewPoint;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "User32.lib")

namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}
// INPUT ACTION DIAGNOSTICS
HOOK_METHOD(
    InputManager,
    GetActionValue,
    (int action, int controllerid, int unk) -> float)
{
    const float value = super(action, controllerid, unk);

    static float lastValues[256] = {};
    static bool initialized[256] = {};

    if (action >= 0 && action < 256)
    {
        const int index = action;

        if (!initialized[index] ||
            std::fabs(value - lastValues[index]) > 0.001f)
        {
            initialized[index] = true;
            lastValues[index] = value;

            char message[128];

            std::snprintf(
                message,
                sizeof(message),
                "Input action: %d, value: %.3f, controller: %d",
                action,
                value,
                controllerid
            );

            ViewPoint::LogMessage(message);
        }
    }

    return value;
}
// REPENTOGON HOOK

HOOK_GLOBAL(
    OpenGL::wglSwapBuffers,
    (HDC hdc)->bool,
    __stdcall)
{
    if (wglGetCurrentContext())
    {
        const HWND window = WindowFromDC(hdc);

        if (!ViewPoint::g_RenderWindow)
        {
            ViewPoint::g_RenderWindow = window;
        }
        else if (ViewPoint::g_RenderWindow != window)
        {
            return super(hdc);
        }

        ViewPoint::UpdateRoomExtractor();

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
        "Default model: disabled; scene starts empty.");

    ViewPoint::LogNumber(
        "Configured scene objects",
        g_ObjectConfigs.size());

    DiagnoseEmbeddedResources();

    return 0;
}
