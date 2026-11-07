#include "Camera.h"

#include "../Core/State.h"
#include "../Core/Logger.h"

#include <algorithm>
#include <cmath>

namespace ViewPoint
{

    void ReleaseCameraCursor()
    {
        ClipCursor(nullptr);
        g_CursorCaptured = false;
    }

    void UpdateCamera(HWND window)
    {
        const ULONGLONG currentTime = GetTickCount64();

        float deltaTime = 0.0f;

        if (g_Camera.lastUpdateTime != 0)
        {
            deltaTime = static_cast<float>(
                            currentTime - g_Camera.lastUpdateTime) /
                        1000.0f;
        }

        g_Camera.lastUpdateTime = currentTime;

        // Prevent large movement after pauses or window stalls.
        deltaTime = (std::min)(deltaTime, 0.05f);

        // ----------------------------------------------
        // F1 camera toggle
        // ----------------------------------------------

        const bool f1Down =
            (GetAsyncKeyState(VK_F1) & 0x8000) != 0;

        if (f1Down && !g_Camera.previousF1State)
        {
            g_Camera.enabled = !g_Camera.enabled;

            if (!g_Camera.enabled)
            {
                ReleaseCameraCursor();
                ViewPoint::LogMessage("First-person camera disabled.");
            }
            else
            {
                g_CursorCaptured = false;
                ViewPoint::LogMessage("First-person camera enabled.");
            }
        }

        g_Camera.previousF1State = f1Down;

        if (!g_Camera.enabled || !window)
        {
            if (g_CursorCaptured)
                ReleaseCameraCursor();

            return;
        }

        // ----------------------------------------------
        // Window and cursor coordinates
        // ----------------------------------------------

        RECT clientRect{};

        if (!GetClientRect(window, &clientRect))
            return;

        const int clientWidth =
            clientRect.right - clientRect.left;

        const int clientHeight =
            clientRect.bottom - clientRect.top;

        if (clientWidth <= 0 || clientHeight <= 0)
            return;

        POINT topLeft = {
            clientRect.left,
            clientRect.top};

        POINT bottomRight = {
            clientRect.right,
            clientRect.bottom};

        if (!ClientToScreen(window, &topLeft) ||
            !ClientToScreen(window, &bottomRight))
        {
            return;
        }

        RECT screenRect = {
            topLeft.x,
            topLeft.y,
            bottomRight.x,
            bottomRight.y};

        const int centerX =
            (topLeft.x + bottomRight.x) / 2;

        const int centerY =
            (topLeft.y + bottomRight.y) / 2;

        // ----------------------------------------------
        // Mouse capture
        // ----------------------------------------------

        if (!g_CursorCaptured)
        {
            ClipCursor(&screenRect);
            SetCursorPos(centerX, centerY);

            g_CursorCaptured = true;
        }

        POINT mousePosition{};

        if (GetCursorPos(&mousePosition))
        {
            const int mouseDeltaX =
                mousePosition.x - centerX;

            const int mouseDeltaY =
                mousePosition.y - centerY;

            g_Camera.yaw -=
                static_cast<float>(mouseDeltaX) *
                g_Camera.mouseSensitivity;

            g_Camera.pitch -=
                static_cast<float>(mouseDeltaY) *
                g_Camera.mouseSensitivity;

            // Prevent the camera from flipping upside down.
            g_Camera.pitch = (std::max)(-89.0f,
                                        (std::min)(89.0f, g_Camera.pitch));
        }

        SetCursorPos(centerX, centerY);

        // ----------------------------------------------
        // Movement input
        // ----------------------------------------------

        const auto KeyDown = [](int key) -> bool
        {
            return (GetAsyncKeyState(key) & 0x8000) != 0;
        };

        float forwardInput = 0.0f;
        float rightInput = 0.0f;
        float verticalInput = 0.0f;

        if (KeyDown('W'))
            forwardInput += 1.0f;

        if (KeyDown('S'))
            forwardInput -= 1.0f;

        if (KeyDown('D'))
            rightInput += 1.0f;

        if (KeyDown('A'))
            rightInput -= 1.0f;

        if (KeyDown(VK_SPACE))
            verticalInput += 1.0f;

        if (KeyDown(VK_CONTROL))
            verticalInput -= 1.0f;

        // Normalize horizontal movement so diagonal movement
        // is not faster than straight movement.
        const float movementLength = std::sqrt(
            forwardInput * forwardInput +
            rightInput * rightInput);

        if (movementLength > 1.0f)
        {
            forwardInput /= movementLength;
            rightInput /= movementLength;
        }

        // ----------------------------------------------
        // Calculate camera direction
        // ----------------------------------------------

        const float yawRadians =
            g_Camera.yaw *
            3.14159265358979323846f / 180.0f;

        const float forwardX = -std::sin(yawRadians);
        const float forwardZ = -std::cos(yawRadians);

        const float rightX = std::cos(yawRadians);
        const float rightZ = -std::sin(yawRadians);

        // ----------------------------------------------
        // Movement speed
        // ----------------------------------------------

        float speed = g_Camera.movementSpeed;

        if (KeyDown(VK_SHIFT))
        {
            speed *= g_Camera.sprintMultiplier;
        }

        const float movement =
            speed * deltaTime;

        g_Camera.position.x +=
            (forwardX * forwardInput +
             rightX * rightInput) *
            movement;

        g_Camera.position.z +=
            (forwardZ * forwardInput +
             rightZ * rightInput) *
            movement;

        g_Camera.position.y +=
            verticalInput * movement;
    }
}
