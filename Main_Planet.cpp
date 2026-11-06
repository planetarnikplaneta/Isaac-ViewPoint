#define NOMINMAX
#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "libzhl.h"
#include "HookSystem.h"

// -----------------------------------------------------------------------------
// Minimal engine types
// -----------------------------------------------------------------------------

struct Vector
{
    float x;
    float y;
};

struct KColor
{
    float _red;
    float _green;
    float _blue;
    float _alpha;
    int _unk;

    KColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f, int unk = 0)
        : _red(r), _green(g), _blue(b), _alpha(a), _unk(unk)
    {
    }
};

struct ANM2;

class PlayerHUD
{
public:
    void RenderHearts(
        Vector *unk,
        ANM2 *sprite,
        int playerHudLayout,
        float scale,
        Vector pos);

    char _padding[8];
    short _playerHudIndex;
};

struct ShapeRenderer
{
    LIBZHL_API int RenderLine(
        Vector *pos1,
        Vector *pos2,
        KColor *col1,
        KColor *col2,
        const float &thickness);
};

extern LIBZHL_API ShapeRenderer **__ptr_g_ShapeRenderer;
extern LIBZHL_API unsigned int *__ptr_g_WindowSizeX;
extern LIBZHL_API unsigned int *__ptr_g_WindowSizeY;

// -----------------------------------------------------------------------------
// OBJ mesh data
// -----------------------------------------------------------------------------

namespace
{
    struct Vertex3
    {
        float x;
        float y;
        float z;
    };

    struct Edge
    {
        uint32_t a;
        uint32_t b;
    };

    static HMODULE g_Module = nullptr;

    static bool g_MeshLoaded = false;
    static std::vector<Vertex3> g_Vertices;
    static std::vector<Edge> g_Edges;

    static void LogMessage(const char *message)
    {
        FILE *file = fopen("C:\\MyNativeMod.log", "a");
        if (!file)
            return;

        fprintf(file, "OBJ overlay: %s\n", message);
        fclose(file);
    }

    static std::string GetObjPath()
    {
        char modulePath[MAX_PATH] = {};
        DWORD len = GetModuleFileNameA(g_Module, modulePath, MAX_PATH);
        if (len == 0 || len >= MAX_PATH)
            return "objectToRender.obj";

        std::string path(modulePath, len);
        const size_t slash = path.find_last_of("\\/");
        if (slash != std::string::npos)
            path.resize(slash + 1);

        return path + "objectToRender.obj";
    }

    static bool ParseObjIndex(const std::string &token, size_t vertexCount, uint32_t &out)
    {
        const size_t slash = token.find('/');
        const std::string indexText = token.substr(0, slash);

        if (indexText.empty())
            return false;

        char *end = nullptr;
        const long vIndex = strtol(indexText.c_str(), &end, 10);

        if (!end || *end != '\0' || vIndex == 0)
            return false;

        const long resolved = (vIndex > 0)
            ? (vIndex - 1)
            : static_cast<long>(vertexCount) + vIndex;

        if (resolved < 0 || static_cast<size_t>(resolved) >= vertexCount)
            return false;

        out = static_cast<uint32_t>(resolved);
        return true;
    }

    static void LoadOBJ()
    {
        const std::string path = GetObjPath();
        std::ifstream input(path);
        if (!input)
        {
            LogMessage("could not open objectToRender.obj");
            return;
        }

        std::vector<Vertex3> rawVertices;
        std::vector<uint32_t> faceIndices;
        std::unordered_set<uint64_t> uniqueEdges;

        std::string line;
        while (std::getline(input, line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream ss(line);
            std::string type;
            ss >> type;

            if (type == "v")
            {
                Vertex3 v{};
                if (ss >> v.x >> v.y >> v.z)
                    rawVertices.push_back(v);
            }
            else if (type == "f")
            {
                std::vector<uint32_t> faceVerts;
                std::string tok;

                while (ss >> tok)
                {
                    uint32_t idx = 0;
                    if (!ParseObjIndex(tok, rawVertices.size(), idx))
                        continue;

                    faceVerts.push_back(idx);
                }

                if (faceVerts.size() >= 3)
                {
                    for (size_t i = 0; i < faceVerts.size(); ++i)
                    {
                        const uint32_t a = faceVerts[i];
                        const uint32_t b = faceVerts[(i + 1) % faceVerts.size()];

                        if (a == b)
                            continue;

                        const uint32_t lo = std::min(a, b);
                        const uint32_t hi = std::max(a, b);
                        const uint64_t key = (static_cast<uint64_t>(lo) << 32) | hi;

                        uniqueEdges.insert(key);
                    }
                }
            }
        }

        if (rawVertices.empty() || uniqueEdges.empty())
        {
            LogMessage("OBJ contains no usable vertices/faces");
            return;
        }

        // Center and scale the model to a nice screen-space size.
        Vertex3 minV = rawVertices.front();
        Vertex3 maxV = rawVertices.front();
        for (const Vertex3 &v : rawVertices)
        {
            minV.x = std::min(minV.x, v.x);
            minV.y = std::min(minV.y, v.y);
            minV.z = std::min(minV.z, v.z);

            maxV.x = std::max(maxV.x, v.x);
            maxV.y = std::max(maxV.y, v.y);
            maxV.z = std::max(maxV.z, v.z);
        }

        const float cx = (minV.x + maxV.x) * 0.5f;
        const float cy = (minV.y + maxV.y) * 0.5f;
        const float cz = (minV.z + maxV.z) * 0.5f;

        const float sx = maxV.x - minV.x;
        const float sy = maxV.y - minV.y;
        const float sz = maxV.z - minV.z;
        const float scale = 2.5f / std::max({ sx, sy, sz, 0.0001f });

        g_Vertices.clear();
        g_Vertices.reserve(rawVertices.size());
        for (const Vertex3 &v : rawVertices)
        {
            g_Vertices.push_back({
                (v.x - cx) * scale,
                (v.y - cy) * scale,
                (v.z - cz) * scale
            });
        }

        g_Edges.clear();
        g_Edges.reserve(uniqueEdges.size());
        for (const uint64_t key : uniqueEdges)
        {
            g_Edges.push_back({
                static_cast<uint32_t>(key >> 32),
                static_cast<uint32_t>(key & 0xffffffffu)
            });
        }

        g_MeshLoaded = true;

        char temp[160];
        snprintf(temp, sizeof(temp), "loaded %zu vertices and %zu edges", g_Vertices.size(), g_Edges.size());
        LogMessage(temp);
    }

    static Vector Project3D(const Vertex3 &v, float angle, float centerX, float centerY, float focalLength)
    {
        // Simple rotation around Y, plus a slight pitch tilt.
        const float c = std::cos(angle);
        const float s = std::sin(angle);

        const float rx = v.x * c - v.z * s;
        const float rz = v.x * s + v.z * c;

        const float pitch = -0.35f;
        const float pc = std::cos(pitch);
        const float ps = std::sin(pitch);

        const float ry = v.y * pc - rz * ps;
        const float depth = 5.0f + (v.y * ps + rz * pc);

        const float safeDepth = std::max(0.5f, depth);
        const float perspective = focalLength / safeDepth;

        return {
            centerX + rx * perspective,
            centerY - ry * perspective
        };
    }

static void RenderOBJOverlay()
{
    if (!__ptr_g_ShapeRenderer || !__ptr_g_WindowSizeX || !__ptr_g_WindowSizeY)
        return;

    ShapeRenderer *renderer = *__ptr_g_ShapeRenderer;
    if (!renderer)
        return;

    if (!g_MeshLoaded)
    {
        LoadOBJ();
        if (!g_MeshLoaded)
            return;
    }

    if (g_Vertices.empty() || g_Edges.empty())
        return;

    const float width = static_cast<float>(*__ptr_g_WindowSizeX);
    const float height = static_cast<float>(*__ptr_g_WindowSizeY);

    if (width <= 0.0f || height <= 0.0f)
        return;

    const float centerX = width * 0.5f;
    const float centerY = height * 0.5f;
    const float focalLength = std::min(width, height) * 0.70f;
    const float angle = static_cast<float>(GetTickCount64()) * 0.0008f;

    KColor color(0.35f, 0.85f, 1.0f, 1.0f);
    const float thickness = 1.1f;

    const size_t maxDraws = 256;
    const size_t step = std::max<size_t>(1, g_Edges.size() / maxDraws);

    for (size_t i = 0; i < g_Edges.size(); i += step)
    {
        const Edge &edge = g_Edges[i];
        if (edge.a >= g_Vertices.size() || edge.b >= g_Vertices.size())
            continue;

        Vector p1 = Project3D(g_Vertices[edge.a], angle, centerX, centerY, focalLength);
        Vector p2 = Project3D(g_Vertices[edge.b], angle, centerX, centerY, focalLength);

        renderer->RenderLine(&p1, &p2, &color, &color, thickness);
    }
}
}

// -----------------------------------------------------------------------------
// Hook: render the OBJ as a screen overlay after inventory/heart HUD draws
// -----------------------------------------------------------------------------

HOOK_METHOD_PRIORITY(
    PlayerHUD,
    RenderHearts,
    100,
    (Vector *unk, ANM2 *sprite, int playerHudLayout, float scale, Vector pos)
        -> void)
{
    super(unk, sprite, playerHudLayout, scale, pos);

    // This keeps it from drawing once per player instance.
    // if you want it on every HUD, remove this check.
    if (_playerHudIndex == 0)
        RenderOBJOverlay();
}

// -----------------------------------------------------------------------------
// Entry points
// -----------------------------------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        g_Module = instance;
        DisableThreadLibraryCalls(instance);
    }
    return TRUE;
}

extern "C" __declspec(dllexport) int ModInit()
{
    return 0;
}
