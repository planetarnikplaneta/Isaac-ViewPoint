
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

#ifndef GL_TEXTURE_BINDING_2D
#define GL_TEXTURE_BINDING_2D 0x8069
#endif

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

using PFNGLUSEPROGRAMPROC = void (APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void (APIENTRY *)(GLenum);

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

    constexpr float OBJECT_COLOR_R = 1.0f;
    constexpr float OBJECT_COLOR_G = 1.0f;
    constexpr float OBJECT_COLOR_B = 1.0f;

    constexpr float AMBIENT_LIGHT = 0.40f;
    constexpr float DIFFUSE_LIGHT = 0.60f;

    constexpr float LIGHT_X = -0.35f;
    constexpr float LIGHT_Y = 0.55f;
    constexpr float LIGHT_Z = -0.76f;

    // --------------------------------------------------
    // OBJ structures
    // --------------------------------------------------

    struct Vertex3
    {
        float x, y, z;
    };

    struct Vertex2
    {
        float u, v;
    };

    struct ObjCorner
    {
        uint32_t position;
        int32_t texcoord;
        int32_t normal;
    };

    struct Triangle
    {
        ObjCorner corners[3];
    };

    // --------------------------------------------------
    // Global state
    // --------------------------------------------------

    static HMODULE g_Module = nullptr;

    static bool g_MeshAttempted = false;
    static bool g_MeshLoaded = false;

    static bool g_TextureAttempted = false;
    static bool g_TextureLoaded = false;

    static HGLRC g_ResourceContext = nullptr;

    static PFNGLUSEPROGRAMPROC g_UseProgram = nullptr;
    static PFNGLACTIVETEXTUREPROC g_ActiveTexture = nullptr;

    static GLuint g_TextureId = 0;

    static int g_TextureWidth = 0;
    static int g_TextureHeight = 0;
    static unsigned char* g_TexturePixels = nullptr;

    static std::vector<Vertex3> g_Vertices;
    static std::vector<Vertex2> g_Texcoords;
    static std::vector<Vertex3> g_Normals;
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
    // File paths
    // --------------------------------------------------

    static std::string GetFilePath(const char* filename)
    {
        char modulePath[MAX_PATH] = {};

        DWORD len = GetModuleFileNameA(
            g_Module,
            modulePath,
            MAX_PATH
        );

        if (!len || len >= MAX_PATH)
            return filename;

        std::string path(modulePath, len);

        size_t slash = path.find_last_of("\\/");

        if (slash != std::string::npos)
            path.resize(slash + 1);

        return path + filename;
    }

    // --------------------------------------------------
    // OBJ index parsing
    // --------------------------------------------------

    // component:
    // 0 = position
    // 1 = texture coordinate
    // 2 = normal

    static bool ParseObjIndex(
        const std::string& token,
        int component,
        size_t count,
        int32_t& out
    )
    {
        size_t start = 0;

        for (int i = 0; i < component; ++i)
        {
            size_t slash = token.find('/', start);

            if (slash == std::string::npos)
                return false;

            start = slash + 1;
        }

        size_t end = token.find('/', start);

        if (end == std::string::npos)
            end = token.size();

        if (start >= end)
            return false;

        const std::string text = token.substr(
            start,
            end - start
        );

        char* parseEnd = nullptr;

        long value = strtol(text.c_str(), &parseEnd, 10);

        if (!parseEnd || *parseEnd || value == 0)
            return false;

        long resolved = value > 0
            ? value - 1
            : static_cast<long>(count) + value;

        if (resolved < 0 ||
            static_cast<size_t>(resolved) >= count)
        {
            return false;
        }

        out = static_cast<int32_t>(resolved);

        return true;
    }

    // --------------------------------------------------
    // OBJ loading
    // --------------------------------------------------

    static void LoadOBJ()
    {
        g_MeshAttempted = true;

        const std::string path = GetFilePath(
            "objectToRender.obj"
        );

        std::ifstream input(path);

        if (!input)
        {
            LogMessage("Cannot open objectToRender.obj beside DLL");
            return;
        }

        std::vector<Vertex3> sourceVertices;
        std::vector<Vertex2> sourceTexcoords;
        std::vector<Vertex3> sourceNormals;
        std::vector<Triangle> faces;

        std::string line;

        while (std::getline(input, line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream stream(line);

            std::string type;
            stream >> type;

            // ------------------------------------------
            // Positions
            // ------------------------------------------

            if (type == "v")
            {
                Vertex3 vertex{};

                if (stream >> vertex.x >> vertex.y >> vertex.z)
                    sourceVertices.push_back(vertex);
            }

            // ------------------------------------------
            // Texture coordinates
            // ------------------------------------------

            else if (type == "vt")
            {
                Vertex2 texcoord{};

                if (stream >> texcoord.u >> texcoord.v)
                    sourceTexcoords.push_back(texcoord);
            }

            // ------------------------------------------
            // Normals
            // ------------------------------------------

            else if (type == "vn")
            {
                Vertex3 normal{};

                if (stream >> normal.x >> normal.y >> normal.z)
                    sourceNormals.push_back(normal);
            }

            // ------------------------------------------
            // Faces
            // ------------------------------------------

            else if (type == "f")
            {
                std::vector<ObjCorner> face;

                std::string token;

                while (stream >> token)
                {
                    ObjCorner corner{};

                    int32_t position = -1;
                    int32_t texcoord = -1;
                    int32_t normal = -1;

                    if (!ParseObjIndex(
                        token,
                        0,
                        sourceVertices.size(),
                        position))
                    {
                        continue;
                    }

                    ParseObjIndex(
                        token,
                        1,
                        sourceTexcoords.size(),
                        texcoord
                    );

                    ParseObjIndex(
                        token,
                        2,
                        sourceNormals.size(),
                        normal
                    );

                    corner.position =
                        static_cast<uint32_t>(position);

                    corner.texcoord = texcoord;
                    corner.normal = normal;

                    face.push_back(corner);
                }

                // Fan triangulation.
                for (size_t i = 1; i + 1 < face.size(); ++i)
                {
                    Triangle triangle{};

                    triangle.corners[0] = face[0];
                    triangle.corners[1] = face[i];
                    triangle.corners[2] = face[i + 1];

                    faces.push_back(triangle);
                }
            }
        }

        if (sourceVertices.empty() || faces.empty())
        {
            LogMessage("OBJ has no usable vertices or faces");
            return;
        }

        // ----------------------------------------------
        // Calculate bounding box
        // ----------------------------------------------

        Vertex3 lo = sourceVertices.front();
        Vertex3 hi = sourceVertices.front();

        for (const Vertex3& v : sourceVertices)
        {
            lo.x = std::min(lo.x, v.x);
            lo.y = std::min(lo.y, v.y);
            lo.z = std::min(lo.z, v.z);

            hi.x = std::max(hi.x, v.x);
            hi.y = std::max(hi.y, v.y);
            hi.z = std::max(hi.z, v.z);
        }

        // ----------------------------------------------
        // Center and normalize model
        // ----------------------------------------------

        const float cx = (lo.x + hi.x) * 0.5f;
        const float cy = (lo.y + hi.y) * 0.5f;
        const float cz = (lo.z + hi.z) * 0.5f;

        const float scale = 2.0f / std::max({
            hi.x - lo.x,
            hi.y - lo.y,
            hi.z - lo.z,
            0.0001f
        });

        g_Vertices.clear();
        g_Vertices.reserve(sourceVertices.size());

        for (const Vertex3& v : sourceVertices)
        {
            g_Vertices.push_back({
                (v.x - cx) * scale,
                (v.y - cy) * scale,
                (v.z - cz) * scale
            });
        }

        g_Texcoords = std::move(sourceTexcoords);
        g_Normals = std::move(sourceNormals);
        g_Triangles = std::move(faces);

        g_MeshLoaded = true;

        char msg[256];

        snprintf(
            msg,
            sizeof(msg),
            "Loaded OBJ: %zu positions, %zu UVs, %zu normals, %zu triangles",
            g_Vertices.size(),
            g_Texcoords.size(),
            g_Normals.size(),
            g_Triangles.size()
        );

        LogMessage(msg);
    }

    // --------------------------------------------------
    // PNG loading
    // --------------------------------------------------

    static void LoadPNG()
    {
        g_TextureAttempted = true;

        const std::string path = GetFilePath(
            "objectToRender.png"
        );

        // OBJ UV coordinates use a bottom-left origin.
        stbi_set_flip_vertically_on_load(1);

        g_TexturePixels = stbi_load(
            path.c_str(),
            &g_TextureWidth,
            &g_TextureHeight,
            nullptr,
            4
        );

        if (!g_TexturePixels)
        {
            LogMessage("Cannot load objectToRender.png");
            return;
        }

        g_TextureLoaded = true;

        char msg[192];

        snprintf(
            msg,
            sizeof(msg),
            "Loaded PNG: %dx%d",
            g_TextureWidth,
            g_TextureHeight
        );

        LogMessage(msg);
    }

    // --------------------------------------------------
    // Upload PNG to OpenGL
    // --------------------------------------------------

    static bool UploadTexture()
    {
        if (!g_TextureLoaded || !g_TexturePixels)
            return false;

        if (g_TextureId != 0)
            return true;

        glGenTextures(1, &g_TextureId);

        if (!g_TextureId)
        {
            LogMessage("Failed to create OpenGL texture");
            return false;
        }

        glBindTexture(
            GL_TEXTURE_2D,
            g_TextureId
        );

        glPixelStorei(
            GL_UNPACK_ALIGNMENT,
            1
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT
        );

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            g_TextureWidth,
            g_TextureHeight,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            g_TexturePixels
        );

        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            char msg[128];

            snprintf(
                msg,
                sizeof(msg),
                "PNG texture upload failed: 0x%X",
                error
            );

            LogMessage(msg);

            glDeleteTextures(1, &g_TextureId);
            g_TextureId = 0;

            return false;
        }

        LogMessage("PNG uploaded to OpenGL");

        return true;
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

            // OpenGL texture IDs belong to their context.
            g_TextureId = 0;

            LogMessage("OpenGL context changed");
        }

        return LoadGLFunctions();
    }

    // --------------------------------------------------
    // Vector helpers
    // --------------------------------------------------

    static Vertex3 CalculateFaceNormal(
        const Vertex3& a,
        const Vertex3& b,
        const Vertex3& c
    )
    {
        const float ux = b.x - a.x;
        const float uy = b.y - a.y;
        const float uz = b.z - a.z;

        const float vx = c.x - a.x;
        const float vy = c.y - a.y;
        const float vz = c.z - a.z;

        Vertex3 normal{};

        normal.x = uy * vz - uz * vy;
        normal.y = uz * vx - ux * vz;
        normal.z = ux * vy - uy * vx;

        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z
        );

        if (length < 1e-8f)
            return { 0.0f, 0.0f, 1.0f };

        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        return normal;
    }

    static Vertex3 NormalizeNormal(const Vertex3& input)
    {
        const float length = std::sqrt(
            input.x * input.x +
            input.y * input.y +
            input.z * input.z
        );

        if (length < 1e-8f)
            return { 0.0f, 0.0f, 1.0f };

        return {
            input.x / length,
            input.y / length,
            input.z / length
        };
    }

    // --------------------------------------------------
    // Lighting
    // --------------------------------------------------

    static float CalculateBrightness(const Vertex3& normal)
    {
        const float lightLength = std::sqrt(
            LIGHT_X * LIGHT_X +
            LIGHT_Y * LIGHT_Y +
            LIGHT_Z * LIGHT_Z
        );

        const float diffuse = std::max(
            0.0f,
            (
                normal.x * LIGHT_X +
                normal.y * LIGHT_Y +
                normal.z * LIGHT_Z
            ) / lightLength
        );

        return std::min(
            1.0f,
            AMBIENT_LIGHT + DIFFUSE_LIGHT * diffuse
        );
    }

    // --------------------------------------------------
    // Render OBJ
    // --------------------------------------------------

    static void RenderTriangleMesh()
    {
        if (!EnsureContext())
            return;

        if (!g_MeshAttempted)
            LoadOBJ();

        if (!g_MeshLoaded)
            return;

        if (!g_TextureAttempted)
            LoadPNG();

        if (g_Vertices.empty() || g_Triangles.empty())
            return;

        // --------------------------------------------------
        // Save OpenGL state
        // --------------------------------------------------

        GLint viewport[4] = {};

        GLint oldProgram = 0;
        GLint oldMatrixMode = GL_MODELVIEW;
        GLint oldActiveTexture = GL_TEXTURE0;
        GLint depthBits = 0;

        glGetIntegerv(GL_VIEWPORT, viewport);

        if (viewport[2] <= 0 || viewport[3] <= 0)
            return;

        glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
        glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
        glGetIntegerv(GL_DEPTH_BITS, &depthBits);

        if (depthBits <= 0)
            return;

        if (oldMatrixMode != GL_MODELVIEW &&
            oldMatrixMode != GL_PROJECTION &&
            oldMatrixMode != GL_TEXTURE)
        {
            oldMatrixMode = GL_MODELVIEW;
        }

        if (g_ActiveTexture)
        {
            glGetIntegerv(
                GL_ACTIVE_TEXTURE,
                &oldActiveTexture
            );
        }

        // Save fixed-function attributes.
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        if (g_ActiveTexture)
            g_ActiveTexture(GL_TEXTURE0);

        // Save projection matrix.
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        // Save modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // --------------------------------------------------
        // Configure rendering
        // --------------------------------------------------

        g_UseProgram(0);

        glDisable(GL_CULL_FACE);

        glDisable(GL_STENCIL_TEST);
        glDisable(GL_SCISSOR_TEST);

        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        glDisable(GL_COLOR_LOGIC_OP);
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(
            GL_FRONT_AND_BACK,
            GL_FILL
        );

        glColorMask(
            GL_TRUE,
            GL_TRUE,
            GL_TRUE,
            GL_TRUE
        );

        // --------------------------------------------------
        // Texture setup
        // --------------------------------------------------

        const bool textureReady = UploadTexture();

        if (textureReady)
        {
            glEnable(GL_TEXTURE_2D);

            glBindTexture(
                GL_TEXTURE_2D,
                g_TextureId
            );

            glTexEnvi(
                GL_TEXTURE_ENV,
                GL_TEXTURE_ENV_MODE,
                GL_MODULATE
            );

            // Preserve transparent PNG pixels.
            glEnable(GL_BLEND);

            glBlendFunc(
                GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA
            );

            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.01f);
        }
        else
        {
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            glDisable(GL_ALPHA_TEST);
        }

        // --------------------------------------------------
        // Depth buffer
        // --------------------------------------------------

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);

        glClearDepth(1.0);
        glClear(GL_DEPTH_BUFFER_BIT);

        // --------------------------------------------------
        // Perspective projection
        // --------------------------------------------------

        const double aspect =
            static_cast<double>(viewport[2]) /
            static_cast<double>(viewport[3]);

        const double nearPlane = 0.1;
        const double farPlane = 100.0;

        const double halfFov =
            OBJECT_FOV * 3.14159265358979323846 / 360.0;

        const double halfHeight =
            nearPlane * std::tan(halfFov);

        const double halfWidth =
            halfHeight * aspect;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glFrustum(
            -halfWidth,
            halfWidth,
            -halfHeight,
            halfHeight,
            nearPlane,
            farPlane
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
        // Render triangles
        // --------------------------------------------------

        glBegin(GL_TRIANGLES);

        for (const Triangle& triangle : g_Triangles)
        {
            const ObjCorner& ca = triangle.corners[0];
            const ObjCorner& cb = triangle.corners[1];
            const ObjCorner& cc = triangle.corners[2];

            if (ca.position >= g_Vertices.size() ||
                cb.position >= g_Vertices.size() ||
                cc.position >= g_Vertices.size())
            {
                continue;
            }

            const Vertex3& a = g_Vertices[ca.position];
            const Vertex3& b = g_Vertices[cb.position];
            const Vertex3& c = g_Vertices[cc.position];

            const Vertex3 faceNormal =
                CalculateFaceNormal(a, b, c);

            const ObjCorner* corners[3] = {
                &ca,
                &cb,
                &cc
            };

            const Vertex3* positions[3] = {
                &a,
                &b,
                &c
            };

            for (int i = 0; i < 3; ++i)
            {
                const ObjCorner& corner = *corners[i];

                const Vertex3& position = *positions[i];

                Vertex3 normal = faceNormal;

                if (corner.normal >= 0 &&
                    static_cast<size_t>(corner.normal) < g_Normals.size())
                {
                    normal = NormalizeNormal(
                        g_Normals[corner.normal]
                    );
                }

                const float brightness =
                    CalculateBrightness(normal);

                glColor4f(
                    OBJECT_COLOR_R * brightness,
                    OBJECT_COLOR_G * brightness,
                    OBJECT_COLOR_B * brightness,
                    1.0f
                );

                glNormal3f(
                    normal.x,
                    normal.y,
                    normal.z
                );

                if (textureReady &&
                    corner.texcoord >= 0 &&
                    static_cast<size_t>(corner.texcoord) < g_Texcoords.size())
                {
                    const Vertex2& uv =
                        g_Texcoords[corner.texcoord];

                    glTexCoord2f(uv.u, uv.v);
                }
                else
                {
                    glTexCoord2f(0.0f, 0.0f);
                }

                glVertex3f(
                    position.x,
                    position.y,
                    position.z
                );
            }
        }

        glEnd();

        // --------------------------------------------------
        // Restore OpenGL state
        // --------------------------------------------------

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glPopAttrib();

        g_UseProgram(
            static_cast<GLuint>(oldProgram)
        );

        if (g_ActiveTexture)
        {
            g_ActiveTexture(
                static_cast<GLenum>(oldActiveTexture)
            );
        }

        glMatrixMode(
            static_cast<GLenum>(oldMatrixMode)
        );
    }
}

// --------------------------------------------------
// REPENTOGON hook
// --------------------------------------------------

HOOK_GLOBAL(OpenGL::wglSwapBuffers, (HDC hdc)->bool, __stdcall)
{
    if (wglGetCurrentContext())
        RenderTriangleMesh();

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
    LogMessage("Isaac: ViewPoint initialized");
    return 0;
}
