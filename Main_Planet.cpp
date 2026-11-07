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

#ifndef GL_FRAMEBUFFER_BINDING
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#endif

#ifndef GL_DRAW_BUFFER
#define GL_DRAW_BUFFER 0x0C01
#endif

using PFNGLUSEPROGRAMPROC = void (APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void (APIENTRY *)(GLenum);
using PFNGLCHECKFRAMEBUFFERSTATUSPROC = GLenum (APIENTRY *)(GLenum);

// --------------------------------------------------
// Game structures
// --------------------------------------------------

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
namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}
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
static PFNGLCHECKFRAMEBUFFERSTATUSPROC g_CheckFramebufferStatus = nullptr;

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

    static void CheckGLError(const char* stage)
    {
        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            char msg[256];

            snprintf(
                msg,
                sizeof(msg),
                "OpenGL error at %s: 0x%X",
                stage,
                error
            );

            LogMessage(msg);
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
g_CheckFramebufferStatus =
    reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(
        GetGLProc("glCheckFramebufferStatus")
    );
        if (g_CheckFramebufferStatus)
{
    GLenum status = g_CheckFramebufferStatus(0x8D40);

    char msg[128];

    snprintf(
        msg,
        sizeof(msg),
        "Framebuffer status: 0x%X",
        status
    );

    LogMessage(msg);
}
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

            if (type == "v")
            {
                Vertex3 v{};

                if (stream >> v.x >> v.y >> v.z)
                    source.push_back(v);
            }
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
    // Diagnostic marker
    // --------------------------------------------------

    static void RenderDiagnosticMarker()
    {
        // Save and replace projection matrix.
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        // Save and replace modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Disable states that could hide the marker.
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
        glDisable(GL_SCISSOR_TEST);

        glDisable(GL_ALPHA_TEST);
        glDisable(GL_STENCIL_TEST);

        // Magenta diagnostic square.
        glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);

        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f,  0.5f, 0.0f);
        glVertex3f(-0.5f,  0.5f, 0.0f);

        glEnd();

        // Restore modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        // Restore projection matrix.
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }

    // --------------------------------------------------
    // OBJ rendering
    // --------------------------------------------------
static void TestFramebufferPixel(const GLint* viewport)
{
    GLubyte pixel[4] = {};

    const GLint x = viewport[0] + viewport[2] / 2;
    const GLint y = viewport[1] + viewport[3] / 2;

    glReadPixels(
        x,
        y,
        1,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixel
    );

    GLenum error = glGetError();

    char msg[256];

    snprintf(
        msg,
        sizeof(msg),
        "Framebuffer center pixel: R=%u G=%u B=%u A=%u; GL error=0x%X",
        pixel[0],
        pixel[1],
        pixel[2],
        pixel[3],
        error
    );

    LogMessage(msg);
}
    static void RenderTriangleMesh()
    {
        if (!EnsureContext())
            return;

        // Clear errors from previous game rendering.
        while (glGetError() != GL_NO_ERROR)
        {
        }

        if (!g_MeshLoaded)
        {
            LoadOBJ();

            if (!g_MeshLoaded)
                return;
        }

        if (g_Vertices.empty() || g_Triangles.empty())
            return;

        // --------------------------------------------------
        // Save original OpenGL state
        // --------------------------------------------------

        GLint viewport[4] = {};

        GLint oldProgram = 0;
        GLint oldMatrixMode = GL_MODELVIEW;
        GLint oldActiveTexture = GL_TEXTURE0;

        GLint framebuffer = 0;
        GLint drawBuffer = 0;

        glGetIntegerv(GL_VIEWPORT, viewport);

        glGetIntegerv(
            GL_CURRENT_PROGRAM,
            &oldProgram
        );

        glGetIntegerv(
            GL_MATRIX_MODE,
            &oldMatrixMode
        );

        // Validate original matrix mode.
        if (oldMatrixMode != GL_MODELVIEW &&
            oldMatrixMode != GL_PROJECTION &&
            oldMatrixMode != GL_TEXTURE)
        {
            LogMessage("Invalid original matrix mode; using GL_MODELVIEW");

            oldMatrixMode = GL_MODELVIEW;
        }

        // Validate viewport before changing other state.
        if (viewport[2] <= 0 || viewport[3] <= 0)
        {
            LogMessage("Invalid viewport");
            return;
        }

        if (g_ActiveTexture)
        {
            glGetIntegerv(
                GL_ACTIVE_TEXTURE,
                &oldActiveTexture
            );
        }

        glGetIntegerv(
            GL_FRAMEBUFFER_BINDING,
            &framebuffer
        );

        glGetIntegerv(
            GL_DRAW_BUFFER,
            &drawBuffer
        );

        char framebufferMsg[256];

        snprintf(
            framebufferMsg,
            sizeof(framebufferMsg),
            "Framebuffer: %d, draw buffer: 0x%X",
            framebuffer,
            drawBuffer
        );

        LogMessage(framebufferMsg);

        // --------------------------------------------------
        // Context information
        // --------------------------------------------------

        if (!g_ContextLogged)
        {
            const GLubyte* version = glGetString(GL_VERSION);
            const GLubyte* renderer = glGetString(GL_RENDERER);

            char msg[512];

            snprintf(
                msg,
                sizeof(msg),
                "GL %s / %s; viewport %dx%d",
                version
                    ? reinterpret_cast<const char*>(version)
                    : "unknown",
                renderer
                    ? reinterpret_cast<const char*>(renderer)
                    : "unknown",
                viewport[2],
                viewport[3]
            );

            LogMessage(msg);

            g_ContextLogged = true;
        }

        // --------------------------------------------------
        // Save attributes and matrices
        // --------------------------------------------------

        glPushAttrib(GL_ALL_ATTRIB_BITS);

        if (g_ActiveTexture)
            g_ActiveTexture(GL_TEXTURE0);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // --------------------------------------------------
        // Disable game rendering states
        // --------------------------------------------------

        g_UseProgram(0);

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
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glColorMask(
            GL_TRUE,
            GL_TRUE,
            GL_TRUE,
            GL_TRUE
        );

        // --------------------------------------------------
        // Projection
        // --------------------------------------------------

        const float aspect =
            static_cast<float>(viewport[2]) /
            static_cast<float>(viewport[3]);

        const double nearPlane = 0.1;

        const double halfHeight =
            nearPlane * std::tan(
                OBJECT_FOV * 3.14159265358979323846 / 360.0
            );

        const double halfWidth = halfHeight * aspect;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glFrustum(
            -halfWidth,
            halfWidth,
            -halfHeight,
            halfHeight,
            nearPlane,
            100.0
        );

        // --------------------------------------------------
        // Model transformation
        // --------------------------------------------------

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(
            0.0f,
            0.0f,
            -OBJECT_DISTANCE
        );

        glRotatef(
            OBJECT_TILT,
            1.0f,
            0.0f,
            0.0f
        );

        glRotatef(
            static_cast<float>(GetTickCount64()) *
                OBJECT_ROTATION_SPEED,
            0.0f,
            1.0f,
            0.0f
        );

        // --------------------------------------------------
        // Render OBJ
        // --------------------------------------------------

        if (!g_RenderLogged)
        {
            LogMessage("Rendering mesh directly to game framebuffer");
            g_RenderLogged = true;
        }

        glBegin(GL_TRIANGLES);

        for (const Triangle& t : g_Triangles)
        {
            if (t.a >= g_Vertices.size() ||
                t.b >= g_Vertices.size() ||
                t.c >= g_Vertices.size())
            {
                continue;
            }

            const Vertex3& a = g_Vertices[t.a];
            const Vertex3& b = g_Vertices[t.b];
            const Vertex3& c = g_Vertices[t.c];

            // Calculate face normal.
            const float ux = b.x - a.x;
            const float uy = b.y - a.y;
            const float uz = b.z - a.z;

            const float vx = c.x - a.x;
            const float vy = c.y - a.y;
            const float vz = c.z - a.z;

            float nx = uy * vz - uz * vy;
            float ny = uz * vx - ux * vz;
            float nz = ux * vy - uy * vx;

            const float length =
                std::sqrt(nx * nx + ny * ny + nz * nz);

            if (length < 1e-8f)
                continue;

            nx /= length;
            ny /= length;
            nz /= length;

            // Directional lighting.
            const float lx = -0.35f;
            const float ly = 0.55f;
            const float lz = -0.76f;

            const float lightLength =
                std::sqrt(lx * lx + ly * ly + lz * lz);

            const float diffuse = std::max(
                0.0f,
                (nx * lx + ny * ly + nz * lz) / lightLength
            );

            const float brightness =
                0.25f + 0.75f * diffuse;

            glColor4f(
                OBJECT_COLOR_R * brightness,
                OBJECT_COLOR_G * brightness,
                OBJECT_COLOR_B * brightness,
                1.0f
            );

            glNormal3f(nx, ny, nz);

            glVertex3f(a.x, a.y, a.z);
            glVertex3f(b.x, b.y, b.z);
            glVertex3f(c.x, c.y, c.z);
        }

        glEnd();

        CheckGLError("after OBJ rendering");

        // --------------------------------------------------
        // Draw diagnostic marker
        // --------------------------------------------------

RenderDiagnosticMarker();

CheckGLError("after diagnostic marker");

TestFramebufferPixel(viewport);

        

        // --------------------------------------------------
        // Restore matrices
        // --------------------------------------------------

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        // Restore OpenGL attributes.
        glPopAttrib();

        // Restore shader program.
        g_UseProgram(
            static_cast<GLuint>(oldProgram)
        );

        // Restore active texture.
        if (g_ActiveTexture)
        {
            g_ActiveTexture(
                static_cast<GLenum>(oldActiveTexture)
            );
        }

        // Restore original matrix mode.
        glMatrixMode(
            static_cast<GLenum>(oldMatrixMode)
        );

        CheckGLError("after restoring OpenGL state");
    }
}

// --------------------------------------------------
// REPENTOGON hook
// --------------------------------------------------

HOOK_GLOBAL(OpenGL::wglSwapBuffers, (HDC hdc)->bool, __stdcall)
{
    static unsigned int swapCount = 0;

    GLint viewport[4] = {};
    GLint framebuffer = -1;
    GLint drawBuffer = -1;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);

    char msg[256];

    snprintf(
        msg,
        sizeof(msg),
        "SWAP #%u | HDC=%p | FBO=%d | DRAW=0x%X | VIEWPORT=%dx%d",
        swapCount,
        static_cast<void*>(hdc),
        framebuffer,
        drawBuffer,
        viewport[2],
        viewport[3]
    );

    LogMessage(msg);

    ++swapCount;

    return super(hdc);
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
    LogMessage("ModInit called");
    return 0;
}
