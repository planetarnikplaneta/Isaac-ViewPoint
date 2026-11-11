
#include "Camera.h"

#include "../IsaacRepentance.h"
#include "../Core/State.h"
#include "../Core/Logger.h"

#include <algorithm>
#include <cmath>

namespace ViewPoint
{
    namespace
    {
        constexpr float PI =
            3.14159265358979323846f;

        // Isaac grid coordinates use 40 pixels per tile.
        // ViewPoint uses one world unit per tile.
        constexpr float ISAAC_PIXELS_PER_TILE = 40.0f;

        // RoomExtractor uses FLOOR_Y = -1.0f.
        constexpr float ROOM_FLOOR_Y = -1.0f;

        // Camera height above the room floor.
        constexpr float PLAYER_EYE_HEIGHT = 1.15f;

        bool KeyDown(int key)
        {
            return (GetAsyncKeyState(key) & 0x8000) != 0;
        }

        bool UpdatePlayerCamera()
        {
            if (!g_Game)
                return false;

            Entity_Player *player =
                g_Game->GetPlayer(0);

            if (!player)
                return false;

            Room *room =
                g_Game->GetCurrentRoom();

            if (!room)
                return false;

            const Vector *playerPosition =
                player->GetPosition();

            if (!playerPosition)
                return false;

            const float roomCenterX =
                320.0f + (static_cast<float>(room->_gridWidth) - 15.0f) * 20.0f;

            const float roomCenterY =
                280.0f + (static_cast<float>(room->_gridHeight) - 9.0f) * 20.0f;

            g_Camera.position.x =
                (playerPosition->x - roomCenterX) / ISAAC_PIXELS_PER_TILE;

            g_Camera.position.z =
                (roomCenterY - playerPosition->y) / ISAAC_PIXELS_PER_TILE;

            g_Camera.position.y =
                ROOM_FLOOR_Y + PLAYER_EYE_HEIGHT;

            static unsigned int debugCounter = 0;

            if (++debugCounter >= 60)
            {
                debugCounter = 0;

                LogNumber("VP Player X", playerPosition->x);
                LogNumber("VP Player Y", playerPosition->y);

                LogNumber(
                    "VP Grid Width",
                    static_cast<float>(room->_gridWidth));

                LogNumber(
                    "VP Grid Height",
                    static_cast<float>(room->_gridHeight));

                LogNumber("VP Camera X", g_Camera.position.x);
                LogNumber("VP Camera Z", g_Camera.position.z);
            }
            return true;
        }
    }

    void ReleaseCameraCursor()
    {
        ClipCursor(nullptr);
        g_CursorCaptured = false;
    }

    void UpdateCamera(HWND window)
    {
        const ULONGLONG currentTime =
            GetTickCount64();

        float deltaTime = 0.0f;

        if (g_Camera.lastUpdateTime != 0)
        {
            deltaTime =
                static_cast<float>(
                    currentTime - g_Camera.lastUpdateTime) /
                1000.0f;
        }

        g_Camera.lastUpdateTime = currentTime;

        deltaTime = (std::min)(deltaTime, 0.05f);

        // -------------------------------------------------
        // F1: Enable / disable camera
        // -------------------------------------------------

        const bool f1Down = KeyDown(VK_F1);

        if (f1Down && !g_Camera.previousF1State)
        {
            g_Camera.enabled = !g_Camera.enabled;

            if (!g_Camera.enabled)
            {
                ReleaseCameraCursor();

                ViewPoint::LogMessage(
                    "First-person camera disabled.");
            }
            else
            {
                g_CursorCaptured = false;

                ViewPoint::LogMessage(
                    "First-person camera enabled.");
            }
        }

        g_Camera.previousF1State = f1Down;

        if (!g_Camera.enabled || !window)
        {
            if (g_CursorCaptured)
                ReleaseCameraCursor();

            return;
        }

        // -------------------------------------------------
        // F2: Toggle player-follow / free-fly
        // -------------------------------------------------

        const bool f2Down = KeyDown(VK_F2);

        if (f2Down && !g_Camera.previousF2State)
        {
            g_Camera.followPlayer =
                !g_Camera.followPlayer;

            if (g_Camera.followPlayer)
            {
                g_Camera.playerYawOffset = 0.0f;

                UpdatePlayerCamera();

                ViewPoint::LogMessage(
                    "Player-follow camera enabled.");
            }
            else
            {
                ViewPoint::LogMessage(
                    "Free-fly debug camera enabled.");
            }
        }

        g_Camera.previousF2State = f2Down;

        // -------------------------------------------------
        // Synchronize with Isaac player
        // -------------------------------------------------

        if (g_Camera.followPlayer)
        {
            UpdatePlayerCamera();
        }

        // -------------------------------------------------
        // Window coordinates
        // -------------------------------------------------

        RECT clientRect{};

        if (!GetClientRect(window, &clientRect))
            return;

        const int clientWidth =
            clientRect.right - clientRect.left;

        const int clientHeight =
            clientRect.bottom - clientRect.top;

        if (clientWidth <= 0 || clientHeight <= 0)
            return;

        POINT topLeft =
            {
                clientRect.left,
                clientRect.top};

        POINT bottomRight =
            {
                clientRect.right,
                clientRect.bottom};

        if (!ClientToScreen(window, &topLeft) ||
            !ClientToScreen(window, &bottomRight))
        {
            return;
        }

        RECT screenRect =
            {
                topLeft.x,
                topLeft.y,
                bottomRight.x,
                bottomRight.y};

        const int centerX =
            (topLeft.x + bottomRight.x) / 2;

        const int centerY =
            (topLeft.y + bottomRight.y) / 2;

        // -------------------------------------------------
        // Mouse capture
        // -------------------------------------------------

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

            const float yawChange =
                static_cast<float>(mouseDeltaX) *
                g_Camera.mouseSensitivity;

            const float pitchChange =
                static_cast<float>(mouseDeltaY) *
                g_Camera.mouseSensitivity;

            if (g_Camera.followPlayer)
            {
                g_Camera.yaw -= yawChange;
            }
            else
            {
                g_Camera.yaw -= yawChange;
            }

            g_Camera.pitch -= pitchChange;

            g_Camera.pitch =
                (std::max)(-89.0f,
                           (std::min)(89.0f, g_Camera.pitch));
        }

        SetCursorPos(centerX, centerY);

        // -------------------------------------------------
        // Free-fly movement
        // -------------------------------------------------

        if (g_Camera.followPlayer)
            return;

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

        const float movementLength =
            std::sqrt(
                forwardInput * forwardInput +
                rightInput * rightInput);

        if (movementLength > 1.0f)
        {
            forwardInput /= movementLength;
            rightInput /= movementLength;
        }

        const float yawRadians =
            g_Camera.yaw * PI / 180.0f;

        const float forwardX =
            -std::sin(yawRadians);

        const float forwardZ =
            -std::cos(yawRadians);

        const float rightX =
            std::cos(yawRadians);

        const float rightZ =
            -std::sin(yawRadians);

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
