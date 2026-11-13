
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
#include <algorithm>

using namespace ViewPoint;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "User32.lib")

namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}

// ------------------------------------------------------------
// INPUT HELPERS
// ------------------------------------------------------------

namespace ViewPoint
{
    constexpr float VIEWPOINT_PI = 3.14159265358979323846f;

    bool IsMouseAiming()
    {
        return g_Camera.enabled &&
               g_Camera.followPlayer &&
               (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    }

    Vector GetCameraShootVector()
    {
        const float yawRadians =
            g_Camera.yaw * VIEWPOINT_PI / 180.0f;

        // Isaac's 2D aim uses a screen-space Y that increases downward, so the
        // camera-forward vector must be inverted on the vertical axis. This keeps
        // the camera movement/yaw code unchanged while fixing the tear direction.
        const float shootX = -std::sin(yawRadians);
        const float shootY = -std::cos(yawRadians);

        return Vector(shootX, shootY);
    }

    float GetMouseAimActionValue(int action)
    {
        const Vector cameraShoot = GetCameraShootVector();

        float value = 0.0f;

        switch (action)
        {
            // Shoot left
            case 4:
                value = -cameraShoot.x;
                break;

            // Shoot right
            case 5:
                value = cameraShoot.x;
                break;

            // Shoot up
            case 6:
                value = -cameraShoot.y;
                break;

            // Shoot down
            case 7:
                value = cameraShoot.y;
                break;

            default:
                return 0.0f;
        }

        return std::clamp(value, 0.0f, 1.0f);
    }
}
// ------------------------------------------------------
// VANILLA WEAPON FIRE - CAMERA AIM
// ------------------------------------------------------

HOOK_METHOD(
    Weapon,
    Fire,
    (const Vector& dir, bool isShooting, bool isInterpolated)->void)
{
    super(dir, isShooting, isInterpolated);
}
// ------------------------------------------------------------
// GET ACTION VALUE
// ------------------------------------------------------------

HOOK_METHOD(
    InputManager,
    GetActionValue,
    (int action, int controllerid, int unk)->float)
{
    constexpr float PI = 3.14159265358979323846f;

    if (!ViewPoint::g_Camera.enabled)
        return super(action, controllerid, unk);

    // Camera-aimed mouse shooting
    if (action >= 4 && action <= 7 &&
        ViewPoint::IsMouseAiming())
    {
        return ViewPoint::GetMouseAimActionValue(action);
    }

    // Camera-relative player movement
    if (action < 0 || action > 3)
        return super(action, controllerid, unk);

    if (!ViewPoint::g_Camera.followPlayer)
        return super(action, controllerid, unk);

    const float left =
        super(0, controllerid, unk);

    const float right =
        super(1, controllerid, unk);

    const float up =
        super(2, controllerid, unk);

    const float down =
        super(3, controllerid, unk);

    const float strafe = right - left;
    const float forward = up - down;

    const float yaw =
        ViewPoint::g_Camera.yaw * PI / 180.0f;

    const float sinYaw = std::sin(yaw);
    const float cosYaw = std::cos(yaw);

    const float worldX =
        -(strafe * cosYaw - forward * sinYaw);

    const float worldZ =
        -(strafe * sinYaw + forward * cosYaw);

    switch (action)
    {
        case 0:
            return worldX < 0.0f ? -worldX : 0.0f;

        case 1:
            return worldX > 0.0f ? worldX : 0.0f;

        case 2:
            return worldZ > 0.0f ? worldZ : 0.0f;

        case 3:
            return worldZ < 0.0f ? -worldZ : 0.0f;
    }

    return 0.0f;
}

// ------------------------------------------------------------
// IS ACTION PRESSED
// ------------------------------------------------------------

HOOK_METHOD(
    InputManager,
    IsActionPressed,
    (int btn, int controllerid, int unk)->bool)
{
    if (btn >= 4 && btn <= 7 &&
        ViewPoint::IsMouseAiming())
    {
        return ViewPoint::GetMouseAimActionValue(btn) > 0.25f;
    }

    if (btn >= 0 && btn <= 3 &&
        ViewPoint::g_Camera.enabled &&
        ViewPoint::g_Camera.followPlayer)
    {
        return GetActionValue(btn, controllerid, unk) > 0.25f;
    }

    return super(btn, controllerid, unk);
}

// ------------------------------------------------------------
// IS ACTION TRIGGERED
// ------------------------------------------------------------

HOOK_METHOD(
    InputManager,
    IsActionTriggered,
    (int btnaction, int controllerid, int unk)->bool)
{
    if (btnaction >= 4 && btnaction <= 7 &&
        ViewPoint::IsMouseAiming())
    {
        return ViewPoint::GetMouseAimActionValue(btnaction) > 0.25f;
    }

    return super(btnaction, controllerid, unk);
}

// ------------------------------------------------------------
// REPENTOGON OPENGL HOOK
// ------------------------------------------------------------

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

// ------------------------------------------------------------
// DLL ENTRY POINT
// ------------------------------------------------------------

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

// ------------------------------------------------------------
// MOD INITIALIZATION
// ------------------------------------------------------------

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
