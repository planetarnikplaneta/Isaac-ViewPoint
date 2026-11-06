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

// libzhl.def exports pointer-reference symbols for these engine globals.
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

    struct CameraVertex
    {
        float x;
        float y;
        float z;
        float depth;
        float screenX;
        float screenY;
        bool valid;
    };

    static HMODULE g_Module = nullptr;
    static bool g_MeshLoaded = false;
    static std::vector<Vertex3> g_Vertices;
    static std::vector<Triangle> g_Triangles;

    // Reused each frame to avoid repeatedly allocating the software depth/color buffers.
    static std::vector<float> g_DepthBuffer;
    static std::vector<uint8_t> g_ShadeBuffer;
    static std::vector<CameraVertex> g_CameraVertices;

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

        // Fixed model normalization. This scale does not change while rotating.
        const float modelScale = 3.0f / std::max({sx, sy, sz, 0.0001f});

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

    static float EdgeFunction(float ax, float ay, float bx, float by, float px, float py)
    {
        return (px - ax) * (by - ay) - (py - ay) * (bx - ax);
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

        const int width = static_cast<int>(*__ptr_g_WindowSizeX);
        const int height = static_cast<int>(*__ptr_g_WindowSizeY);
        if (width <= 0 || height <= 0 || width > 8192 || height > 8192)
            return;

        const size_t pixelCount = static_cast<size_t>(width) * static_cast<size_t>(height);
        g_DepthBuffer.assign(pixelCount, 0.0f);
        g_ShadeBuffer.assign(pixelCount, 0);
        g_CameraVertices.resize(g_Vertices.size());

        // Constant rotation speed and fixed scale prevent the model from pulsing
        // or shifting as its projected bounds change.
        const float seconds = static_cast<float>(GetTickCount64()) * 0.001f;
        const float angle = seconds * 0.25f;
        const float c = std::cos(angle);
        const float s = std::sin(angle);
        const float pitch = -0.25f;
        const float pc = std::cos(pitch);
        const float ps = std::sin(pitch);

        const float focalLength = static_cast<float>(std::min(width, height)) * 0.85f;
        const float cameraDistance = 5.0f;
        const float centerX = static_cast<float>(width) * 0.5f;
        const float centerY = static_cast<float>(height) * 0.5f;

        for (size_t i = 0; i < g_Vertices.size(); ++i)
        {
            const Vertex3 &v = g_Vertices[i];
            const float rx = v.x * c - v.z * s;
            const float rz = v.x * s + v.z * c;
            const float ry = v.y * pc - rz * ps;
            const float cameraZ = v.y * ps + rz * pc;
            const float depth = cameraDistance + cameraZ;

            CameraVertex cv{};
            cv.x = rx;
            cv.y = ry;
            cv.z = cameraZ;
            cv.depth = depth;
            cv.valid = depth > 0.1f;

            if (cv.valid)
            {
                const float perspective = focalLength / depth;
                cv.screenX = centerX + rx * perspective;
                cv.screenY = centerY - ry * perspective;
            }

            g_CameraVertices[i] = cv;
        }

        // Camera-space directional light, facing generally toward the camera.
        float lightX = -0.35f;
        float lightY = 0.55f;
        float lightZ = -0.76f;
        const float lightLength = std::sqrt(lightX * lightX + lightY * lightY + lightZ * lightZ);
        lightX /= lightLength;
        lightY /= lightLength;
        lightZ /= lightLength;

        // Software rasterize filled triangles with a per-pixel depth buffer.
        // This performs hidden-surface removal without drawing the rear surfaces.
        for (const Triangle &tri : g_Triangles)
        {
            if (tri.a >= g_CameraVertices.size() ||
                tri.b >= g_CameraVertices.size() ||
                tri.c >= g_CameraVertices.size())
            {
                continue;
            }

            const CameraVertex &a = g_CameraVertices[tri.a];
            const CameraVertex &b = g_CameraVertices[tri.b];
            const CameraVertex &d = g_CameraVertices[tri.c];
            if (!a.valid || !b.valid || !d.valid)
                continue;

            const float area = EdgeFunction(
                a.screenX, a.screenY,
                b.screenX, b.screenY,
                d.screenX, d.screenY);
            if (std::fabs(area) < 1.0e-6f)
                continue;

            const int minX = std::max(0, static_cast<int>(std::floor(
                std::min({a.screenX, b.screenX, d.screenX}))));
            const int maxX = std::min(width - 1, static_cast<int>(std::ceil(
                std::max({a.screenX, b.screenX, d.screenX}))));
            const int minY = std::max(0, static_cast<int>(std::floor(
                std::min({a.screenY, b.screenY, d.screenY}))));
            const int maxY = std::min(height - 1, static_cast<int>(std::ceil(
                std::max({a.screenY, b.screenY, d.screenY}))));

            if (minX > maxX || minY > maxY)
                continue;

            // Flat diffuse lighting per triangle. Flip the normal toward the
            // camera so inconsistent OBJ winding does not make faces vanish.
            const float abx = b.x - a.x;
            const float aby = b.y - a.y;
            const float abz = b.z - a.z;
            const float acx = d.x - a.x;
            const float acy = d.y - a.y;
            const float acz = d.z - a.z;

            float nx = aby * acz - abz * acy;
            float ny = abz * acx - abx * acz;
            float nz = abx * acy - aby * acx;
            float normalLength = std::sqrt(nx * nx + ny * ny + nz * nz);
            if (normalLength < 1.0e-8f)
                continue;

            nx /= normalLength;
            ny /= normalLength;
            nz /= normalLength;

            if (nz > 0.0f)
            {
                nx = -nx;
                ny = -ny;
                nz = -nz;
            }

            const float diffuse = std::max(0.0f, nx * lightX + ny * lightY + nz * lightZ);
            const float brightness = 0.22f + 0.78f * diffuse;
            const uint8_t shade = static_cast<uint8_t>(
                std::max(1.0f, std::min(15.0f, std::round(brightness * 15.0f))));

            const float invArea = 1.0f / area;

            for (int y = minY; y <= maxY; ++y)
            {
                const float py = static_cast<float>(y) + 0.5f;
                const size_t rowOffset = static_cast<size_t>(y) * static_cast<size_t>(width);

                for (int x = minX; x <= maxX; ++x)
                {
                    const float px = static_cast<float>(x) + 0.5f;
                    const float w0 = EdgeFunction(
                        b.screenX, b.screenY,
                        d.screenX, d.screenY,
                        px, py) * invArea;
                    const float w1 = EdgeFunction(
                        d.screenX, d.screenY,
                        a.screenX, a.screenY,
                        px, py) * invArea;
                    const float w2 = 1.0f - w0 - w1;

                    if (w0 < 0.0f || w1 < 0.0f || w2 < 0.0f)
                        continue;

                    // Interpolate reciprocal depth for perspective-correct visibility.
                    const float invDepth = w0 / a.depth + w1 / b.depth + w2 / d.depth;
                    const size_t pixel = rowOffset + static_cast<size_t>(x);

                    if (invDepth > g_DepthBuffer[pixel])
                    {
                        g_DepthBuffer[pixel] = invDepth;
                        g_ShadeBuffer[pixel] = shade;
                    }
                }
            }
        }

        // Draw horizontal runs of equally shaded pixels. This uses the engine's
        // existing line primitive to display the software-filled/depth-tested image.
        KColor shades[16];
        for (int i = 0; i < 16; ++i)
        {
            const float t = static_cast<float>(i) / 15.0f;
            shades[i] = KColor(0.10f + 0.20f * t,
                               0.28f + 0.62f * t,
                               0.38f + 0.62f * t,
                               1.0f);
        }

        const float lineThickness = 1.2f;
        for (int y = 0; y < height; ++y)
        {
            const size_t rowOffset = static_cast<size_t>(y) * static_cast<size_t>(width);
            int x = 0;

            while (x < width)
            {
                const uint8_t shade = g_ShadeBuffer[rowOffset + static_cast<size_t>(x)];
                if (shade == 0)
                {
                    ++x;
                    continue;
                }

                const int startX = x;
                while (x + 1 < width &&
                       g_ShadeBuffer[rowOffset + static_cast<size_t>(x + 1)] == shade)
                {
                    ++x;
                }

                Vector p1 = {static_cast<float>(startX) + 0.5f,
                             static_cast<float>(y) + 0.5f};
                Vector p2 = {static_cast<float>(x) + 0.5f,
                             static_cast<float>(y) + 0.5f};

                renderer->RenderLine(&p1, &p2, &shades[shade], &shades[shade], lineThickness);
                ++x;
            }
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
