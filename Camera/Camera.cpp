
#include "Camera.h"

#include "../Core/State.h"
#include "../Core/Logger.h"
#include "../IsaacRepentance.h"

#include <algorithm>
#include <cmath>

namespace ViewPoint
{
    namespace
    {
        constexpr float PI = 3.14159265358979323846f;

        // Isaac uses pixel-like position units.
        // One Isaac grid tile corresponds to one ViewPoint unit.
        constexpr float ISAAC_UNITS_PER_TILE = 40.0f;

        // Room floor is at -1.5. Place the camera 1.15 units above it.
        constexpr float ROOM_FLOOR_Y = -1.5f;
        constexpr float PLAYER_EYE_HEIGHT = 1.15f;

        constexpr int DIRECTION_LEFT = 0;
        constexpr int DIRECTION_UP = 1;
        constexpr int DIRECTION_RIGHT = 2;
        constexpr int DIRECTION_DOWN = 3;

        bool g_PlayerFollowMode = true;
        bool g_PreviousF2State = false;

        Room* g_CameraRoom = nullptr;

        float g_PlayerOriginX = 0.0f;
        float g_PlayerOriginY = 0.0f;

        float g_PlayerLookYaw = 0.0f;

        float DegreesToRadians(float degrees)
        {
            return degrees * PI / 180.0f;
        }

        float GetPlayerFacingYaw(int direction)
        {
            switch (direction)
            {
            case DIRECTION_UP:
                return 0.0f;

            case DIRECTION_RIGHT:
                return -90.0f;

            case DIRECTION_DOWN:
                return 180.0f;

            case DIRECTION_LEFT:
                return 90.0f;

            default:
                return 0.0f;
            }
        }

        bool KeyDown(int key)
        {
            return (GetAsyncKeyState(key) & 0x8000) != 0;
        }

        void UpdatePlayerFollowCamera()
        {
            if (!g_Game)
                return;

            Room* room = g_Game->GetCurrentRoom();

            if (!room)
                return;

            Entity_Player* player = g_Game->GetPlayer(0);

            if (!player)
                return;

            Vector* playerPosition = player->GetPosition();

            if (!playerPosition)
                return;

            // Re-anchor the camera whenever Isaac enters another room.
            // The room mesh is centered at (0, 0), so the player's
            // initial position becomes the center of the ViewPoint room.
            if (room != g_CameraRoom)
            {
                g_CameraRoom = room;

                g_PlayerOriginX = playerPosition->x;
                g_PlayerOriginY = playerPosition->y;

                g_PlayerLookYaw = 0.0f;

                g_Camera.position.x = 0.0f;
                g_Camera.position.y =
                    ROOM_FLOOR_Y + PLAYER_EYE_HEIGHT;
                g_Camera.position.z = 0.0f;

                g_Camera.yaw =
                    GetPlayerFacingYaw(player->_headDirection);

                LogMessage(
                    "Camera: Player-follow mode attached to new room.");

                LogNumber(
                    "Camera: Player origin X",
                    g_PlayerOriginX);

                LogNumber(
                    "Camera: Player origin Y",
                    g_PlayerOriginY);
            }

            // Convert Isaac's room-relative movement into ViewPoint
            // tile coordinates.
            const float deltaX =
                (playerPosition->x - g_PlayerOriginX) /
                ISAAC_UNITS_PER_TILE;

            const float deltaY =
                (playerPosition->y - g_PlayerOriginY) /
                ISAAC_UNITS_PER_TILE;

            g_Camera.position.x = deltaX;

            // Isaac's screen Y increases downwards.
            // ViewPoint's positive Z points towards the back of the room.
            g_Camera.position.z = -deltaY;

            g_Camera.position.y =
                ROOM_FLOOR_Y + PLAYER_EYE_HEIGHT;

            // Keep the player's cardinal facing direction as the base
            // yaw, with mouse movement providing the additional offset.
            g_Camera.yaw =
                GetPlayerFacingYaw(player->_headDirection) +
                g_PlayerLookYaw;
        }
    }

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
            deltaTime =
                static_cast<float>(
                    currentTime - g_Camera.lastUpdateTime) /
                1000.0f;
        }

        g_Camera.lastUpdateTime = currentTime;

        deltaTime = (std::min)(deltaTime, 0.05f);

        // ---------------------------------------------------------
        // F1: Enable or disable the ViewPoint camera.
        // ---------------------------------------------------------

        const bool f1Down = KeyDown(VK_F1);

        if (f1Down && !g_Camera.previousF1State)
        {
            g_Camera.enabled = !g_Camera.enabled;

            if (!g_Camera.enabled)
            {
                ReleaseCameraCursor();

                LogMessage("First-person camera disabled.");
            }
            else
            {
                g_CursorCaptured = false;

                LogMessage("First-person camera enabled.");
            }
        }

        g_Camera.previousF1State = f1Down;

        if (!g_Camera.enabled || !window)
        {
            if (g_CursorCaptured)
                ReleaseCameraCursor();

            return;
        }

        // ---------------------------------------------------------
        // F2: Switch between player-follow and free-fly modes.
        // ---------------------------------------------------------

        const bool f2Down = KeyDown(VK_F2);

        if (f2Down && !g_PreviousF2State)
        {
            g_PlayerFollowMode = !g_PlayerFollowMode;

            if (g_PlayerFollowMode)
            {
                // Re-anchor when returning to player-follow mode.
                g_CameraRoom = nullptr;
                g_PlayerLookYaw = 0.0f;

                LogMessage(
                    "Camera: Player-follow mode enabled.");
            }
            else
            {
                LogMessage(
                    "Camera: Free-fly debug mode enabled.");
            }
        }

        g_PreviousF2State = f2Down;

        // ---------------------------------------------------------
        // Window and cursor coordinates.
        // ---------------------------------------------------------

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
            clientRect.top
        };

        POINT bottomRight = {
            clientRect.right,
            clientRect.bottom
        };

        if (!ClientToScreen(window, &topLeft) ||
            !ClientToScreen(window, &bottomRight))
        {
            return;
        }

        RECT screenRect = {
            topLeft.x,
            topLeft.y,
            bottomRight.x,
            bottomRight.y
        };

        const int centerX =
            (topLeft.x + bottomRight.x) / 2;

        const int centerY =
            (topLeft.y + bottomRight.y) / 2;

        // ---------------------------------------------------------
        // Mouse capture.
        // ---------------------------------------------------------

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

            if (g_PlayerFollowMode)
            {
                g_PlayerLookYaw -=
                    static_cast<float>(mouseDeltaX) *
                    g_Camera.mouseSensitivity;
            }
            else
            {
                g_Camera.yaw -=
                    static_cast<float>(mouseDeltaX) *
                    g_Camera.mouseSensitivity;
            }

            g_Camera.pitch -=
                static_cast<float>(mouseDeltaY) *
                g_Camera.mouseSensitivity;

            g_Camera.pitch =
                (std::max)(
                    -89.0f,
                    (std::min)(89.0f, g_Camera.pitch));
        }

        SetCursorPos(centerX, centerY);

        // ---------------------------------------------------------
        // Player-follow mode.
        // ---------------------------------------------------------

        if (g_PlayerFollowMode)
        {
            UpdatePlayerFollowCamera();
            return;
        }

        // ---------------------------------------------------------
        // Free-fly debug mode.
        // ---------------------------------------------------------

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

        const float movementLength = std::sqrt(
            forwardInput * forwardInput +
            rightInput * rightInput);

        if (movementLength > 1.0f)
        {
            forwardInput /= movementLength;
            rightInput /= movementLength;
        }

        const float yawRadians =
            DegreesToRadians(g_Camera.yaw);

        const float forwardX = -std::sin(yawRadians);
        const float forwardZ = -std::cos(yawRadians);

        const float rightX = std::cos(yawRadians);
        const float rightZ = -std::sin(yawRadians);

        float speed = g_Camera.movementSpeed;

        if (KeyDown(VK_SHIFT))
            speed *= g_Camera.sprintMultiplier;

        const float movement = speed * deltaTime;

        g_Camera.position.x +=
            (forwardX * forwardInput +
             rightX * rightInput) * movement;

        g_Camera.position.z +=
            (forwardZ * forwardInput +
             rightZ * rightInput) * movement;

        g_Camera.position.y +=
            verticalInput * movement;
    }
}
