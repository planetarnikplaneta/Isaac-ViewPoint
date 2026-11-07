#include "RoomExtractor.h"

#include "../IsaacRepentance.h"
#include "../Core/Logger.h"

#include <cstdio>
#include <cstdint>

namespace ViewPoint
{
    namespace
    {
        constexpr unsigned int MAX_GRID_ENTITIES = 447;

        Room* g_LastRoom = nullptr;
        int g_LastRoomIndex = -1;
        int g_LastDimension = -1;

        void LogRoom(Room* room, int roomIndex, int dimension)
        {
            if (!room)
                return;

            const unsigned int width = room->_gridWidth;
            const unsigned int height = room->_gridHeight;

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

            if (cellCount > MAX_GRID_ENTITIES)
                cellCount = MAX_GRID_ENTITIES;

            LogNumber("RoomExtractor: Grid cells", cellCount);

            unsigned int occupiedCells = 0;

            for (unsigned int i = 0; i < cellCount; ++i)
            {
                GridEntity* grid = room->GetGridEntity(i);

                if (!grid)
                    continue;

                ++occupiedCells;

                std::snprintf(
                    message,
                    sizeof(message),
                    "RoomExtractor: Grid entity | Cell: %u | Type: %d | GridIndex: %u",
                    i,
                    grid->GetType(),
                    grid->_gridIndex
                );

                LogMessage(message);
            }

            LogNumber("RoomExtractor: Occupied grid cells", occupiedCells);
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
