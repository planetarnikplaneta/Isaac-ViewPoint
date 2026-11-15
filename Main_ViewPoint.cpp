
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl/GL.h>

#include "libzhl.h"
#include "HookSystem.h"
#include "ASMPatcher.hpp"
#include "SigScan.h"

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
               (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0) ||
                ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0));
    }

    Vector GetCameraShootVector()
    {
        const float yawRadians =
            g_Camera.yaw * VIEWPOINT_PI / 180.0f;

        const float direction =
            (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0
                ? -1.0f
                : 1.0f;

        const float shootX = std::sin(yawRadians) * direction;
        const float shootY = std::cos(yawRadians) * direction;

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
    if (ViewPoint::IsMouseAiming() && g_Game)
    {
        Entity_Player* player = g_Game->GetPlayer(0);

        if (player && GetOwner() == player)
        {
            const Vector cameraAim = ViewPoint::GetCameraShootVector();
            super(cameraAim, isShooting, isInterpolated);
            return;
        }
    }

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
// ROOM RENDER CALLBACK PATCH
// ------------------------------------------------------------

namespace
{
    void __stdcall RenderSceneAfterRoomRender()
    {
        if (!wglGetCurrentContext())
            return;

        // The hook fires during the game's normal render passes before the
        // feature is enabled and before a valid room is always available.
        // Avoid doing any ViewPoint work in those startup states so the
        // injected render path cannot dereference invalid game state.
        if (!ViewPoint::g_Camera.enabled || !g_Game || g_ObjectConfigs.empty())
            return;

        HWND window = ViewPoint::g_RenderWindow;

        if (!window)
        {
            HDC currentDC = wglGetCurrentDC();
            window = currentDC ? WindowFromDC(currentDC) : nullptr;
        }

        if (!window)
            return;

        ViewPoint::g_RenderWindow = window;
        ViewPoint::UpdateRoomExtractor();

        if (!g_Game || !g_Game->GetCurrentRoom())
            return;

        glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);

        ViewPoint::RenderTriangleMesh(window);

        glPopAttrib();
    }

    void PatchRoomRenderEntitiesCallback()
    {
        SigScan scanner("33f68d87????????39b0????????76??8bbd????????6690");
        if (!scanner.Scan())
        {
            ViewPoint::LogMessage("ViewPoint: Room render signature not found.");
            return;
        }

        void* addr = scanner.GetAddress();
        if (!addr)
            return;

        ASMPatch::SavedRegisters savedRegisters(
            ASMPatch::SavedRegisters::Registers::GP_REGISTERS_STACKLESS,
            true);

        ASMPatch patch;
        patch.PreserveRegisters(savedRegisters)
            .AddInternalCall(RenderSceneAfterRoomRender)
            .RestoreRegisters(savedRegisters)
            .AddBytes(ByteBuffer().AddAny((char*)addr, 0x8))
            .AddRelativeJump((char*)addr + 0x8);

        ASMPatcher::instance().PatchAt(addr, &patch);
    }
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

    if (!g_ObjectConfigs.empty())
    {
        PatchRoomRenderEntitiesCallback();
    }
    else
    {
        ViewPoint::LogMessage(
            "No configured objects; skipping room render patch until a scene is configured.");
    }

    return 0;
}
