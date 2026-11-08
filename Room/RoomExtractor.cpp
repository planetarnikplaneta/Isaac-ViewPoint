#include "RoomExtractor.h"

#include "../IsaacRepentance.h"
#include "../Core/Logger.h"
#include "../Models/GpuMesh.h"
#include "../Models/Texture.h"

#include <cstdint>
#include <string>
#include <utility>

namespace ViewPoint
{
    namespace
    {
        constexpr unsigned int MAX_GRID_CELLS = 447;

        constexpr int GRID_WALL_TYPE = 15;

        constexpr float FLOOR_Y = -1.5f;
        constexpr float WALL_TOP_Y = 1.5f;
        constexpr float TILE_SIZE = 1.0f;

        Room* g_LastRoom = nullptr;
        int g_LastRoomIndex = -1;
        int g_LastDimension = -1;

        Model g_RoomModel;

        void AddTriangle(
            Model& model,
            int materialIndex,
            int a,
            int b,
            int c)
        {
            Triangle triangle{};

            triangle.corners[0].position = a;
            triangle.corners[1].position = b;
            triangle.corners[2].position = c;

            triangle.materialIndex = materialIndex;

            model.triangles.push_back(triangle);
        }

        void AddQuad(
            Model& model,
            int materialIndex,
            const Vertex3& a,
            const Vertex3& b,
            const Vertex3& c,
            const Vertex3& d)
        {
            const int base =
                static_cast<int>(model.vertices.size());

            model.vertices.push_back(a);
            model.vertices.push_back(b);
            model.vertices.push_back(c);
            model.vertices.push_back(d);

            AddTriangle(
                model,
                materialIndex,
                base,
                base + 1,
                base + 2);

            AddTriangle(
                model,
                materialIndex,
                base,
                base + 2,
                base + 3);
        }

        void AddWallBlock(
            Model& model,
            float centerX,
            float centerZ)
        {
            const float half = TILE_SIZE * 0.5f;

            const float left = centerX - half;
            const float right = centerX + half;

            const float front = centerZ - half;
            const float back = centerZ + half;

            const float bottom = FLOOR_Y;
            const float top = WALL_TOP_Y;

            // Front.
            AddQuad(
                model,
                1,
                {left, bottom, front},
                {right, bottom, front},
                {right, top, front},
                {left, top, front});

            // Back.
            AddQuad(
                model,
                1,
                {right, bottom, back},
                {left, bottom, back},
                {left, top, back},
                {right, top, back});

            // Left.
            AddQuad(
                model,
                1,
                {left, bottom, back},
                {left, bottom, front},
                {left, top, front},
                {left, top, back});

            // Right.
            AddQuad(
                model,
                1,
                {right, bottom, front},
                {right, bottom, back},
                {right, top, back},
                {right, top, front});

            // Top.
            AddQuad(
                model,
                1,
                {left, top, front},
                {right, top, front},
                {right, top, back},
                {left, top, back});

            // Bottom.
            AddQuad(
                model,
                1,
                {left, bottom, back},
                {right, bottom, back},
                {right, bottom, front},
                {left, bottom, front});
        }

        void ResetRoomModel()
        {
            ReleaseModelTextures(g_RoomModel);
            ReleaseModelGpu(g_RoomModel);

            g_RoomModel = Model{};
        }

        bool BuildRoomModel(
            Room* room,
            int roomIndex,
            int dimension)
        {
            if (!room)
                return false;

            const unsigned int width =
                static_cast<unsigned int>(room->_gridWidth);

            const unsigned int height =
                static_cast<unsigned int>(room->_gridHeight);

            if (width == 0 || height == 0)
                return false;

            const unsigned int cellCount = width * height;

            if (cellCount > MAX_GRID_CELLS)
            {
                LogMessage(
                    "RoomExtractor: Grid exceeds maximum supported size.");

                return false;
            }

            Model model;

            model.path =
                "generated/room_" +
                std::to_string(roomIndex) +
                "_dimension_" +
                std::to_string(dimension);

            model.position = {0.0f, 0.0f, 0.0f};
            model.rotation = {0.0f, 0.0f, 0.0f};
            model.scale = 1.0f;

            // Floor material.
            Material floorMaterial;
            floorMaterial.name = "RoomFloor";
            floorMaterial.diffuse[0] = 0.32f;
            floorMaterial.diffuse[1] = 0.30f;
            floorMaterial.diffuse[2] = 0.29f;

            // Wall material.
            Material wallMaterial;
            wallMaterial.name = "RoomWalls";
            wallMaterial.diffuse[0] = 0.62f;
            wallMaterial.diffuse[1] = 0.60f;
            wallMaterial.diffuse[2] = 0.57f;

            model.materials.push_back(
                std::move(floorMaterial));

            model.materials.push_back(
                std::move(wallMaterial));

            const float halfWidth =
                static_cast<float>(width) * TILE_SIZE * 0.5f;

            const float halfHeight =
                static_cast<float>(height) * TILE_SIZE * 0.5f;

            // One continuous floor.
            AddQuad(
                model,
                0,
                {-halfWidth, FLOOR_Y, -halfHeight},
                {halfWidth, FLOOR_Y, -halfHeight},
                {halfWidth, FLOOR_Y, halfHeight},
                {-halfWidth, FLOOR_Y, halfHeight});

            unsigned int wallCount = 0;
            unsigned int doorCount = 0;

            for (unsigned int i = 0; i < cellCount; ++i)
            {
                GridEntity* grid =
                    room->GetGridEntity(static_cast<int>(i));

                if (!grid)
                    continue;

                const int entityType =
                    static_cast<int>(grid->GetType());

                if (entityType == 16)
                {
                    ++doorCount;
                    continue;
                }

                if (entityType != GRID_WALL_TYPE)
                    continue;

                const unsigned int row = i / width;
                const unsigned int column = i % width;

                const float centerX =
                    (static_cast<float>(column) -
                     (static_cast<float>(width) - 1.0f) * 0.5f) *
                    TILE_SIZE;

                const float centerZ =
                    ((static_cast<float>(height) - 1.0f) * 0.5f -
                     static_cast<float>(row)) *
                    TILE_SIZE;

                AddWallBlock(
                    model,
                    centerX,
                    centerZ);

                ++wallCount;
            }

            model.loaded = true;
            model.attempted = true;

            g_RoomModel = std::move(model);

            LogMessage(
                ("RoomExtractor: Generated room mesh: " +
                 g_RoomModel.path).c_str());

            LogNumber(
                "RoomExtractor: Generated wall blocks",
                wallCount);

            LogNumber(
                "RoomExtractor: Door openings",
                doorCount);

            LogNumber(
                "RoomExtractor: Generated triangles",
                g_RoomModel.triangles.size());

            return true;
        }

        void LogRoom(
            Room* room,
            int roomIndex,
            int dimension)
        {
            if (!room)
                return;

            const unsigned int width =
                static_cast<unsigned int>(room->_gridWidth);

            const unsigned int height =
                static_cast<unsigned int>(room->_gridHeight);

            LogNumber("RoomExtractor: Width", width);
            LogNumber("RoomExtractor: Height", height);

            const unsigned int cellCount = width * height;

            if (cellCount > MAX_GRID_CELLS)
            {
                LogMessage(
                    "RoomExtractor: Room grid is too large.");

                return;
            }

            unsigned int occupiedCells = 0;

            for (unsigned int i = 0; i < cellCount; ++i)
            {
                GridEntity* grid =
                    room->GetGridEntity(static_cast<int>(i));

                if (grid)
                    ++occupiedCells;
            }

            LogNumber(
                "RoomExtractor: Occupied grid cells",
                occupiedCells);

            if (!BuildRoomModel(
                    room,
                    roomIndex,
                    dimension))
            {
                LogMessage(
                    "RoomExtractor: Room mesh generation failed.");
            }
        }
    }

    Model* GetRoomModel()
    {
        return g_RoomModel.loaded
            ? &g_RoomModel
            : nullptr;
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

            ResetRoomModel();

            return;
        }

        const int roomIndex =
            g_Game->GetCurrentRoomIdx();

        const int dimension =
            g_Game->GetDimension();

        if (room == g_LastRoom &&
            roomIndex == g_LastRoomIndex &&
            dimension == g_LastDimension)
        {
            return;
        }

        g_LastRoom = room;
        g_LastRoomIndex = roomIndex;
        g_LastDimension = dimension;

        ResetRoomModel();

        LogMessage(
            "RoomExtractor: Room changed.");

        LogRoom(
            room,
            roomIndex,
            dimension);
    }
}
