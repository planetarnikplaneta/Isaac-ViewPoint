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
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "libzhl.h"
#include "HookSystem.h"

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

    KColor(float r = 1.0f, float g = 1.0f, float b = 1.0f,
           float a = 1.0f, int unk = 0)
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

// These are pointer-to-pointer imports from libzhl.def.
extern LIBZHL_API ShapeRenderer **__ptr_g_ShapeRenderer;
extern LIBZHL_API unsigned int *__ptr_g_WindowSizeX;
extern LIBZHL_API unsigned int *__ptr_g_WindowSizeY;

namespace
{
    struct Vertex3
    {
        float x;
        float y;
        float z;
    };

    struct Triangle
    {
        uint32_t a;
        uint32_t b;
        uint32_t c;
    };

    struct Edge
    {
        uint32_t a;
        uint32_t b;
    };

    struct CameraVertex
    {
        float x;
        float y;
        float z;
        float depth;
        Vector projected;
        bool valid;
    };

    struct DrawEdge
    {
        Edge edge;
        float depth;
    };

    static HMODULE g_Module = nullptr;
    static bool g_MeshLoaded = false;

    static std::vector<Vertex3> g_Vertices;
    static std::vector<Triangle> g_Triangles;

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
        const DWORD len = GetModuleFileNameA(g_Module, modulePath, MAX_PATH);

        if (len == 0 || len >= MAX_PATH)
            return "objectToRender.obj";

        std::string path(modulePath, len);
        const size_t slash = path.find_last_of("\\/");
        if (slash != std::string::npos)
            path.resize(slash + 1);

        return path + "objectToRender.obj";
    }

    static bool ParseObjIndex(
        const std::string &token,
        size_t vertexCount,
        uint32_t &out)
    {
        const size_t slash = token.find('/');
        const std::string indexText = token.substr(0, slash);

        if (indexText.empty())
            return false;

        char *end = nullptr;
        const long objIndex = strtol(indexText.c_str(), &end, 10);

        if (!end || *end != '\0' || objIndex == 0)
            return false;

        const long resolved = (objIndex > 0)
            ? objIndex - 1
            : static_cast<long>(vertexCount) + objIndex;

        if (resolved < 0 || static_cast<size_t>(resolved) >= vertexCount)
            return false;

        out = static_cast<uint32_t>(resolved);
        return true;
    }

    static uint64_t MakeEdgeKey(uint32_t a, uint32_t b)
    {
        const uint32_t lo = std::min(a, b);
        const uint32_t hi = std::max(a, b);
        return (static_cast<uint64_t>(lo) << 32) | hi;
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
        std::vector<Triangle> triangles;

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
                Vertex3 vertex{};
                if (ss >> vertex.x >> vertex.y >> vertex.z)
                    rawVertices.push_back(vertex);
            }
            else if (type == "f")
            {
                std::vector<uint32_t> faceVertices;
                std::string token;

                while (ss >> token)
                {
                    uint32_t index = 0;
                    if (ParseObjIndex(token, rawVertices.size(), index))
                        faceVertices.push_back(index);
                }

                // Triangulate polygon faces as a fan.
                for (size_t i = 1; i + 1 < faceVertices.size(); ++i)
                {
                    triangles.push_back({
                        faceVertices[0],
                        faceVertices[i],
                        faceVertices[i + 1]
                    });
                }
            }
        }

        if (rawVertices.empty() || triangles.empty())
        {
            LogMessage("OBJ contains no usable vertices/faces");
            return;
        }

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
        const float modelScale =
            2.5f / std::max({sx, sy, sz, 0.0001f});

        g_Vertices.clear();
        g_Vertices.reserve(rawVertices.size());

        for (const Vertex3 &v : rawVertices)
        {
            g_Vertices.push_back({
                (v.x - cx) * modelScale,
                (v.y - cy) * modelScale,
                (v.z - cz) * modelScale
            });
        }

        g_Triangles = std::move(triangles);
        g_MeshLoaded = true;

        char message[160];
        snprintf(
            message,
            sizeof(message),
            "loaded %zu vertices and %zu triangles",
            g_Vertices.size(),
            g_Triangles.size());
        LogMessage(message);
    }

    static void RenderOBJOverlay()
    {
        if (!__ptr_g_ShapeRenderer ||
            !__ptr_g_WindowSizeX ||
            !__ptr_g_WindowSizeY)
        {
            return;
        }

        ShapeRenderer *renderer = *__ptr_g_ShapeRenderer;
        if (!renderer)
            return;

        if (!g_MeshLoaded)
        {
            LoadOBJ();
            if (!g_MeshLoaded)
                return;
        }

        if (g_Vertices.empty() || g_Triangles.empty())
            return;

        const float width = static_cast<float>(*__ptr_g_WindowSizeX);
        const float height = static_cast<float>(*__ptr_g_WindowSizeY);

        if (width <= 0.0f || height <= 0.0f)
            return;

        const float angle =
            static_cast<float>(GetTickCount64()) * 0.0008f;

        const float c = std::cos(angle);
        const float s = std::sin(angle);

        const float pitch = -0.35f;
        const float pc = std::cos(pitch);
        const float ps = std::sin(pitch);

        // Transform and project every vertex once for this frame.
        std::vector<CameraVertex> cameraVertices;
        cameraVertices.reserve(g_Vertices.size());

        float minX = 0.0f;
        float maxX = 0.0f;
        float minY = 0.0f;
        float maxY = 0.0f;
        bool haveBounds = false;

        for (const Vertex3 &v : g_Vertices)
        {
            const float rx = v.x * c - v.z * s;
            const float rz = v.x * s + v.z * c;

            const float ry = v.y * pc - rz * ps;
            const float cameraZ = v.y * ps + rz * pc;
            const float depth = 5.0f + cameraZ;

            CameraVertex cv{};
            cv.x = rx;
            cv.y = ry;
            cv.z = cameraZ;
            cv.depth = depth;
            cv.valid = depth > 0.5f;

            if (cv.valid)
            {
                const float invDepth = 1.0f / depth;
                cv.projected = {
                    rx * invDepth,
                    -ry * invDepth
                };

                if (!haveBounds)
                {
                    minX = maxX = cv.projected.x;
                    minY = maxY = cv.projected.y;
                    haveBounds = true;
                }
                else
                {
                    minX = std::min(minX, cv.projected.x);
                    maxX = std::max(maxX, cv.projected.x);
                    minY = std::min(minY, cv.projected.y);
                    maxY = std::max(maxY, cv.projected.y);
                }
            }

            cameraVertices.push_back(cv);
        }

        if (!haveBounds)
            return;

        const float spanX = std::max(maxX - minX, 0.001f);
        const float spanY = std::max(maxY - minY, 0.001f);

        // Fit the projected model inside 70% of the window and center it.
        const float fitScale = std::min(
            width * 0.70f / spanX,
            height * 0.70f / spanY);

        const float offsetX =
            width * 0.5f - ((minX + maxX) * 0.5f * fitScale);
        const float offsetY =
            height * 0.5f - ((minY + maxY) * 0.5f * fitScale);

        // Collect unique edges belonging to front-facing triangles.
        // Camera is on the negative camera-Z side, so visible outward
        // normals point toward negative Z.
        std::unordered_map<uint64_t, float> visibleEdges;
        visibleEdges.reserve(g_Triangles.size() * 2);

        for (const Triangle &tri : g_Triangles)
        {
            if (tri.a >= cameraVertices.size() ||
                tri.b >= cameraVertices.size() ||
                tri.c >= cameraVertices.size())
            {
                continue;
            }

            const CameraVertex &a = cameraVertices[tri.a];
            const CameraVertex &b = cameraVertices[tri.b];
            const CameraVertex &d = cameraVertices[tri.c];

            if (!a.valid || !b.valid || !d.valid)
                continue;

            const float ux = b.x - a.x;
            const float uy = b.y - a.y;
            const float uz = b.z - a.z;

            const float vx = d.x - a.x;
            const float vy = d.y - a.y;
            const float vz = d.z - a.z;

            const float normalZ = ux * vy - uy * vx;

            // Back-face culling. If your OBJ uses reversed winding,
            // change this test to: normalZ <= 1.0e-8f
            if (normalZ >= -1.0e-8f)
                continue;

            const float triDepth = (a.depth + b.depth + d.depth) / 3.0f;

            const uint64_t keys[3] = {
                MakeEdgeKey(tri.a, tri.b),
                MakeEdgeKey(tri.b, tri.c),
                MakeEdgeKey(tri.c, tri.a)
            };

            for (const uint64_t key : keys)
            {
                auto it = visibleEdges.find(key);

                // Keep the nearer depth when an edge is shared by faces.
                if (it == visibleEdges.end())
                    visibleEdges.emplace(key, triDepth);
                else
                    it->second = std::min(it->second, triDepth);
            }
        }

        if (visibleEdges.empty())
            return;

        std::vector<DrawEdge> drawList;
        drawList.reserve(visibleEdges.size());

        for (const auto &entry : visibleEdges)
        {
            const uint32_t a = static_cast<uint32_t>(entry.first >> 32);
            const uint32_t b = static_cast<uint32_t>(entry.first & 0xffffffffu);
            drawList.push_back({{a, b}, entry.second});
        }

        // Painter-style depth order: far edges first, near edges last.
        std::sort(
            drawList.begin(),
            drawList.end(),
            [](const DrawEdge &lhs, const DrawEdge &rhs)
            {
                return lhs.depth > rhs.depth;
            });

        KColor color(0.35f, 0.85f, 1.0f, 1.0f);
        const float thickness = 1.1f;

        for (const DrawEdge &item : drawList)
        {
            const Edge &edge = item.edge;

            if (edge.a >= cameraVertices.size() ||
                edge.b >= cameraVertices.size())
            {
                continue;
            }

            const CameraVertex &a = cameraVertices[edge.a];
            const CameraVertex &b = cameraVertices[edge.b];

            if (!a.valid || !b.valid)
                continue;

            Vector p1 = {
                a.projected.x * fitScale + offsetX,
                a.projected.y * fitScale + offsetY
            };

            Vector p2 = {
                b.projected.x * fitScale + offsetX,
                b.projected.y * fitScale + offsetY
            };

            renderer->RenderLine(&p1, &p2, &color, &color, thickness);
        }
    }
}

HOOK_METHOD_PRIORITY(
    PlayerHUD,
    RenderHearts,
    100,
    (Vector *unk, ANM2 *sprite, int playerHudLayout, float scale, Vector pos)
        -> void)
{
    super(unk, sprite, playerHudLayout, scale, pos);

    if (_playerHudIndex == 0)
        RenderOBJOverlay();
}

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
