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
// CAMERA-RELATIVE PLAYER MOVEMENT
HOOK_METHOD(
    InputManager,
    GetActionValue,
    (int action, int controllerid, int unk) -> float)
{
    // Leave all non-movement inputs unchanged.
    if (action < 0 || action > 3)
    {
        return super(action, controllerid, unk);
    }

    // Only transform movement while ViewPoint follow mode is active.
    if (!ViewPoint::g_Camera.enabled ||
        !ViewPoint::g_Camera.followPlayer)
    {
        return super(action, controllerid, unk);
    }

    // Read the original directional inputs.
    // Calling super bypasses this hook.
    const float left =
        super(0, controllerid, unk);

    const float right =
        super(1, controllerid, unk);

    const float up =
        super(2, controllerid, unk);

    const float down =
        super(3, controllerid, unk);

    // Camera-relative input axes.
    const float strafe = right - left;
    const float forward = up - down;

    // Camera orientation.
    constexpr float PI = 3.14159265358979323846f;

    const float yawRadians =
        ViewPoint::g_Camera.yaw * PI / 180.0f;

    const float sinYaw = std::sin(yawRadians);
    const float cosYaw = std::cos(yawRadians);

    // Transform camera-relative movement into world directions.
    const float worldX =
        strafe * cosYaw -
        forward * sinYaw;

    const float worldZ =
        -strafe * sinYaw -
        forward * cosYaw;

    // Convert the transformed vector back into Isaac's
    // four directional actions.
    switch (action)
    {
        case 0: // LEFT
            return worldX < 0.0f ? -worldX : 0.0f;

        case 1: // RIGHT
            return worldX > 0.0f ? worldX : 0.0f;

        case 2: // UP
            return worldZ > 0.0f ? worldZ : 0.0f;

        case 3: // DOWN
            return worldZ < 0.0f ? -worldZ : 0.0f;
    }

    return 0.0f;
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
