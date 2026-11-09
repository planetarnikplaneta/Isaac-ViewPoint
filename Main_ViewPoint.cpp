#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl/GL.h>
#include <cmath>

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
// INPUT ACTION DIAGNOSTICS

HOOK_METHOD(
    InputManager,
    GetActionValue,
    (int action, int controllerid, int unk)->float)
{
    const float value = super(action, controllerid, unk);

    static int lastValues[16][512] = {};

    if (action >= 0 && action < 512 &&
        controllerid >= 0 && controllerid < 16)
    {
        const int scaledValue =
            static_cast<int>(std::lround(value * 1000.0f));

        int &lastValue = lastValues[controllerid][action];

        if (scaledValue != lastValue)
        {
            if (scaledValue != 0 || lastValue != 0)
            {
                ViewPoint::LogNumber(
                    "Input action ID",
                    static_cast<unsigned long long>(action));

                ViewPoint::LogNumber(
                    "Input controller ID",
                    static_cast<unsigned long long>(controllerid));

                ViewPoint::LogNumber(
                    "Input value x1000",
                    static_cast<unsigned long long>(scaledValue));
            }

            lastValue = scaledValue;
        }
    }

    return value;
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
