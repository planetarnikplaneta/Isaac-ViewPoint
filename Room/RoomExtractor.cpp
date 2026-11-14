
#include "RoomExtractor.h"

#include "../IsaacRepentance.h"
#include "../Core/Logger.h"
#include "../Models/GpuMesh.h"
#include "../Models/Texture.h"

#include <cstdint>
#include <string>
#include <utility>
#include <limits>
#include <vector>

namespace ViewPoint
{
    namespace
    {
        constexpr unsigned int MAX_GRID_CELLS = 448;

        constexpr int GRID_DECORATION = 1;
        constexpr int GRID_ROCK = 2;
        constexpr int GRID_ROCKB = 3;
        constexpr int GRID_ROCKT = 4;
        constexpr int GRID_ROCK_BOMB = 5;
        constexpr int GRID_ROCK_ALT = 6;
        constexpr int GRID_PIT = 7;
        constexpr int GRID_SPIKES = 8;
        constexpr int GRID_SPIKES_ONOFF = 9;
        constexpr int GRID_SPIDERWEB = 10;
        constexpr int GRID_LOCK = 11;
        constexpr int GRID_TNT = 12;
        constexpr int GRID_FIREPLACE = 13;
        constexpr int GRID_POOP = 14;
        constexpr int GRID_WALL = 15;
        constexpr int GRID_DOOR = 16;
        constexpr int GRID_TRAPDOOR = 17;
        constexpr int GRID_PRESSURE_PLATE = 20;
        constexpr int GRID_ROCK_SS = 22;
        constexpr int GRID_ROCK_SPIKED = 25;
        constexpr int GRID_ROCK_ALT2 = 26;
        constexpr int GRID_ROCK_GOLD = 27;

        constexpr float FLOOR_Y = -1.5f;
        constexpr float WALL_TOP_Y = 1.0f;
        constexpr float TILE_SIZE = 1.0f;

        // Material indices.
        constexpr int MAT_FLOOR = 0;
        constexpr int MAT_WALL = 1;
        constexpr int MAT_ROCK = 2;
        constexpr int MAT_PIT = 3;
        constexpr int MAT_SPIKES = 4;
        constexpr int MAT_WEB = 5;
        constexpr int MAT_OBJECT = 6;
        constexpr int MAT_POOP = 7;
        constexpr int MAT_FIRE = 8;
        constexpr int MAT_ROCK_CRACK = 9;
        constexpr int MAT_ROCK_B = 10;
        constexpr int MAT_ROCK_B_TOP = 11;
        constexpr int MAT_ROCK_T = 12;
        constexpr int MAT_BOMB = 13;
        constexpr int MAT_BOMB_FUSE = 14;
        constexpr int MAT_PIT_RIM = 15;
        constexpr int MAT_TNT = 16;
        constexpr int MAT_TNT_TOP = 17;
        constexpr int MAT_TNT_MARK = 18;

        Room *g_LastRoom = nullptr;
        int g_LastRoomIndex = -1;
        int g_LastDimension = -1;
        uint64_t g_LastRoomGridSignature = 0;

        Model g_RoomModel;

        bool IsGridEntityDestroyed(GridEntity *grid)
        {
            if (!grid)
                return true;

            GridEntityDesc *desc = grid->GetDesc();
            if (!desc)
                return true;

            return desc->_type <= 0 || desc->_state == 2;
        }

        uint64_t ComputeRoomGridSignature(
            Room *room)
        {
            if (!room)
                return 0;

            const unsigned int width =
                static_cast<unsigned int>(room->_gridWidth);

            const unsigned int height =
                static_cast<unsigned int>(room->_gridHeight);

            const unsigned int cellCount = width * height;

            uint64_t hash = 14695981039346656037ull;

            const auto mix = [&hash](uint64_t value)
            {
                hash ^= value + 0x9e3779b97f4a7c15ull +
                        (hash << 6) + (hash >> 2);
            };

            mix(static_cast<uint64_t>(width));
            mix(static_cast<uint64_t>(height));
            mix(static_cast<uint64_t>(room->_roomType));

            for (unsigned int i = 0; i < cellCount; ++i)
            {
                GridEntity *grid = room->GetGridEntity(i);

                if (!grid)
                {
                    mix(0ull);
                    continue;
                }

                GridEntityDesc *desc = grid->GetDesc();

                if (!desc)
                {
                    mix(0ull);
                    continue;
                }

                mix(static_cast<uint64_t>(desc->_type));
                mix(static_cast<uint64_t>(desc->_variant));
                mix(static_cast<uint64_t>(desc->_state));
                mix(static_cast<uint64_t>(desc->_varData));
            }

            for (unsigned int i = 0; i < 8; ++i)
            {
                GridEntity *door = room->_doors[i];

                const uint32_t doorType =
                    door ? static_cast<uint32_t>(door->GetType()) : 0u;

                mix(static_cast<uint64_t>(doorType + 1u) +
                    static_cast<uint64_t>(i * 131u));
                mix(static_cast<uint64_t>(room->_doorGridPositions[i]) +
                    static_cast<uint64_t>(i * 17u));
            }

            return hash;
        }
        void DiagnoseFloorImage(
            const char *name,
            KAGE_Graphics_ImageBase *image)
        {
            if (!image)
            {
                LogMessage(name);
                return;
            }

            const int width = image->GetWidth();
            const int height = image->GetHeight();

            if (width <= 0 || height <= 0)
                return;

            std::vector<unsigned char> pixels(
                static_cast<size_t>(width) * height * 4);

            image->GetTexelRegion(
                0,
                0,
                static_cast<unsigned int>(width),
                static_cast<unsigned int>(height),
                pixels.data());

            int minX = width;
            int minY = height;
            int maxX = -1;
            int maxY = -1;

            uint64_t count = 0;

            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    const size_t i =
                        (static_cast<size_t>(y) * width + x) * 4;

                    if (pixels[i + 3] == 0 &&
                        pixels[i] == 0 &&
                        pixels[i + 1] == 0 &&
                        pixels[i + 2] == 0)
                        continue;

                    if (x < minX)
                        minX = x;
                    if (y < minY)
                        minY = y;
                    if (x > maxX)
                        maxX = x;
                    if (y > maxY)
                        maxY = y;

                    ++count;
                }
            }

            LogMessage(name);
            LogNumber("Image content min X", minX);
            LogNumber("Image content min Y", minY);
            LogNumber("Image content max X", maxX);
            LogNumber("Image content max Y", maxY);
            LogNumber("Image content pixels", static_cast<double>(count));
        }

        bool ExtractFloorTexture(
            Room *room,
            KAGE_Graphics_ImageBase *image,
            int &outWidth,
            int &outHeight,
            std::vector<unsigned char> &outPixels)
        {
            if (!room || !image)
                return false;

            constexpr int PIXELS_PER_TILE = 26;
            constexpr int CROP_OFFSET = 52;

            const int gridWidth = room->_gridWidth;
            const int gridHeight = room->_gridHeight;

            const int imageWidth = image->GetWidth();
            const int imageHeight = image->GetHeight();

            if (gridWidth <= 2 ||
                gridHeight <= 2 ||
                imageWidth <= 0 ||
                imageHeight <= 0)
            {
                return false;
            }

            const int cropX = CROP_OFFSET;
            const int cropY = CROP_OFFSET;

            const int cropWidth =
                (gridWidth - 2) * PIXELS_PER_TILE;

            const int cropHeight =
                (gridHeight - 2) * PIXELS_PER_TILE;

            if (cropX < 0 ||
                cropY < 0 ||
                cropWidth <= 0 ||
                cropHeight <= 0 ||
                cropX + cropWidth > imageWidth ||
                cropY + cropHeight > imageHeight)
            {
                LogMessage(
                    "RoomExtractor: Fixed floor crop exceeds image bounds.");

                LogNumber("Floor image width", imageWidth);
                LogNumber("Floor image height", imageHeight);
                LogNumber("Floor crop X", cropX);
                LogNumber("Floor crop Y", cropY);
                LogNumber("Floor crop width", cropWidth);
                LogNumber("Floor crop height", cropHeight);

                return false;
            }

            const size_t outputSize =
                static_cast<size_t>(cropWidth) *
                static_cast<size_t>(cropHeight) * 4;

            outPixels.resize(outputSize);

            image->GetTexelRegion(
                cropX,
                cropY,
                static_cast<unsigned int>(cropWidth),
                static_cast<unsigned int>(cropHeight),
                outPixels.data());

            outWidth = cropWidth;
            outHeight = cropHeight;

            return true;
        }

        bool CopyIsaacFloorTexture(
            Room *room,
            Material &material)
        {
            if (!room)
                return false;

            Backdrop *backdrop = room->GetBackdrop();

            if (!backdrop)
            {
                LogMessage(
                    "RoomExtractor: Current room has no backdrop.");
                return false;
            }

            KAGE_Graphics_ImageBase *image =
                backdrop->floorBuffer.image;

            if (!image)
            {
                LogMessage(
                    "RoomExtractor: Backdrop floor image is null.");
                return false;
            }

            std::vector<unsigned char> pixels;

            int width = 0;
            int height = 0;

            if (!ExtractFloorTexture(
                    room,
                    image,
                    width,
                    height,
                    pixels))
            {
                LogMessage(
                    "RoomExtractor: Failed to extract floor texture.");
                return false;
            }

            material.width = width;
            material.height = height;
            material.pixels = std::move(pixels);

            material.textureAttempted = true;
            material.diffuseTexturePath.clear();

            LogMessage(
                "RoomExtractor: Copied fixed-region Isaac floor texture.");

            LogNumber("RoomExtractor: Floor texture width", width);
            LogNumber("RoomExtractor: Floor texture height", height);

            return true;
        }

        void RefreshIsaacFloorTexture(
            Room *room,
            Material &material)
        {
            if (!room)
                return;

            Backdrop *backdrop = room->GetBackdrop();

            if (!backdrop || !backdrop->floorBuffer.image)
                return;

            std::vector<unsigned char> pixels;

            int width = 0;
            int height = 0;

            if (!ExtractFloorTexture(
                    room,
                    backdrop->floorBuffer.image,
                    width,
                    height,
                    pixels))
                return;

            UpdateMaterialTexture(
                material,
                width,
                height,
                std::move(pixels));
        }

        void AddTriangle(
            Model &model,
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
            Model &model,
            int materialIndex,
            const Vertex3 &a,
            const Vertex3 &b,
            const Vertex3 &c,
            const Vertex3 &d)
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

        void AddTexturedFloorQuad(
            Model &model,
            int materialIndex,
            const Vertex3 &a,
            const Vertex3 &b,
            const Vertex3 &c,
            const Vertex3 &d)
        {
            const int texcoordBase =
                static_cast<int>(model.texcoords.size());

            model.texcoords.push_back({1.0f, 1.0f});
            model.texcoords.push_back({0.0f, 1.0f});
            model.texcoords.push_back({0.0f, 0.0f});
            model.texcoords.push_back({1.0f, 0.0f});

            AddQuad(
                model,
                materialIndex,
                a,
                b,
                c,
                d);

            const size_t triangleBase =
                model.triangles.size() - 2;

            Triangle &first = model.triangles[triangleBase];
            Triangle &second = model.triangles[triangleBase + 1];

            first.corners[0].texcoord = texcoordBase;
            first.corners[1].texcoord = texcoordBase + 1;
            first.corners[2].texcoord = texcoordBase + 2;

            second.corners[0].texcoord = texcoordBase;
            second.corners[1].texcoord = texcoordBase + 2;
            second.corners[2].texcoord = texcoordBase + 3;
        }

        void AddTexturedQuadUV(
            Model &model,
            int materialIndex,
            const Vertex3 &a,
            const Vertex3 &b,
            const Vertex3 &c,
            const Vertex3 &d,
            const Vertex2 &uvA,
            const Vertex2 &uvB,
            const Vertex2 &uvC,
            const Vertex2 &uvD)
        {
            const int texcoordBase =
                static_cast<int>(model.texcoords.size());

            model.texcoords.push_back(uvA);
            model.texcoords.push_back(uvB);
            model.texcoords.push_back(uvC);
            model.texcoords.push_back(uvD);

            AddQuad(
                model,
                materialIndex,
                a,
                b,
                c,
                d);

            const size_t triangleBase =
                model.triangles.size() - 2;

            Triangle &first = model.triangles[triangleBase];
            Triangle &second = model.triangles[triangleBase + 1];

            first.corners[0].texcoord = texcoordBase;
            first.corners[1].texcoord = texcoordBase + 1;
            first.corners[2].texcoord = texcoordBase + 2;

            second.corners[0].texcoord = texcoordBase;
            second.corners[1].texcoord = texcoordBase + 2;
            second.corners[2].texcoord = texcoordBase + 3;
        }

        void AddTexturedQuad(
            Model &model,
            int materialIndex,
            const Vertex3 &a,
            const Vertex3 &b,
            const Vertex3 &c,
            const Vertex3 &d)
        {
            AddTexturedQuadUV(
                model,
                materialIndex,
                a,
                b,
                c,
                d,
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f});
        }

        void AddBox(
            Model &model,
            int materialIndex,
            float centerX,
            float centerZ,
            float halfWidth,
            float bottom,
            float top,
            float halfDepth)
        {
            const float left = centerX - halfWidth;
            const float right = centerX + halfWidth;

            const float front = centerZ - halfDepth;
            const float back = centerZ + halfDepth;

            AddTexturedQuadUV(
                model, materialIndex,
                {left, bottom, front},
                {right, bottom, front},
                {right, top, front},
                {left, top, front},
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f});

            AddTexturedQuadUV(
                model, materialIndex,
                {right, bottom, back},
                {left, bottom, back},
                {left, top, back},
                {right, top, back},
                {1.0f, 0.0f},
                {0.0f, 0.0f},
                {0.0f, 1.0f},
                {1.0f, 1.0f});

            AddTexturedQuadUV(
                model, materialIndex,
                {left, bottom, back},
                {left, bottom, front},
                {left, top, front},
                {left, top, back},
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f});

            AddTexturedQuadUV(
                model, materialIndex,
                {right, bottom, front},
                {right, bottom, back},
                {right, top, back},
                {right, top, front},
                {1.0f, 0.0f},
                {0.0f, 0.0f},
                {0.0f, 1.0f},
                {1.0f, 1.0f});

            AddTexturedQuadUV(
                model, materialIndex,
                {left, top, front},
                {right, top, front},
                {right, top, back},
                {left, top, back},
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f});

            AddTexturedQuadUV(
                model, materialIndex,
                {left, bottom, back},
                {right, bottom, back},
                {right, bottom, front},
                {left, bottom, front},
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f});
        }

        void AddPyramid(
            Model &model,
            int materialIndex,
            float centerX,
            float centerZ,
            float halfWidth,
            float bottom,
            float top,
            float halfDepth)
        {
            const int base =
                static_cast<int>(model.vertices.size());

            model.vertices.push_back(
                {centerX - halfWidth, bottom, centerZ - halfDepth});

            model.vertices.push_back(
                {centerX + halfWidth, bottom, centerZ - halfDepth});

            model.vertices.push_back(
                {centerX + halfWidth, bottom, centerZ + halfDepth});

            model.vertices.push_back(
                {centerX - halfWidth, bottom, centerZ + halfDepth});

            model.vertices.push_back(
                {centerX, top, centerZ});

            AddTriangle(model, materialIndex, base, base + 1, base + 2);
            AddTriangle(model, materialIndex, base, base + 2, base + 3);

            AddTriangle(model, materialIndex, base, base + 4, base + 1);
            AddTriangle(model, materialIndex, base + 1, base + 4, base + 2);
            AddTriangle(model, materialIndex, base + 2, base + 4, base + 3);
            AddTriangle(model, materialIndex, base + 3, base + 4, base);
        }

        void AddWallSegment(
            Model &model,
            float centerX,
            float centerZ,
            float halfWidth,
            float halfDepth)
        {
            AddBox(
                model,
                MAT_WALL,
                centerX,
                centerZ,
                halfWidth,
                FLOOR_Y,
                WALL_TOP_Y,
                halfDepth);
        }

        void AddWallBlock(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddWallSegment(
                model,
                centerX,
                centerZ,
                TILE_SIZE * 0.5f,
                TILE_SIZE * 0.5f);
        }

        void AddRock(
            Model &model,
            float centerX,
            float centerZ)
        {
            const float bottom = FLOOR_Y + 0.02f;
            const float top = FLOOR_Y + 0.88f;

            AddBox(
                model,
                MAT_ROCK,
                centerX,
                centerZ,
                0.38f,
                bottom,
                top,
                0.34f);

            AddBox(
                model,
                MAT_ROCK_CRACK,
                centerX - 0.12f,
                centerZ,
                0.05f,
                FLOOR_Y + 0.18f,
                FLOOR_Y + 0.74f,
                0.22f);

            AddBox(
                model,
                MAT_ROCK_CRACK,
                centerX + 0.08f,
                centerZ - 0.10f,
                0.18f,
                FLOOR_Y + 0.12f,
                FLOOR_Y + 0.68f,
                0.04f);
        }

        void AddRockB(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddBox(
                model,
                MAT_ROCK_B,
                centerX,
                centerZ,
                0.34f,
                FLOOR_Y + 0.03f,
                FLOOR_Y + 0.70f,
                0.30f);

            AddBox(
                model,
                MAT_ROCK_B_TOP,
                centerX,
                centerZ,
                0.24f,
                FLOOR_Y + 0.70f,
                FLOOR_Y + 0.82f,
                0.20f);
        }

        void AddRockT(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddRock(model, centerX, centerZ);

            const float y = FLOOR_Y + 0.82f;

            AddQuad(
                model,
                MAT_ROCK_T,
                {centerX - 0.18f, y, centerZ - 0.26f},
                {centerX + 0.18f, y, centerZ - 0.10f},
                {centerX + 0.18f, y, centerZ + 0.10f},
                {centerX - 0.18f, y, centerZ + 0.26f});

            AddQuad(
                model,
                MAT_ROCK_T,
                {centerX - 0.18f, y, centerZ + 0.10f},
                {centerX + 0.18f, y, centerZ - 0.10f},
                {centerX + 0.18f, y, centerZ + 0.26f},
                {centerX - 0.18f, y, centerZ - 0.26f});
        }

        void AddRockBomb(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddRock(model, centerX, centerZ);

            AddBox(
                model,
                MAT_BOMB,
                centerX + 0.28f,
                centerZ + 0.06f,
                0.11f,
                FLOOR_Y + 0.38f,
                FLOOR_Y + 0.64f,
                0.11f);

            AddBox(
                model,
                MAT_BOMB_FUSE,
                centerX + 0.39f,
                centerZ + 0.06f,
                0.04f,
                FLOOR_Y + 0.64f,
                FLOOR_Y + 0.80f,
                0.04f);
        }

        void AddPit(
            Model &model,
            float centerX,
            float centerZ)
        {
            const float half = TILE_SIZE * 0.46f;
            const float rimY = FLOOR_Y + 0.03f;
            const float holeY = FLOOR_Y + 0.015f;

            AddQuad(
                model,
                MAT_PIT_RIM,
                {centerX - half, rimY, centerZ - half},
                {centerX + half, rimY, centerZ - half},
                {centerX + half, rimY, centerZ + half},
                {centerX - half, rimY, centerZ + half});

            AddQuad(
                model,
                MAT_PIT,
                {centerX - half * 0.68f, holeY, centerZ - half * 0.68f},
                {centerX + half * 0.68f, holeY, centerZ - half * 0.68f},
                {centerX + half * 0.68f, holeY, centerZ + half * 0.68f},
                {centerX - half * 0.68f, holeY, centerZ + half * 0.68f});
        }

        void AddSpikes(
            Model &model,
            float centerX,
            float centerZ)
        {
            const float base = FLOOR_Y + 0.03f;
            const float top = FLOOR_Y + 0.52f;
            const float toothSize = 0.11f;

            const std::vector<std::pair<float, float>> positions = {
                {-0.38f, -0.38f}, {0.00f, -0.38f}, {0.38f, -0.38f}, {0.76f, -0.38f},
                {-0.19f, 0.00f}, {0.19f, 0.00f}, {0.57f, 0.00f},
                {-0.38f, 0.38f}, {0.00f, 0.38f}, {0.38f, 0.38f}, {0.76f, 0.38f}};

            for (const auto &[offsetX, offsetZ] : positions)
            {
                AddPyramid(
                    model,
                    MAT_SPIKES,
                    centerX + offsetX,
                    centerZ + offsetZ,
                    toothSize,
                    base,
                    top,
                    toothSize);
            }
        }

        void AddWeb(
            Model &model,
            float centerX,
            float centerZ)
        {
            const float y = FLOOR_Y + 0.025f;
            const float half = 0.43f;
            const float thickness = 0.025f;

            // Diagonal strip one.
            AddQuad(
                model,
                MAT_WEB,
                {centerX - half, y, centerZ - half + thickness},
                {centerX - half + thickness, y, centerZ - half},
                {centerX + half, y, centerZ + half - thickness},
                {centerX + half - thickness, y, centerZ + half});

            // Diagonal strip two.
            AddQuad(
                model,
                MAT_WEB,
                {centerX + half - thickness, y, centerZ - half},
                {centerX + half, y, centerZ - half + thickness},
                {centerX - half + thickness, y, centerZ + half},
                {centerX - half, y, centerZ + half - thickness});

            // Horizontal and vertical strands.
            AddQuad(
                model,
                MAT_WEB,
                {centerX - half, y, centerZ - thickness},
                {centerX + half, y, centerZ - thickness},
                {centerX + half, y, centerZ + thickness},
                {centerX - half, y, centerZ + thickness});

            AddQuad(
                model,
                MAT_WEB,
                {centerX - thickness, y, centerZ - half},
                {centerX + thickness, y, centerZ - half},
                {centerX + thickness, y, centerZ + half},
                {centerX - thickness, y, centerZ + half});
        }

        void AddLock(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddBox(
                model,
                MAT_OBJECT,
                centerX,
                centerZ,
                0.25f,
                FLOOR_Y + 0.03f,
                FLOOR_Y + 0.55f,
                0.22f);

            // Raised lock shackle.
            AddBox(
                model,
                MAT_OBJECT,
                centerX,
                centerZ,
                0.13f,
                FLOOR_Y + 0.50f,
                FLOOR_Y + 0.82f,
                0.10f);
        }

        void AddTNT(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddBox(
                model,
                MAT_TNT,
                centerX,
                centerZ,
                0.32f,
                FLOOR_Y + 0.03f,
                FLOOR_Y + 0.66f,
                0.30f);

            AddBox(
                model,
                MAT_TNT_TOP,
                centerX,
                centerZ,
                0.22f,
                FLOOR_Y + 0.66f,
                FLOOR_Y + 0.86f,
                0.22f);

            AddBox(
                model,
                MAT_TNT_MARK,
                centerX - 0.18f,
                centerZ + 0.05f,
                0.02f,
                FLOOR_Y + 0.42f,
                FLOOR_Y + 0.64f,
                0.08f);

            AddBox(
                model,
                MAT_TNT_MARK,
                centerX,
                centerZ + 0.05f,
                0.08f,
                FLOOR_Y + 0.42f,
                FLOOR_Y + 0.64f,
                0.02f);

            AddBox(
                model,
                MAT_TNT_MARK,
                centerX + 0.18f,
                centerZ + 0.05f,
                0.02f,
                FLOOR_Y + 0.42f,
                FLOOR_Y + 0.64f,
                0.08f);
        }

        void AddFireplace(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddBox(
                model,
                MAT_OBJECT,
                centerX,
                centerZ,
                0.36f,
                FLOOR_Y + 0.03f,
                FLOOR_Y + 0.42f,
                0.34f);

            AddPyramid(
                model,
                MAT_FIRE,
                centerX,
                centerZ,
                0.22f,
                FLOOR_Y + 0.42f,
                FLOOR_Y + 1.05f,
                0.20f);
        }

        void AddPoop(
            Model &model,
            float centerX,
            float centerZ)
        {
            AddBox(
                model,
                MAT_POOP,
                centerX,
                centerZ,
                0.34f,
                FLOOR_Y + 0.03f,
                FLOOR_Y + 0.42f,
                0.32f);

            AddBox(
                model,
                MAT_POOP,
                centerX,
                centerZ,
                0.25f,
                FLOOR_Y + 0.42f,
                FLOOR_Y + 0.68f,
                0.24f);
        }

        void AddGridEntityGeometry(
            Model &model,
            int entityType,
            float centerX,
            float centerZ,
            unsigned int &rockCount,
            unsigned int &pitCount,
            unsigned int &spikeCount,
            unsigned int &webCount,
            unsigned int &objectCount)
        {
            switch (entityType)
            {
            case GRID_ROCK:
                AddRock(model, centerX, centerZ);
                ++rockCount;
                break;

            case GRID_ROCKB:
                AddRockB(model, centerX, centerZ);
                ++rockCount;
                break;

            case GRID_ROCKT:
                AddRockT(model, centerX, centerZ);
                ++rockCount;
                break;

            case GRID_ROCK_BOMB:
                AddRockBomb(model, centerX, centerZ);
                ++rockCount;
                break;

            case GRID_PIT:
                AddPit(model, centerX, centerZ);
                ++pitCount;
                break;

            case GRID_SPIKES:
            case GRID_SPIKES_ONOFF:
                AddSpikes(model, centerX, centerZ);
                ++spikeCount;
                break;

            case GRID_SPIDERWEB:
                AddWeb(model, centerX, centerZ);
                ++webCount;
                break;

            case GRID_LOCK:
                AddLock(model, centerX, centerZ);
                ++objectCount;
                break;

            case GRID_TNT:
                AddTNT(model, centerX, centerZ);
                ++objectCount;
                break;

            case GRID_FIREPLACE:
                AddFireplace(model, centerX, centerZ);
                ++objectCount;
                break;

            case GRID_POOP:
                AddPoop(model, centerX, centerZ);
                ++objectCount;
                break;

            case GRID_DECORATION:
            case GRID_TRAPDOOR:
            case GRID_PRESSURE_PLATE:
                // These are rendered as floor sprites, not as room mesh.
                break;

            default:
                break;
            }
        }

        void ResetRoomModel()
        {
            ReleaseModelTextures(g_RoomModel);
            ReleaseModelGpu(g_RoomModel);

            g_RoomModel = Model{};
        }

        bool BuildRoomModel(
            Room *room,
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

            Material floorMaterial;
            floorMaterial.name = "RoomFloor";

            const bool hasFloorTexture =
                CopyIsaacFloorTexture(room, floorMaterial);

            if (hasFloorTexture)
            {
                floorMaterial.diffuse[0] = 1.0f;
                floorMaterial.diffuse[1] = 1.0f;
                floorMaterial.diffuse[2] = 1.0f;
            }
            else
            {
                floorMaterial.diffuse[0] = 0.32f;
                floorMaterial.diffuse[1] = 0.30f;
                floorMaterial.diffuse[2] = 0.29f;
            }

            Material wallMaterial;
            wallMaterial.name = "RoomWalls";
            wallMaterial.diffuseTexturePath = "textures/wall_basement.png";
            wallMaterial.diffuse[0] = 1.0f;
            wallMaterial.diffuse[1] = 1.0f;
            wallMaterial.diffuse[2] = 1.0f;

            Material rockMaterial;
            rockMaterial.name = "GridRock";
            rockMaterial.diffuse[0] = 0.33f;
            rockMaterial.diffuse[1] = 0.22f;
            rockMaterial.diffuse[2] = 0.13f;

            Material rockCrackMaterial;
            rockCrackMaterial.name = "GridRockCrack";
            rockCrackMaterial.diffuse[0] = 0.20f;
            rockCrackMaterial.diffuse[1] = 0.14f;
            rockCrackMaterial.diffuse[2] = 0.09f;

            Material rockBMaterial;
            rockBMaterial.name = "GridRockB";
            rockBMaterial.diffuse[0] = 0.52f;
            rockBMaterial.diffuse[1] = 0.52f;
            rockBMaterial.diffuse[2] = 0.52f;

            Material rockBTopMaterial;
            rockBTopMaterial.name = "GridRockBTop";
            rockBTopMaterial.diffuse[0] = 0.62f;
            rockBTopMaterial.diffuse[1] = 0.62f;
            rockBTopMaterial.diffuse[2] = 0.62f;

            Material rockTMaterial;
            rockTMaterial.name = "GridRockT";
            rockTMaterial.diffuse[0] = 0.46f;
            rockTMaterial.diffuse[1] = 0.42f;
            rockTMaterial.diffuse[2] = 0.37f;

            Material bombMaterial;
            bombMaterial.name = "GridBomb";
            bombMaterial.diffuse[0] = 0.18f;
            bombMaterial.diffuse[1] = 0.18f;
            bombMaterial.diffuse[2] = 0.18f;

            Material bombFuseMaterial;
            bombFuseMaterial.name = "GridBombFuse";
            bombFuseMaterial.diffuse[0] = 0.85f;
            bombFuseMaterial.diffuse[1] = 0.72f;
            bombFuseMaterial.diffuse[2] = 0.18f;

            Material pitMaterial;
            pitMaterial.name = "GridPits";
            pitMaterial.diffuse[0] = 0.020f;
            pitMaterial.diffuse[1] = 0.018f;
            pitMaterial.diffuse[2] = 0.018f;

            Material pitRimMaterial;
            pitRimMaterial.name = "GridPitRim";
            pitRimMaterial.diffuse[0] = 0.12f;
            pitRimMaterial.diffuse[1] = 0.10f;
            pitRimMaterial.diffuse[2] = 0.09f;

            Material spikeMaterial;
            spikeMaterial.name = "GridSpikes";
            spikeMaterial.diffuse[0] = 0.72f;
            spikeMaterial.diffuse[1] = 0.72f;
            spikeMaterial.diffuse[2] = 0.68f;

            Material webMaterial;
            webMaterial.name = "GridWebs";
            webMaterial.diffuse[0] = 0.78f;
            webMaterial.diffuse[1] = 0.75f;
            webMaterial.diffuse[2] = 0.69f;

            Material objectMaterial;
            objectMaterial.name = "GridObjects";
            objectMaterial.diffuse[0] = 0.65f;
            objectMaterial.diffuse[1] = 0.20f;
            objectMaterial.diffuse[2] = 0.12f;

            Material poopMaterial;
            poopMaterial.name = "GridPoop";
            poopMaterial.diffuse[0] = 0.38f;
            poopMaterial.diffuse[1] = 0.20f;
            poopMaterial.diffuse[2] = 0.09f;

            Material fireMaterial;
            fireMaterial.name = "GridFire";
            fireMaterial.diffuse[0] = 1.0f;
            fireMaterial.diffuse[1] = 0.35f;
            fireMaterial.diffuse[2] = 0.035f;

            Material tntMaterial;
            tntMaterial.name = "GridTNT";
            tntMaterial.diffuse[0] = 0.27f;
            tntMaterial.diffuse[1] = 0.23f;
            tntMaterial.diffuse[2] = 0.17f;

            Material tntTopMaterial;
            tntTopMaterial.name = "GridTNTTop";
            tntTopMaterial.diffuse[0] = 0.55f;
            tntTopMaterial.diffuse[1] = 0.50f;
            tntTopMaterial.diffuse[2] = 0.42f;

            Material tntMarkMaterial;
            tntMarkMaterial.name = "GridTNTMark";
            tntMarkMaterial.diffuse[0] = 0.08f;
            tntMarkMaterial.diffuse[1] = 0.08f;
            tntMarkMaterial.diffuse[2] = 0.08f;

            model.materials.push_back(std::move(floorMaterial));
            model.materials.push_back(std::move(wallMaterial));
            model.materials.push_back(std::move(rockMaterial));
            model.materials.push_back(std::move(pitMaterial));
            model.materials.push_back(std::move(spikeMaterial));
            model.materials.push_back(std::move(webMaterial));
            model.materials.push_back(std::move(objectMaterial));
            model.materials.push_back(std::move(poopMaterial));
            model.materials.push_back(std::move(fireMaterial));
            model.materials.push_back(std::move(rockCrackMaterial));
            model.materials.push_back(std::move(rockBMaterial));
            model.materials.push_back(std::move(rockBTopMaterial));
            model.materials.push_back(std::move(rockTMaterial));
            model.materials.push_back(std::move(bombMaterial));
            model.materials.push_back(std::move(bombFuseMaterial));
            model.materials.push_back(std::move(pitRimMaterial));
            model.materials.push_back(std::move(tntMaterial));
            model.materials.push_back(std::move(tntTopMaterial));
            model.materials.push_back(std::move(tntMarkMaterial));

            const float halfWidth =
                (static_cast<float>(width) - 2.0f) *
                TILE_SIZE * 0.5f;

            const float halfHeight =
                (static_cast<float>(height) - 2.0f) *
                TILE_SIZE * 0.5f;

            AddTexturedFloorQuad(
                model,
                MAT_FLOOR,
                {-halfWidth, FLOOR_Y, -halfHeight},
                {halfWidth, FLOOR_Y, -halfHeight},
                {halfWidth, FLOOR_Y, halfHeight},
                {-halfWidth, FLOOR_Y, halfHeight});

            unsigned int wallCount = 0;
            unsigned int doorCount = 0;
            unsigned int rockCount = 0;
            unsigned int pitCount = 0;
            unsigned int spikeCount = 0;
            unsigned int webCount = 0;
            unsigned int objectCount = 0;

            std::vector<unsigned char> wallMask(
                cellCount,
                0);

            for (unsigned int i = 0; i < cellCount; ++i)
            {
                GridEntity *grid =
                    room->GetGridEntity(static_cast<int>(i));

                if (!grid || IsGridEntityDestroyed(grid))
                    continue;

                const int entityType =
                    static_cast<int>(grid->GetType());

                if (entityType == GRID_DOOR)
                {
                    // Keep the wall patch behind the door so there is no
                    // visible opening in the room shell, then render the
                    // animated door sprite on top of that wall face.
                    wallMask[i] = 1;
                    ++doorCount;
                    continue;
                }

                if (entityType == GRID_WALL)
                {
                    wallMask[i] = 1;
                    ++wallCount;
                    continue;
                }

                const unsigned int row = i / width;
                const unsigned int column = i % width;

                // Isaac's room grid is mirrored relative to the 3D world
                // used by the renderer. Keep the X axis sign consistent
                // between the room mesh, player camera, and entity positions.
                const float centerX =
                    ((static_cast<float>(width) - 1.0f) * 0.5f -
                     static_cast<float>(column)) *
                    TILE_SIZE;

                const float centerZ =
                    ((static_cast<float>(height) - 1.0f) * 0.5f -
                     static_cast<float>(row)) *
                    TILE_SIZE;

                AddGridEntityGeometry(
                    model,
                    entityType,
                    centerX,
                    centerZ,
                    rockCount,
                    pitCount,
                    spikeCount,
                    webCount,
                    objectCount);
            }

            std::vector<unsigned char> wallProcessed(
                cellCount,
                0);

            for (unsigned int row = 0; row < height; ++row)
            {
                for (unsigned int column = 0; column < width; ++column)
                {
                    const unsigned int index = row * width + column;

                    if (!wallMask[index] || wallProcessed[index])
                        continue;

                    unsigned int spanWidth = 1;
                    while (column + spanWidth < width)
                    {
                        const unsigned int nextIndex =
                            row * width + (column + spanWidth);

                        if (!wallMask[nextIndex] || wallProcessed[nextIndex])
                            break;

                        ++spanWidth;
                    }

                    unsigned int spanHeight = 1;
                    while (row + spanHeight < height)
                    {
                        bool rowFull = true;

                        for (unsigned int x = 0; x < spanWidth; ++x)
                        {
                            const unsigned int nextIndex =
                                (row + spanHeight) * width +
                                (column + x);

                            if (!wallMask[nextIndex] ||
                                wallProcessed[nextIndex])
                            {
                                rowFull = false;
                                break;
                            }
                        }

                        if (!rowFull)
                            break;

                        ++spanHeight;
                    }

                    const float centerX =
                        ((static_cast<float>(width) - 1.0f) * 0.5f -
                         (static_cast<float>(column) +
                          (static_cast<float>(spanWidth) - 1.0f) * 0.5f)) *
                        TILE_SIZE;

                    const float centerZ =
                        ((static_cast<float>(height) - 1.0f) * 0.5f -
                         (static_cast<float>(row) +
                          (static_cast<float>(spanHeight) - 1.0f) * 0.5f)) *
                        TILE_SIZE;

                    AddWallSegment(
                        model,
                        centerX,
                        centerZ,
                        (static_cast<float>(spanWidth) * 0.5f) * TILE_SIZE,
                        (static_cast<float>(spanHeight) * 0.5f) * TILE_SIZE);

                    for (unsigned int y = 0; y < spanHeight; ++y)
                    {
                        for (unsigned int x = 0; x < spanWidth; ++x)
                        {
                            const unsigned int markIndex =
                                (row + y) * width + (column + x);

                            wallProcessed[markIndex] = 1;
                        }
                    }
                }
            }

            model.loaded = true;
            model.attempted = true;

            g_RoomModel = std::move(model);

            LogMessage(
                ("RoomExtractor: Generated room mesh: " +
                 g_RoomModel.path)
                    .c_str());

            LogNumber("RoomExtractor: Wall blocks", wallCount);
            LogNumber("RoomExtractor: Door openings", doorCount);
            LogNumber("RoomExtractor: Rocks", rockCount);
            LogNumber("RoomExtractor: Pits", pitCount);
            LogNumber("RoomExtractor: Spikes", spikeCount);
            LogNumber("RoomExtractor: Spider webs", webCount);
            LogNumber("RoomExtractor: Other grid objects", objectCount);
            LogNumber(
                "RoomExtractor: Generated triangles",
                g_RoomModel.triangles.size());

            return true;
        }

        void LogRoom(
            Room *room,
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
                GridEntity *grid =
                    room->GetGridEntity(static_cast<int>(i));

                if (grid)
                    ++occupiedCells;
            }

            LogNumber(
                "RoomExtractor: Occupied grid cells",
                occupiedCells);

            if (!BuildRoomModel(room, roomIndex, dimension))
            {
                LogMessage(
                    "RoomExtractor: Room mesh generation failed.");
            }
        }
    }

    Model *GetRoomModel()
    {
        return g_RoomModel.loaded
                   ? &g_RoomModel
                   : nullptr;
    }

    void UpdateRoomExtractor()
    {
        if (!g_Game)
            return;

        Room *room = g_Game->GetCurrentRoom();

        if (!room)
        {
            g_LastRoom = nullptr;
            g_LastRoomIndex = -1;
            g_LastDimension = -1;
            g_LastRoomGridSignature = 0;

            ResetRoomModel();
            return;
        }

        const int roomIndex =
            g_Game->GetCurrentRoomIdx();

        const int dimension =
            g_Game->GetDimension();

        const uint64_t roomGridSignature =
            ComputeRoomGridSignature(room);

        if (room == g_LastRoom &&
            roomIndex == g_LastRoomIndex &&
            dimension == g_LastDimension &&
            roomGridSignature == g_LastRoomGridSignature)
        {
            if (g_RoomModel.materials.size() > MAT_FLOOR)
            {
                RefreshIsaacFloorTexture(
                    room,
                    g_RoomModel.materials[MAT_FLOOR]);
            }

            return;
        }

        g_LastRoom = room;
        g_LastRoomIndex = roomIndex;
        g_LastDimension = dimension;
        g_LastRoomGridSignature = roomGridSignature;

        ResetRoomModel();

        LogMessage("RoomExtractor: Room changed.");

        LogRoom(room, roomIndex, dimension);
    }
}
