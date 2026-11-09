
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
        constexpr float ISAAC_PIXELS_PER_TILE = 40.0f;

        // RoomExtractor uses FLOOR_Y = -1.5f.
        // Place the camera 1.15 units above the floor.
        constexpr float CAMERA_EYE_HEIGHT = -0.35f;

        bool g_FreeFlyMode = false;

        Entity_Player* g_LastPlayer = nullptr;
        int g_LastHeadDirection = -1;

        float DirectionToYaw(int direction)
        {
            switch (direction)
            {
            case LEFT:
                return 90.0f;

            case UP:
                return 0.0f;

            case RIGHT:
                return -90.0f;

            case DOWN:
                return 180.0f;

            default:
                return 0.0f;
            }
        }

        bool KeyDown(int key)
        {
            return (GetAsyncKeyState(key) & 0x8000) != 0;
        }

        void UpdatePlayerCamera()
        {
            if (!g_Game)
                return;

            Entity_Player* player = g_Game->GetPlayer(0);

            if (!player)
            {
                g_LastPlayer = nullptr;
                g_LastHeadDirection = -1;
                return;
            }

            Room* room = g_Game->GetCurrentRoom();

            if (!room)
                return;

            const Vector* playerPosition = player->GetPosition();

            if (!playerPosition)
                return;

            const unsigned int roomWidth = room->_gridWidth;
            const unsigned int roomHeight = room->_gridHeight;

            if (roomWidth <= 2 || roomHeight <= 2)
                return;

            // Isaac coordinates are pixels.
            // ViewPoint coordinates are centered room tiles.
            g_Camera.position.x =
                playerPosition->x / ISAAC_PIXELS_PER_TILE -
                static_cast<float>(roomWidth) * 0.5f;

            g_Camera.position.z =
                static_cast<float>(roomHeight) * 0.5f -
                playerPosition->y / ISAAC_PIXELS_PER_TILE;

            g_Camera.position.y = CAMERA_EYE_HEIGHT;

            const int headDirection = player->_headDirection;

            // Initialize facing when the player changes.
            if (player != g_LastPlayer)
            {
                g_LastPlayer = player;
                g_LastHeadDirection = headDirection;

                if (headDirection != NO_DIRECTION)
                    g_Camera.yaw = DirectionToYaw(headDirection);

                g_Camera.pitch = 0.0f;
            }
            // Update facing when Isaac changes cardinal direction.
            else if (headDirection != g_LastHeadDirection)
            {
                g_LastHeadDirection = headDirection;

                if (headDirection != NO_DIRECTION)
                    g_Camera.yaw = DirectionToYaw(headDirection);
            }
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

        // --------------------------------------------------
        // F1: Enable or disable ViewPoint camera.
        // --------------------------------------------------

        const bool f1Down = KeyDown(VK_F1);

        if (f1Down && !g_Camera.previousF1State)
        {
            g_Camera.enabled = !g_Camera.enabled;

            if (!g_Camera.enabled)
            {
                ReleaseCameraCursor();

                g_LastPlayer = nullptr;
                g_LastHeadDirection = -1;

                LogMessage("First-person camera disabled.");
            }
            else
            {
                g_CursorCaptured = false;

                g_LastPlayer = nullptr;
                g_LastHeadDirection = -1;

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

        // --------------------------------------------------
        // F2: Toggle player-follow / free-fly mode.
        // --------------------------------------------------

        static bool previousF2State = false;

        const bool f2Down = KeyDown(VK_F2);

        if (f2Down && !previousF2State)
        {
            g_FreeFlyMode = !g_FreeFlyMode;

            if (g_FreeFlyMode)
            {
                LogMessage(
                    "Camera mode: Free-fly debugging.");
            }
            else
            {
                g_LastPlayer = nullptr;
                g_LastHeadDirection = -1;

                LogMessage(
                    "Camera mode: Player follow.");
            }
        }

        previousF2State = f2Down;

        // --------------------------------------------------
        // Player position and facing.
        // --------------------------------------------------

        if (!g_FreeFlyMode)
            UpdatePlayerCamera();

        // --------------------------------------------------
        // Window coordinates.
        // --------------------------------------------------

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
            clientRect.top
        };

        POINT bottomRight =
        {
            clientRect.right,
            clientRect.bottom
        };

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
            bottomRight.y
        };

        const int centerX =
            (topLeft.x + bottomRight.x) / 2;

        const int centerY =
            (topLeft.y + bottomRight.y) / 2;

        // --------------------------------------------------
        // Mouse capture.
        // --------------------------------------------------

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

            g_Camera.pitch =
                (std::max)(
                    -89.0f,
                    (std::min)(89.0f, g_Camera.pitch));
        }

        SetCursorPos(centerX, centerY);

        // --------------------------------------------------
        // Free-fly movement.
        // Only active in debugging mode.
        // --------------------------------------------------

        if (!g_FreeFlyMode)
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
            g_Camera.yaw *
            3.14159265358979323846f /
            180.0f;

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
