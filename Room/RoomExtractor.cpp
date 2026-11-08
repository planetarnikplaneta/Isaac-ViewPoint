#include "RoomExtractor.h"

#include "IsaacRepentance.h"
#include "../Core/Logger.h"

#include <cstdio>
#include <cstdint>

namespace ViewPoint
{
    namespace
    {
        constexpr unsigned int MAX_GRID_CELLS = 447;

        Room* g_LastRoom = nullptr;
        int g_LastRoomIndex = -1;
        int g_LastDimension = -1;

        void LogRoom(Room* room, int roomIndex, int dimension)
        {
            if (!room)
                return;

            const unsigned int width =
                static_cast<unsigned int>(room->_gridWidth);

            const unsigned int height =
                static_cast<unsigned int>(room->_gridHeight);

            char message[256];

            std::snprintf(
                message,
                sizeof(message),
                "RoomExtractor: Room changed | Index: %d | Dimension: %d | Width: %u | Height: %u",
                roomIndex,
                dimension,
                width,
                height
            );

            LogMessage(message);

            unsigned int cellCount = width * height;

            if (cellCount > MAX_GRID_CELLS)
                cellCount = MAX_GRID_CELLS;

            LogNumber("RoomExtractor: Grid cells", cellCount);

            unsigned int occupiedCells = 0;

            for (unsigned int i = 0; i < cellCount; ++i)
            {
                GridEntity* grid =
                    room->GetGridEntity(static_cast<int>(i));

                const unsigned int collision =
                    room->GetGridCollision(static_cast<int>(i));

                if (grid)
                    ++occupiedCells;

                const int entityType = grid
                    ? static_cast<int>(grid->GetType())
                    : -1;

                const unsigned int gridIndex = grid
                    ? static_cast<unsigned int>(grid->_gridIndex)
                    : 0;

                std::snprintf(
                    message,
                    sizeof(message),
                    "RoomExtractor: Cell %u | EntityType: %d | Collision: %u | GridIndex: %u",
                    i,
                    entityType,
                    collision,
                    gridIndex
                );

                LogMessage(message);
            }

            LogNumber(
                "RoomExtractor: Occupied grid cells",
                occupiedCells
            );

            LogMessage("RoomExtractor: Extraction finished.");
        }
    }

    void UpdateRoomExtractor()
    {
        if (!g_Game)
            return;

        Room* room = g_Game->GetCurrentRoom();

        if (!room)
        {
            g_LastRoom = nullptr;
            g_LastRoomIndex = -1;
            g_LastDimension = -1;
            return;
        }

        const int roomIndex = g_Game->GetCurrentRoomIdx();
        const int dimension = g_Game->GetDimension();

        if (room == g_LastRoom &&
            roomIndex == g_LastRoomIndex &&
            dimension == g_LastDimension)
        {
            return;
        }

        g_LastRoom = room;
        g_LastRoomIndex = roomIndex;
        g_LastDimension = dimension;

        LogRoom(room, roomIndex, dimension);
    }
}
