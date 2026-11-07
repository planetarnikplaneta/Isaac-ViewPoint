
#define NOMINMAX

#include <Windows.h>
#include <gl/GL.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "libzhl.h"
#include "HookSystem.h"

#pragma comment(lib, "opengl32.lib")

#ifndef GL_CURRENT_PROGRAM
#define GL_CURRENT_PROGRAM 0x8B8D
#endif

#ifndef GL_ACTIVE_TEXTURE
#define GL_ACTIVE_TEXTURE 0x84E0
#endif

#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif

using PFNGLUSEPROGRAMPROC = void (APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void (APIENTRY *)(GLenum);

struct Vector
{
    float x;
    float y;
};

struct ANM2;

class PlayerHUD
{
public:
    void RenderHearts(
        Vector* unk,
        ANM2* sprite,
        int playerHudLayout,
        float scale,
        Vector pos
    );

    char _padding[8];
    short _playerHudIndex;
};

namespace
{
    // --------------------------------------------------
    // Configuration
    // --------------------------------------------------

    constexpr float OBJECT_DISTANCE = 5.0f;
    constexpr float OBJECT_ROTATION_SPEED = 0.012f;
    constexpr float OBJECT_TILT = -12.0f;
    constexpr float OBJECT_FOV = 45.0f;

    constexpr float OBJECT_COLOR_R = 0.18f;
    constexpr float OBJECT_COLOR_G = 0.52f;
    constexpr float OBJECT_COLOR_B = 0.82f;

    // --------------------------------------------------
    // OBJ structures
    // --------------------------------------------------

    struct Vertex3
    {
        float x, y, z;
    };

    struct Triangle
    {
        uint32_t a, b, c;
    };

    // --------------------------------------------------
    // Global state
    // --------------------------------------------------

    static HMODULE g_Module = nullptr;

    static bool g_MeshLoaded = false;
    static bool g_ContextLogged = false;
    static bool g_RenderLogged = false;

    static HGLRC g_ResourceContext = nullptr;

    static PFNGLUSEPROGRAMPROC g_UseProgram = nullptr;
    static PFNGLACTIVETEXTUREPROC g_ActiveTexture = nullptr;

    static std::vector<Vertex3> g_Vertices;
    static std::vector<Triangle> g_Triangles;

    // --------------------------------------------------
    // Logging
    // --------------------------------------------------

    static void LogMessage(const char* message)
    {
        FILE* file = fopen("C:\\MyNativeMod.log", "a");

        if (file)
        {
            fprintf(file, "OBJ OpenGL: %s\n", message);
            fclose(file);
        }
    }

    // --------------------------------------------------
    // OpenGL function loading
    // --------------------------------------------------

    static PROC GetGLProc(const char* name)
    {
        PROC p = wglGetProcAddress(name);

        if (!p ||
            p == reinterpret_cast<PROC>(1) ||
            p == reinterpret_cast<PROC>(2) ||
            p == reinterpret_cast<PROC>(3) ||
            p == reinterpret_cast<PROC>(-1))
        {
            static HMODULE gl = GetModuleHandleA("opengl32.dll");

            p = gl ? GetProcAddress(gl, name) : nullptr;
        }

        return p;
    }

    static bool LoadGLFunctions()
    {
        g_UseProgram =
            reinterpret_cast<PFNGLUSEPROGRAMPROC>(
                GetGLProc("glUseProgram")
            );

        g_ActiveTexture =
            reinterpret_cast<PFNGLACTIVETEXTUREPROC>(
                GetGLProc("glActiveTexture")
            );

        if (!g_UseProgram)
        {
            LogMessage("glUseProgram unavailable");
            return false;
        }

        return true;
    }

    // --------------------------------------------------
    // OBJ path
    // --------------------------------------------------

    static std::string GetObjPath()
    {
        char modulePath[MAX_PATH] = {};

        DWORD len = GetModuleFileNameA(
            g_Module,
            modulePath,
            MAX_PATH
        );

        if (!len || len >= MAX_PATH)
            return "objectToRender.obj";

        std::string path(modulePath, len);

        size_t slash = path.find_last_of("\\/");

        if (slash != std::string::npos)
            path.resize(slash + 1);

        return path + "objectToRender.obj";
    }

    // --------------------------------------------------
    // OBJ index parsing
    // --------------------------------------------------

    static bool ParseObjIndex(
        const std::string& token,
        size_t count,
        uint32_t& out
    )
    {
        std::string text = token.substr(
            0,
            token.find('/')
        );

        if (text.empty())
            return false;

        char* end = nullptr;

        long value = strtol(text.c_str(), &end, 10);

        if (!end || *end || value == 0)
            return false;

        long resolved = value > 0
            ? value - 1
            : static_cast<long>(count) + value;

        if (resolved < 0 ||
            static_cast<size_t>(resolved) >= count)
        {
            return false;
        }

        out = static_cast<uint32_t>(resolved);

        return true;
    }

    // --------------------------------------------------
    // OBJ loading
    // --------------------------------------------------

    static void LoadOBJ()
    {
        const std::string path = GetObjPath();

        std::ifstream input(path);

        if (!input)
        {
            LogMessage("Cannot open objectToRender.obj beside DLL");
            return;
        }

        std::vector<Vertex3> source;
        std::vector<Triangle> faces;

        std::string line;

        while (std::getline(input, line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream stream(line);

            std::string type;
            stream >> type;

            // Vertices
            if (type == "v")
            {
                Vertex3 v{};

                if (stream >> v.x >> v.y >> v.z)
                    source.push_back(v);
            }

            // Faces
            else if (type == "f")
            {
                std::vector<uint32_t> face;

                std::string token;

                while (stream >> token)
                {
                    uint32_t index;

                    if (ParseObjIndex(token, source.size(), index))
                        face.push_back(index);
                }

                // Triangulate polygon.
                for (size_t i = 1; i + 1 < face.size(); ++i)
                {
                    faces.push_back({
                        face[0],
                        face[i],
                        face[i + 1]
                    });
                }
            }
        }

        if (source.empty() || faces.empty())
        {
            LogMessage("OBJ has no usable vertices/faces");
            return;
        }

        // Calculate bounding box.
        Vertex3 lo = source.front();
        Vertex3 hi = source.front();

        for (const Vertex3& v : source)
        {
            lo.x = std::min(lo.x, v.x);
            lo.y = std::min(lo.y, v.y);
            lo.z = std::min(lo.z, v.z);

            hi.x = std::max(hi.x, v.x);
            hi.y = std::max(hi.y, v.y);
            hi.z = std::max(hi.z, v.z);
        }

        // Center object.
        const float cx = (lo.x + hi.x) * 0.5f;
        const float cy = (lo.y + hi.y) * 0.5f;
        const float cz = (lo.z + hi.z) * 0.5f;

        // Normalize object size.
        const float scale = 2.0f / std::max({
            hi.x - lo.x,
            hi.y - lo.y,
            hi.z - lo.z,
            0.0001f
        });

        g_Vertices.clear();
        g_Vertices.reserve(source.size());

        for (const Vertex3& v : source)
        {
            g_Vertices.push_back({
                (v.x - cx) * scale,
                (v.y - cy) * scale,
                (v.z - cz) * scale
            });
        }

        g_Triangles = std::move(faces);

        g_MeshLoaded = true;

        char msg[160];

        snprintf(
            msg,
            sizeof(msg),
            "Loaded %zu vertices and %zu triangles",
            g_Vertices.size(),
            g_Triangles.size()
        );

        LogMessage(msg);
    }

    // --------------------------------------------------
    // Context initialization
    // --------------------------------------------------

    static bool EnsureContext()
    {
        HGLRC context = wglGetCurrentContext();

        if (!context)
            return false;

        if (context != g_ResourceContext)
        {
            g_ResourceContext = context;

            g_UseProgram = nullptr;
            g_ActiveTexture = nullptr;

            g_ContextLogged = false;

            LogMessage("OpenGL context changed");
        }

        return LoadGLFunctions();
    }

    // --------------------------------------------------
    // Mesh rendering
    // --------------------------------------------------

    void RenderTriangleMesh()
{
    GLint viewport[4] = { 0, 0, 0, 0 };
    GLint oldMatrixMode = GL_MODELVIEW;
    GLint oldProgram = 0;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);

    if (viewport[2] <= 0 || viewport[3] <= 0)
        return;

    if (glUseProgram)
    {
        glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
        glUseProgram(0);
    }

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glDisable(GL_COLOR_LOGIC_OP);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(
        0,
        viewport[2],
        0,
        viewport[3],
        -1,
        1
    );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw a large red rectangle in the center of the viewport.
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

    float centerX = viewport[2] * 0.5f;
    float centerY = viewport[3] * 0.5f;

    glBegin(GL_QUADS);
        glVertex2f(centerX - 100.0f, centerY - 100.0f);
        glVertex2f(centerX + 100.0f, centerY - 100.0f);
        glVertex2f(centerX + 100.0f, centerY + 100.0f);
        glVertex2f(centerX - 100.0f, centerY + 100.0f);
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();

    if (glUseProgram)
        glUseProgram(oldProgram);

    glMatrixMode(oldMatrixMode);
}

// --------------------------------------------------
// REPENTOGON hook
// --------------------------------------------------

HOOK_METHOD_PRIORITY(
    PlayerHUD,
    RenderHearts,
    100,
    (Vector* unk,
     ANM2* sprite,
     int playerHudLayout,
     float scale,
     Vector pos)
        -> void
)
{
    super(
        unk,
        sprite,
        playerHudLayout,
        scale,
        pos
    );

    if (_playerHudIndex == 0)
    {
        RenderTriangleMesh();
    }
}

// --------------------------------------------------
// DLL entry point
// --------------------------------------------------

BOOL WINAPI DllMain(
    HINSTANCE instance,
    DWORD reason,
    LPVOID
)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        g_Module = instance;

        DisableThreadLibraryCalls(instance);
    }

    return TRUE;
}

// --------------------------------------------------
// Mod initialization
// --------------------------------------------------

extern "C" __declspec(dllexport) int ModInit()
{
    return 0;
}
