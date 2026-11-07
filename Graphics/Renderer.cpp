#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Renderer.h"

#include "../Core/Logger.h"
#include "../Core/Types.h"
#include "../Core/State.h"
#include "../Models/Texture.h"
#include "../Models/GpuMesh.h"
#include "../Camera/Camera.h"
#include "../Scene/Scene.h"

#include <Windows.h>
#include <gl/GL.h>

#ifndef GL_CURRENT_PROGRAM
#define GL_CURRENT_PROGRAM 0x8B8D
#endif

#ifndef GL_ACTIVE_TEXTURE
#define GL_ACTIVE_TEXTURE 0x84E0
#endif

#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif

#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif

#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif

#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif

#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif

#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH 0x8B84
#endif

#ifndef GL_FLOAT
#define GL_FLOAT 0x1406
#endif

#ifndef GL_TRIANGLES
#define GL_TRIANGLES 0x0004
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstddef>
#include <string>
#include <vector>

namespace ViewPoint
{
    namespace
    {
    // CONFIGURATION

    constexpr float OBJECT_DISTANCE = 5.0f;
    constexpr float OBJECT_ROTATION_SPEED = 0.012f;
    constexpr float OBJECT_TILT = -12.0f;
    constexpr float OBJECT_FOV = 45.0f;

    constexpr float LIGHT_X = -0.35f;
    constexpr float LIGHT_Y = 0.55f;
    constexpr float LIGHT_Z = -0.76f;

    constexpr float AMBIENT_LIGHT = 0.40f;
    constexpr float DIFFUSE_LIGHT = 0.60f;
    // LIGHTING

    static float CalculateBrightness(
        const Vertex3 &normal)
    {
        const float lightLength = std::sqrt(
            LIGHT_X * LIGHT_X +
            LIGHT_Y * LIGHT_Y +
            LIGHT_Z * LIGHT_Z);

        const float diffuse = (std::max)(0.0f,
                                         (
                                             normal.x * LIGHT_X +
                                             normal.y * LIGHT_Y +
                                             normal.z * LIGHT_Z) /
                                             lightLength);

        return (std::min)(1.0f,
                          AMBIENT_LIGHT + DIFFUSE_LIGHT * diffuse);
    }
    // OPENGL FUNCTION LOADING

    static PROC GetGLProc(const char *name)
    {
        PROC proc = wglGetProcAddress(name);

        if (!proc ||
            proc == reinterpret_cast<PROC>(1) ||
            proc == reinterpret_cast<PROC>(2) ||
            proc == reinterpret_cast<PROC>(3) ||
            proc == reinterpret_cast<PROC>(-1))
        {
            HMODULE gl =
                GetModuleHandleA("opengl32.dll");

            proc = gl
                       ? GetProcAddress(gl, name)
                       : nullptr;
        }

        return proc;
    }

// SHADER COMPILATION

    static GLuint CompileShader(
        GLenum type,
        const char *source)
    {
        GLuint shader = g_CreateShader(type);

        if (!shader)
        {
            ViewPoint::LogMessage("glCreateShader failed.");
            return 0;
        }

        g_ShaderSource(
            shader,
            1,
            &source,
            nullptr);

        g_CompileShader(shader);

        GLint success = GL_FALSE;

        g_GetShaderiv(
            shader,
            GL_COMPILE_STATUS,
            &success);

        if (success != GL_TRUE)
        {
            GLint length = 0;

            g_GetShaderiv(
                shader,
                GL_INFO_LOG_LENGTH,
                &length);

            std::vector<char> log(
                static_cast<size_t>((std::max)(length, 1)),
                '\0');

            g_GetShaderInfoLog(
                shader,
                static_cast<GLsizei>(log.size()),
                nullptr,
                log.data());

            ViewPoint::LogMessage("Shader compilation failed.");
            ViewPoint::LogMessage(log.data());

            g_DeleteShader(shader);

            return 0;
        }

        return shader;
    }

    static bool CreateShaderProgram()
    {
        if (g_ShaderProgram)
            return true;

        static const char *vertexSource = R"(
            #version 120
        
            uniform vec3 uLightDirection;
            uniform float uAmbient;
            uniform float uDiffuse;
        
            varying vec2 vTexcoord;
            varying float vBrightness;
        
            void main()
            {
                gl_Position = ftransform();
        
                // Pass the fixed-function current color to the fragment shader.
                gl_FrontColor = gl_Color;
        
                // Pass texture coordinates from VBO attribute array 0.
                vTexcoord = gl_MultiTexCoord0.xy;
        
                // Transform the normal into eye space.
                vec3 normal =
                    normalize(gl_NormalMatrix * gl_Normal);
        
                float diffuseLight = max(
                    dot(normal, normalize(uLightDirection)),
                    0.0
                );
        
                vBrightness = clamp(
                    uAmbient + uDiffuse * diffuseLight,
                    0.0,
                    1.0
                );
            }
        )";

        static const char *fragmentSource = R"(
            #version 120
    
            uniform sampler2D uTexture;
            uniform int uUseTexture;
    
            varying vec2 vTexcoord;
            varying float vBrightness;
    
            void main()
            {
                vec4 color = gl_Color;
    
                if (uUseTexture != 0)
                {
                    color *= texture2D(
                        uTexture,
                        vTexcoord
                    );
                }
    
                gl_FragColor = vec4(
                    color.rgb * vBrightness,
                    color.a
                );
            }
        )";

        GLuint vertexShader = CompileShader(
            GL_VERTEX_SHADER,
            vertexSource);

        if (!vertexShader)
            return false;

        GLuint fragmentShader = CompileShader(
            GL_FRAGMENT_SHADER,
            fragmentSource);

        if (!fragmentShader)
        {
            g_DeleteShader(vertexShader);
            return false;
        }

        GLuint program = g_CreateProgram();

        if (!program)
        {
            g_DeleteShader(vertexShader);
            g_DeleteShader(fragmentShader);

            ViewPoint::LogMessage("glCreateProgram failed.");

            return false;
        }

        g_AttachShader(program, vertexShader);
        g_AttachShader(program, fragmentShader);

        g_LinkProgram(program);

        g_DeleteShader(vertexShader);
        g_DeleteShader(fragmentShader);

        GLint success = GL_FALSE;

        g_GetProgramiv(
            program,
            GL_LINK_STATUS,
            &success);

        if (success != GL_TRUE)
        {
            GLint length = 0;

            g_GetProgramiv(
                program,
                GL_INFO_LOG_LENGTH,
                &length);

            std::vector<char> log(
                static_cast<size_t>((std::max)(length, 1)),
                '\0');

            g_GetProgramInfoLog(
                program,
                static_cast<GLsizei>(log.size()),
                nullptr,
                log.data());

            ViewPoint::LogMessage("Shader program linking failed.");
            ViewPoint::LogMessage(log.data());

            g_DeleteProgram(program);

            return false;
        }

        g_ShaderProgram = program;

        g_UniformTexture =
            g_GetUniformLocation(program, "uTexture");

        g_UniformUseTexture =
            g_GetUniformLocation(program, "uUseTexture");

        g_UniformLightDirection =
            g_GetUniformLocation(program, "uLightDirection");

        g_UniformAmbient =
            g_GetUniformLocation(program, "uAmbient");

        g_UniformDiffuse =
            g_GetUniformLocation(program, "uDiffuse");

        ViewPoint::LogMessage("GPU shader program successfully created.");

        return true;
    }

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

            g_GenBuffers = nullptr;
            g_BindBuffer = nullptr;
            g_BufferData = nullptr;
            g_DeleteBuffers = nullptr;

            g_CreateShader = nullptr;
            g_ShaderSource = nullptr;
            g_CompileShader = nullptr;
            g_GetShaderiv = nullptr;
            g_GetShaderInfoLog = nullptr;
            g_DeleteShader = nullptr;

            g_CreateProgram = nullptr;
            g_AttachShader = nullptr;
            g_LinkProgram = nullptr;
            g_GetProgramiv = nullptr;
            g_GetProgramInfoLog = nullptr;
            g_DeleteProgram = nullptr;

            g_GetUniformLocation = nullptr;
            g_Uniform1i = nullptr;
            g_Uniform1f = nullptr;
            g_Uniform3f = nullptr;
            g_DrawArrays = nullptr;

            g_ShaderProgram = 0;

            for (Model &model : g_Models)
            {
                for (Material &material : model.materials)
                    material.textureId = 0;

                for (MaterialBatch &batch : model.gpuBatches)
                    batch.vertexBuffer = 0;

                model.gpuReady = false;
                model.gpuBuildAttempted = false;
            }

            ViewPoint::LogMessage("OpenGL context changed.");
        }

#define LOAD_GL_FUNCTION(variable, type, name) \
    if (!(variable))                           \
    (variable) = reinterpret_cast<type>(GetGLProc(name))

        LOAD_GL_FUNCTION(
            g_UseProgram,
            PFNGLUSEPROGRAMPROC,
            "glUseProgram");

        LOAD_GL_FUNCTION(
            g_ActiveTexture,
            PFNGLACTIVETEXTUREPROC,
            "glActiveTexture");

        LOAD_GL_FUNCTION(
            g_GenBuffers,
            PFNGLGENBUFFERSPROC,
            "glGenBuffers");

        LOAD_GL_FUNCTION(
            g_BindBuffer,
            PFNGLBINDBUFFERPROC,
            "glBindBuffer");

        LOAD_GL_FUNCTION(
            g_BufferData,
            PFNGLBUFFERDATAPROC,
            "glBufferData");

        LOAD_GL_FUNCTION(
            g_DeleteBuffers,
            PFNGLDELETEBUFFERSPROC,
            "glDeleteBuffers");

        LOAD_GL_FUNCTION(
            g_CreateShader,
            PFNGLCREATESHADERPROC,
            "glCreateShader");

        LOAD_GL_FUNCTION(
            g_ShaderSource,
            PFNGLSHADERSOURCEPROC,
            "glShaderSource");

        LOAD_GL_FUNCTION(
            g_CompileShader,
            PFNGLCOMPILESHADERPROC,
            "glCompileShader");

        LOAD_GL_FUNCTION(
            g_GetShaderiv,
            PFNGLGETSHADERIVPROC,
            "glGetShaderiv");

        LOAD_GL_FUNCTION(
            g_GetShaderInfoLog,
            PFNGLGETSHADERINFOLOGPROC,
            "glGetShaderInfoLog");

        LOAD_GL_FUNCTION(
            g_DeleteShader,
            PFNGLDELETESHADERPROC,
            "glDeleteShader");

        LOAD_GL_FUNCTION(
            g_CreateProgram,
            PFNGLCREATEPROGRAMPROC,
            "glCreateProgram");

        LOAD_GL_FUNCTION(
            g_AttachShader,
            PFNGLATTACHSHADERPROC,
            "glAttachShader");

        LOAD_GL_FUNCTION(
            g_LinkProgram,
            PFNGLLINKPROGRAMPROC,
            "glLinkProgram");

        LOAD_GL_FUNCTION(
            g_GetProgramiv,
            PFNGLGETPROGRAMIVPROC,
            "glGetProgramiv");

        LOAD_GL_FUNCTION(
            g_GetProgramInfoLog,
            PFNGLGETPROGRAMINFOLOGPROC,
            "glGetProgramInfoLog");

        LOAD_GL_FUNCTION(
            g_DeleteProgram,
            PFNGLDELETEPROGRAMPROC,
            "glDeleteProgram");

        LOAD_GL_FUNCTION(
            g_GetUniformLocation,
            PFNGLGETUNIFORMLOCATIONPROC,
            "glGetUniformLocation");

        LOAD_GL_FUNCTION(
            g_Uniform1i,
            PFNGLUNIFORM1IPROC,
            "glUniform1i");

        LOAD_GL_FUNCTION(
            g_Uniform1f,
            PFNGLUNIFORM1FPROC,
            "glUniform1f");

        LOAD_GL_FUNCTION(
            g_Uniform3f,
            PFNGLUNIFORM3FPROC,
            "glUniform3f");

        LOAD_GL_FUNCTION(
            g_DrawArrays,
            PFNGLDRAWARRAYSPROC,
            "glDrawArrays");

#undef LOAD_GL_FUNCTION

        if (!g_UseProgram ||
            !g_GenBuffers ||
            !g_BindBuffer ||
            !g_BufferData ||
            !g_DeleteBuffers ||
            !g_CreateShader ||
            !g_ShaderSource ||
            !g_CompileShader ||
            !g_GetShaderiv ||
            !g_GetShaderInfoLog ||
            !g_DeleteShader ||
            !g_CreateProgram ||
            !g_AttachShader ||
            !g_LinkProgram ||
            !g_GetProgramiv ||
            !g_GetProgramInfoLog ||
            !g_DeleteProgram ||
            !g_GetUniformLocation ||
            !g_Uniform1i ||
            !g_Uniform1f ||
            !g_Uniform3f ||
            !g_DrawArrays)
        {
            ViewPoint::LogMessage(
                "Required VBO or shader OpenGL functions are unavailable.");

            return false;
        }

        if (!CreateShaderProgram())
            return false;

        return true;
    }

    // TRIANGLE RENDERING

    static void RenderTriangle(
        const Model &model,
        const Triangle &triangle)
    {
        const ObjCorner *corners[3] = {
            &triangle.corners[0],
            &triangle.corners[1],
            &triangle.corners[2]};

        const Vertex3 *positions[3] = {
            &model.vertices[corners[0]->position],
            &model.vertices[corners[1]->position],
            &model.vertices[corners[2]->position]};

        const Vertex3 faceNormal =
            CalculateFaceNormal(
                *positions[0],
                *positions[1],
                *positions[2]);

        const int materialIndex =
            triangle.materialIndex >= 0 &&
                    static_cast<size_t>(
                        triangle.materialIndex) < model.materials.size()
                ? triangle.materialIndex
                : 0;

        const Material &material =
            model.materials[materialIndex];

        for (int i = 0; i < 3; ++i)
        {
            const ObjCorner &corner =
                *corners[i];

            Vertex3 normal = faceNormal;

            if (corner.normal >= 0 &&
                static_cast<size_t>(corner.normal) <
                    model.normals.size())
            {
                normal = NormalizeNormal(
                    model.normals[corner.normal]);
            }

            const float brightness =
                CalculateBrightness(normal);

            glColor4f(
                material.diffuse[0] * brightness,
                material.diffuse[1] * brightness,
                material.diffuse[2] * brightness,
                1.0f);

            glNormal3f(
                normal.x,
                normal.y,
                normal.z);

            if (corner.texcoord >= 0 &&
                static_cast<size_t>(corner.texcoord) <
                    model.texcoords.size())
            {
                const Vertex2 &uv =
                    model.texcoords[corner.texcoord];

                glTexCoord2f(uv.u, uv.v);
            }
            else
            {
                glTexCoord2f(0.0f, 0.0f);
            }

            glVertex3f(
                positions[i]->x,
                positions[i]->y,
                positions[i]->z);
        }
    }

    // MODEL RENDERING

    static void RenderModel(Model &model)
    {
        if (!model.loaded)
            return;

        GLint viewport[4] = {};

        GLint oldProgram = 0;
        GLint oldMatrixMode = GL_MODELVIEW;
        GLint oldActiveTexture = GL_TEXTURE0;
        GLint depthBits = 0;

        glGetIntegerv(
            GL_VIEWPORT,
            viewport);

        if (viewport[2] <= 0 ||
            viewport[3] <= 0)
        {
            return;
        }

        glGetIntegerv(
            GL_CURRENT_PROGRAM,
            &oldProgram);

        glGetIntegerv(
            GL_MATRIX_MODE,
            &oldMatrixMode);

        glGetIntegerv(
            GL_DEPTH_BITS,
            &depthBits);

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
                &oldActiveTexture);
        }

        // ----------------------------------------------
        // Save state
        // ----------------------------------------------

        glPushAttrib(GL_ALL_ATTRIB_BITS);

        if (g_ActiveTexture)
            g_ActiveTexture(GL_TEXTURE0);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // ----------------------------------------------
        // Rendering configuration
        // ----------------------------------------------

        glDisable(GL_CULL_FACE);
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        glDisable(GL_COLOR_LOGIC_OP);
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(
            GL_FRONT_AND_BACK,
            GL_FILL);

        glColorMask(
            GL_TRUE,
            GL_TRUE,
            GL_TRUE,
            GL_TRUE);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);

        glEnable(GL_BLEND);

        glBlendFunc(
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.01f);

        // ----------------------------------------------
        // Projection
        // ----------------------------------------------

        const double aspect =
            static_cast<double>(viewport[2]) /
            static_cast<double>(viewport[3]);

        const double nearPlane = g_Camera.nearPlane;
        const double farPlane = g_Camera.farPlane;

        const double halfFov =
            g_Camera.fieldOfView *
            3.14159265358979323846 / 360.0;

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
            farPlane);

        // ----------------------------------------------
        // First-person camera transformation
        // ----------------------------------------------

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Apply inverse camera rotation.
        glRotatef(
            -g_Camera.pitch,
            1.0f,
            0.0f,
            0.0f);

        glRotatef(
            -g_Camera.yaw,
            0.0f,
            1.0f,
            0.0f);

        // Apply inverse camera position.
        glTranslatef(
            -g_Camera.position.x,
            -g_Camera.position.y,
            -g_Camera.position.z);

        // ----------------------------------------------
        // Individual object transformation
        // ----------------------------------------------

        glTranslatef(
            model.position.x,
            model.position.y,
            model.position.z);

        glRotatef(
            model.rotation.x,
            1.0f,
            0.0f,
            0.0f);

        glRotatef(
            model.rotation.y,
            0.0f,
            1.0f,
            0.0f);

        glRotatef(
            model.rotation.z,
            0.0f,
            0.0f,
            1.0f);

        glScalef(
            model.scale,
            model.scale,
            model.scale);

        // ----------------------------------------------
        // GPU mesh rendering
        // ----------------------------------------------

        if (!BuildGpuMesh(model))
        {
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();

            glPopAttrib();

            g_UseProgram(
                static_cast<GLuint>(oldProgram));

            if (g_ActiveTexture)
            {
                g_ActiveTexture(
                    static_cast<GLenum>(oldActiveTexture));
            }

            glMatrixMode(
                static_cast<GLenum>(oldMatrixMode));

            return;
        }

        glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

        g_UseProgram(g_ShaderProgram);

        g_Uniform1i(g_UniformTexture, 0);
        g_Uniform3f(
            g_UniformLightDirection,
            LIGHT_X,
            LIGHT_Y,
            LIGHT_Z);

        g_Uniform1f(g_UniformAmbient, AMBIENT_LIGHT);
        g_Uniform1f(g_UniformDiffuse, DIFFUSE_LIGHT);

        if (g_ActiveTexture)
            g_ActiveTexture(GL_TEXTURE0);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        for (MaterialBatch &batch : model.gpuBatches)
        {
            if (!batch.vertexBuffer ||
                batch.vertexCount <= 0)
            {
                continue;
            }

            if (batch.materialIndex < 0 ||
                static_cast<size_t>(batch.materialIndex) >=
                    model.materials.size())
            {
                continue;
            }

            Material &material =
                model.materials[batch.materialIndex];

            const bool textured =
                UploadMaterialTexture(material);

            glColor4f(
                material.diffuse[0],
                material.diffuse[1],
                material.diffuse[2],
                1.0f);

            g_Uniform1i(
                g_UniformUseTexture,
                textured ? 1 : 0);

            if (textured)
            {
                glBindTexture(
                    GL_TEXTURE_2D,
                    material.textureId);
            }

            g_BindBuffer(
                GL_ARRAY_BUFFER,
                batch.vertexBuffer);

            glVertexPointer(
                3,
                GL_FLOAT,
                sizeof(GpuVertex),
                reinterpret_cast<const void *>(
                    offsetof(GpuVertex, position)));

            glNormalPointer(
                GL_FLOAT,
                sizeof(GpuVertex),
                reinterpret_cast<const void *>(
                    offsetof(GpuVertex, normal)));

            glTexCoordPointer(
                2,
                GL_FLOAT,
                sizeof(GpuVertex),
                reinterpret_cast<const void *>(
                    offsetof(GpuVertex, texcoord)));

            while (glGetError() != GL_NO_ERROR)
            {
                // Clear errors from earlier rendering operations.
            }

            g_DrawArrays(
                GL_TRIANGLES,
                0,
                batch.vertexCount);

            const GLenum drawError = glGetError();

            if (drawError != GL_NO_ERROR)
            {
                char message[256];

                snprintf(
                    message,
                    sizeof(message),
                    "GPU draw failed for %s: OpenGL error 0x%X",
                    model.path.c_str(),
                    drawError);

                ViewPoint::LogMessage(message);
            }
        }

        g_BindBuffer(GL_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glPopClientAttrib();

        g_UseProgram(0);

        // ----------------------------------------------
        // Restore state
        // ----------------------------------------------

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glPopAttrib();

        g_UseProgram(
            static_cast<GLuint>(oldProgram));

        if (g_ActiveTexture)
        {
            g_ActiveTexture(
                static_cast<GLenum>(oldActiveTexture));
        }

        glMatrixMode(
            static_cast<GLenum>(oldMatrixMode));
    }
    }
 // MAIN RENDERER

    static void RenderTriangleMesh(HWND window)
    {
        if (!EnsureContext())
            return;

        UpdateCamera(window);

        // Detect configuration changes.
        CheckConfigurationReload();

        // Initial scene loading.
        if (!g_SceneAttempted)
        {
            g_SceneAttempted = true;

            if (!LoadConfiguredScene())
            {
                ViewPoint::LogMessage(
                    "Initial scene loading failed.");
            }
        }

        if (g_Models.empty())
            return;

        // Clear the depth buffer once for the whole scene.
        // Preserve the game's depth/scissor state.
        glPushAttrib(
            GL_DEPTH_BUFFER_BIT |
            GL_SCISSOR_BIT);

        glDisable(GL_SCISSOR_TEST);
        glDepthMask(GL_TRUE);
        glClearDepth(1.0);
        glClear(GL_DEPTH_BUFFER_BIT);

        glPopAttrib();

        // Render every model using the same depth buffer.
        for (Model &model : g_Models)
        {
            if (model.loaded)
            {
                RenderModel(model);
            }
        }
    }
}
