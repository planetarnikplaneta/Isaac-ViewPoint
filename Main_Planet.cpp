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

// OpenGL 1.2+ / framebuffer extension declarations; Windows' GL header is 1.1.
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#ifndef GL_RGBA8
#define GL_RGBA8 0x8058
#endif
#ifndef GL_DEPTH_COMPONENT24
#define GL_DEPTH_COMPONENT24 0x81A6
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_RENDERBUFFER
#define GL_RENDERBUFFER 0x8D41
#endif
#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif
#ifndef GL_DEPTH_ATTACHMENT
#define GL_DEPTH_ATTACHMENT 0x8D00
#endif
#ifndef GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#endif
#ifndef GL_FRAMEBUFFER_BINDING
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#endif
#ifndef GL_RENDERBUFFER_BINDING
#define GL_RENDERBUFFER_BINDING 0x8CA7
#endif
#ifndef GL_CURRENT_PROGRAM
#define GL_CURRENT_PROGRAM 0x8B8D
#endif
#ifndef GL_ACTIVE_TEXTURE
#define GL_ACTIVE_TEXTURE 0x84E0
#endif
#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif

using PFNGLGENFRAMEBUFFERSPROC = void (APIENTRY *)(GLsizei, GLuint *);
using PFNGLBINDFRAMEBUFFERPROC = void (APIENTRY *)(GLenum, GLuint);
using PFNGLDELETEFRAMEBUFFERSPROC = void (APIENTRY *)(GLsizei, const GLuint *);
using PFNGLCHECKFRAMEBUFFERSTATUSPROC = GLenum (APIENTRY *)(GLenum);
using PFNGLFRAMEBUFFERTEXTURE2DPROC = void (APIENTRY *)(GLenum, GLenum, GLenum, GLuint, GLint);
using PFNGLGENRENDERBUFFERSPROC = void (APIENTRY *)(GLsizei, GLuint *);
using PFNGLBINDRENDERBUFFERPROC = void (APIENTRY *)(GLenum, GLuint);
using PFNGLDELETERENDERBUFFERSPROC = void (APIENTRY *)(GLsizei, const GLuint *);
using PFNGLRENDERBUFFERSTORAGEPROC = void (APIENTRY *)(GLenum, GLenum, GLsizei, GLsizei);
using PFNGLFRAMEBUFFERRENDERBUFFERPROC = void (APIENTRY *)(GLenum, GLenum, GLenum, GLuint);
using PFNGLUSEPROGRAMPROC = void (APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void (APIENTRY *)(GLenum);

struct Vector { float x; float y; };
struct ANM2;

class PlayerHUD
{
public:
    void RenderHearts(Vector *unk, ANM2 *sprite, int playerHudLayout, float scale, Vector pos);
    char _padding[8];
    short _playerHudIndex;
};

namespace
{
    constexpr GLsizei kRenderSize = 768;

    struct Vertex3 { float x, y, z; };
    struct Triangle { uint32_t a, b, c; };

    struct GLFunctions
    {
        PFNGLGENFRAMEBUFFERSPROC genFramebuffers = nullptr;
        PFNGLBINDFRAMEBUFFERPROC bindFramebuffer = nullptr;
        PFNGLDELETEFRAMEBUFFERSPROC deleteFramebuffers = nullptr;
        PFNGLCHECKFRAMEBUFFERSTATUSPROC checkFramebufferStatus = nullptr;
        PFNGLFRAMEBUFFERTEXTURE2DPROC framebufferTexture2D = nullptr;
        PFNGLGENRENDERBUFFERSPROC genRenderbuffers = nullptr;
        PFNGLBINDRENDERBUFFERPROC bindRenderbuffer = nullptr;
        PFNGLDELETERENDERBUFFERSPROC deleteRenderbuffers = nullptr;
        PFNGLRENDERBUFFERSTORAGEPROC renderbufferStorage = nullptr;
        PFNGLFRAMEBUFFERRENDERBUFFERPROC framebufferRenderbuffer = nullptr;
        PFNGLUSEPROGRAMPROC useProgram = nullptr;
        PFNGLACTIVETEXTUREPROC activeTexture = nullptr;
    };

    static HMODULE g_Module = nullptr;
    static bool g_MeshLoaded = false;
    static bool g_ContextLogged = false;
    static HGLRC g_ResourceContext = nullptr;
    static GLuint g_Fbo = 0, g_ColorTexture = 0, g_DepthRenderbuffer = 0;
    static GLFunctions g_GL;
    static std::vector<Vertex3> g_Vertices;
    static std::vector<Triangle> g_Triangles;

    static void LogMessage(const char *text)
    {
        FILE *file = fopen("C:\\MyNativeMod.log", "a");
        if (file) { fprintf(file, "OBJ OpenGL: %s\n", text); fclose(file); }
    }

    static std::string GetObjPath()
    {
        char modulePath[MAX_PATH] = {};
 DWORD len = GetModuleFileNameA(g_Module, modulePath, MAX_PATH);
        if (!len || len >= MAX_PATH) return "objectToRender.obj";
        std::string path(modulePath, len);
size_t slash = path.find_last_of("\\/");
        if (slash != std::string::npos) path.resize(slash + 1);
        return path + "objectToRender.obj";
    }
 static bool ParseObjIndex(const std::string &token, size_t count, uint32_t &out)
    {
         std::string text = token.substr(0, token.find('/'));
        if (text.empty()) return false;
        char *end = nullptr;
 long value = strtol(text.c_str(), &end, 10);
        if (!end || *end || value == 0) return false;
        long resolved = value > 0 ? value - 1 : static_cast<long>(count) + value;
        if (resolved < 0 || static_cast<size_t>(resolved) >= count) return false;
        out = static_cast<uint32_t>(resolved);
        return true;
    }

    static void LoadOBJ()
    {
        const std::string path = GetObjPath();
        std::ifstream input(path);
 if (!input) { LogMessage("cannot open objectToRender.obj beside DLL"); return; }

        std::vector<Vertex3> source;
        std::vector<Triangle> faces;
        std::string line;
        while (std::getline(input, line))
        {
 if (line.empty() || line[0] == '#') continue;
            std::istringstream stream(line);
            std::string type;
  stream >> type;
            if (type == "v")
            {
 Vertex3 v{};
                if (stream >> v.x >> v.y >> v.z) source.push_back(v);
            }
            else if (type == "f")
            {
std::vector<uint32_t> face;
                std::string token;
                while (stream >> token)
                {
                    uint32_t index;
                    if (ParseObjIndex(token, source.size(), index)) face.push_back(index);
                }
                for (size_t i = 1; i + 1 < face.size(); ++i)
                    faces.push_back({face[0], face[i], face[i + 1]});
            }
        }
        if (source.empty() || faces.empty()) { LogMessage("OBJ has no usable vertices/faces"); return; }

        Vertex3 lo = source.front(), hi = source.front();
        for (const Vertex3 &v : source)
        {
            lo.x = std::min(lo.x, v.x); lo.y = std::min(lo.y, v.y); lo.z = std::min(lo.z, v.z);
            hi.x = std::max(hi.x, v.x); hi.y = std::max(hi.y, v.y); hi.z = std::max(hi.z, v.z);
        }
        const float cx = (lo.x + hi.x) * .5f, cy = (lo.y + hi.y) * .5f, cz = (lo.z + hi.z) * .5f;
        const float scale = 2.0f / std::max({hi.x-lo.x, hi.y-lo.y, hi.z-lo.z, 0.0001f});
        g_Vertices.clear();
        g_Vertices.reserve(source.size());
        for (const Vertex3 &v : source) g_Vertices.push_back({(v.x-cx)*scale, (v.y-cy)*scale, (v.z-cz)*scale});
        g_Triangles = std::move(faces);
        g_MeshLoaded = true;
        char msg[160];
        snprintf(msg, sizeof(msg), "loaded %zu vertices and %zu triangles", g_Vertices.size(), g_Triangles.size());
        LogMessage(msg);
    }

    static PROC GetGLProc(const char *name)
    {
        PROC p = wglGetProcAddress(name);
        if (!p || p == reinterpret_cast<PROC>(1) || p == reinterpret_cast<PROC>(2) ||
            p == reinterpret_cast<PROC>(3) || p == reinterpret_cast<PROC>(-1))
        {
            static HMODULE gl = GetModuleHandleA("opengl32.dll");
            p = gl ? GetProcAddress(gl, name) : nullptr;
        }
        return p;
    }

    template<class T>
    static T LoadEither(const char *core, const char *ext)
    {
        T p = reinterpret_cast<T>(GetGLProc(core));
        return p ? p : reinterpret_cast<T>(GetGLProc(ext));
    }

    static bool LoadGLFunctions()
    {
        g_GL.genFramebuffers = LoadEither<PFNGLGENFRAMEBUFFERSPROC>("glGenFramebuffers", "glGenFramebuffersEXT");
        g_GL.bindFramebuffer = LoadEither<PFNGLBINDFRAMEBUFFERPROC>("glBindFramebuffer", "glBindFramebufferEXT");
        g_GL.deleteFramebuffers = LoadEither<PFNGLDELETEFRAMEBUFFERSPROC>("glDeleteFramebuffers", "glDeleteFramebuffersEXT");
        g_GL.checkFramebufferStatus = LoadEither<PFNGLCHECKFRAMEBUFFERSTATUSPROC>("glCheckFramebufferStatus", "glCheckFramebufferStatusEXT");
        g_GL.framebufferTexture2D = LoadEither<PFNGLFRAMEBUFFERTEXTURE2DPROC>("glFramebufferTexture2D", "glFramebufferTexture2DEXT");
        g_GL.genRenderbuffers = LoadEither<PFNGLGENRENDERBUFFERSPROC>("glGenRenderbuffers", "glGenRenderbuffersEXT");
        g_GL.bindRenderbuffer = LoadEither<PFNGLBINDRENDERBUFFERPROC>("glBindRenderbuffer", "glBindRenderbufferEXT");
        g_GL.deleteRenderbuffers = LoadEither<PFNGLDELETERENDERBUFFERSPROC>("glDeleteRenderbuffers", "glDeleteRenderbuffersEXT");
        g_GL.renderbufferStorage = LoadEither<PFNGLRENDERBUFFERSTORAGEPROC>("glRenderbufferStorage", "glRenderbufferStorageEXT");
        g_GL.framebufferRenderbuffer = LoadEither<PFNGLFRAMEBUFFERRENDERBUFFERPROC>("glFramebufferRenderbuffer", "glFramebufferRenderbufferEXT");
        g_GL.useProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(GetGLProc("glUseProgram"));
        g_GL.activeTexture = LoadEither<PFNGLACTIVETEXTUREPROC>("glActiveTexture", "glActiveTextureARB");
        return g_GL.genFramebuffers && g_GL.bindFramebuffer && g_GL.deleteFramebuffers &&
               g_GL.checkFramebufferStatus && g_GL.framebufferTexture2D && g_GL.genRenderbuffers &&
               g_GL.bindRenderbuffer && g_GL.deleteRenderbuffers && g_GL.renderbufferStorage &&
               g_GL.framebufferRenderbuffer && g_GL.useProgram;
    }

    static bool EnsureTarget()
    {
        HGLRC context = wglGetCurrentContext();
        if (!context) return false;
        if (context != g_ResourceContext)
        {
            // Names from another GL context cannot safely be reused here.
            g_ResourceContext = context;
            g_Fbo = g_ColorTexture = g_DepthRenderbuffer = 0;
            g_GL = GLFunctions{};
        }
        if (g_Fbo && g_ColorTexture && g_DepthRenderbuffer) return true;
        if (!LoadGLFunctions()) { LogMessage("FBO functions unavailable in current context"); return false; }

        GLint oldFbo = 0, oldRbo = 0, oldTexture = 0;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFbo);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRbo);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture);

        glGenTextures(1, &g_ColorTexture);
        glBindTexture(GL_TEXTURE_2D, g_ColorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, kRenderSize, kRenderSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        g_GL.genFramebuffers(1, &g_Fbo);
        g_GL.bindFramebuffer(GL_FRAMEBUFFER, g_Fbo);
        g_GL.framebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_ColorTexture, 0);
        g_GL.genRenderbuffers(1, &g_DepthRenderbuffer);
        g_GL.bindRenderbuffer(GL_RENDERBUFFER, g_DepthRenderbuffer);
        g_GL.renderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, kRenderSize, kRenderSize);
        g_GL.framebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_DepthRenderbuffer);
        GLenum status = g_GL.checkFramebufferStatus(GL_FRAMEBUFFER);

        g_GL.bindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(oldFbo));
        g_GL.bindRenderbuffer(GL_RENDERBUFFER, static_cast<GLuint>(oldRbo));
        glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(oldTexture));
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            char msg[128]; snprintf(msg, sizeof(msg), "FBO incomplete: 0x%04X", status); LogMessage(msg);
            g_GL.deleteFramebuffers(1, &g_Fbo);
            g_GL.deleteRenderbuffers(1, &g_DepthRenderbuffer);
            glDeleteTextures(1, &g_ColorTexture);
            g_Fbo = g_ColorTexture = g_DepthRenderbuffer = 0;
            return false;
        }
        LogMessage("offscreen color/depth framebuffer created");
        return true;
    }

    static void RenderTriangleMesh()
    {
        if (!wglGetCurrentContext() || !EnsureTarget()) return;
        if (!g_MeshLoaded) { LoadOBJ(); if (!g_MeshLoaded) return; }
        if (g_Vertices.empty() || g_Triangles.empty()) return;

        GLint viewport[4] = {}, oldFbo = 0, oldProgram = 0, oldMatrixMode = GL_MODELVIEW;
        GLint oldActiveTexture = GL_TEXTURE0;
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFbo);
        glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
        glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
        if (g_GL.activeTexture) glGetIntegerv(GL_ACTIVE_TEXTURE, &oldActiveTexture);
        if (viewport[2] <= 0 || viewport[3] <= 0) return;

        if (!g_ContextLogged)
        {
            const GLubyte *ver = glGetString(GL_VERSION), *renderer = glGetString(GL_RENDERER);
            char msg[256];
            snprintf(msg, sizeof(msg), "active context GL %s / %s; viewport %dx%d",
                ver ? reinterpret_cast<const char *>(ver) : "unknown",
                renderer ? reinterpret_cast<const char *>(renderer) : "unknown", viewport[2], viewport[3]);
            LogMessage(msg);
            g_ContextLogged = true;
        }

        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION); glPushMatrix();
        glMatrixMode(GL_MODELVIEW); glPushMatrix();

        if (g_GL.activeTexture) g_GL.activeTexture(GL_TEXTURE0);
        g_GL.useProgram(0);
        g_GL.bindFramebuffer(GL_FRAMEBUFFER, g_Fbo);
        glViewport(0, 0, kRenderSize, kRenderSize);
        glDisable(GL_SCISSOR_TEST); glDisable(GL_BLEND); glDisable(GL_ALPHA_TEST);
        glDisable(GL_STENCIL_TEST); glDisable(GL_CULL_FACE); glDisable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL); glDepthMask(GL_TRUE);
        glClearColor(0, 0, 0, 0); glClearDepth(1.0); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        const double n = 0.1, half = n * 0.41421356237;
        glFrustum(-half, half, -half, half, n, 100.0);
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glTranslatef(0, 0, -5);
        glRotatef(-12, 1, 0, 0);
        glRotatef(static_cast<float>(GetTickCount64()) * 0.012f, 0, 1, 0);

        const float lx = -0.35f, ly = 0.55f, lz = -0.76f;
        const float lightLen = std::sqrt(lx*lx + ly*ly + lz*lz);
        glBegin(GL_TRIANGLES);
        for (const Triangle &t : g_Triangles)
        {
            if (t.a >= g_Vertices.size() || t.b >= g_Vertices.size() || t.c >= g_Vertices.size()) continue;
            const Vertex3 &a = g_Vertices[t.a], &b = g_Vertices[t.b], &c = g_Vertices[t.c];
            const float ux=b.x-a.x, uy=b.y-a.y, uz=b.z-a.z;
            const float vx=c.x-a.x, vy=c.y-a.y, vz=c.z-a.z;
            float nx=uy*vz-uz*vy, ny=uz*vx-ux*vz, nz=ux*vy-uy*vx;
            const float nl=std::sqrt(nx*nx+ny*ny+nz*nz);
            if (nl < 1e-8f) continue;
            nx/=nl; ny/=nl; nz/=nl;
            const float diffuse=std::max(0.0f,(nx*lx+ny*ly+nz*lz)/lightLen);
            const float brightness=0.25f+0.75f*diffuse;
            glColor4f(0.18f*brightness, 0.52f*brightness, 0.82f*brightness, 1.0f);
            glNormal3f(nx,ny,nz);
            glVertex3f(a.x,a.y,a.z); glVertex3f(b.x,b.y,b.z); glVertex3f(c.x,c.y,c.z);
        }
        glEnd();

        // Composite the isolated render target; the game's depth buffer is untouched.
        g_GL.bindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(oldFbo));
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
        glMatrixMode(GL_PROJECTION); glLoadIdentity(); glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glDisable(GL_DEPTH_TEST); glDisable(GL_CULL_FACE); glDisable(GL_ALPHA_TEST);
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, g_ColorTexture);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); glColor4f(1,1,1,1);

        const float side=static_cast<float>(std::min(viewport[2],viewport[3]))*0.72f;
        const float left=(viewport[2]-side)*0.5f, top=(viewport[3]-side)*0.5f;
        const float right=left+side, bottom=top+side;
        glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex2f(left,top); glTexCoord2f(1,1); glVertex2f(right,top);
        glTexCoord2f(1,0); glVertex2f(right,bottom); glTexCoord2f(0,0); glVertex2f(left,bottom);
        glEnd();

        glMatrixMode(GL_MODELVIEW); glPopMatrix();
        glMatrixMode(GL_PROJECTION); glPopMatrix();
        glPopAttrib();
        g_GL.bindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(oldFbo));
        g_GL.useProgram(static_cast<GLuint>(oldProgram));
        if (g_GL.activeTexture) g_GL.activeTexture(static_cast<GLenum>(oldActiveTexture));
        glMatrixMode(static_cast<GLenum>(oldMatrixMode));
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
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
if (_playerHudIndex == 0) RenderTriangleMesh();
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
