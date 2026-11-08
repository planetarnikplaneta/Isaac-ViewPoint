#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl/GL.h>

#include <cstddef>
#include <filesystem>
#include <vector>

#include "Types.h"

namespace ViewPoint
{
    // OpenGL function pointer types.
    typedef void (APIENTRY* PFNGLUSEPROGRAMPROC)(GLuint program);
    typedef void (APIENTRY* PFNGLACTIVETEXTUREPROC)(GLenum texture);
    typedef void (APIENTRY* PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
    typedef void (APIENTRY* PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
    typedef void (APIENTRY* PFNGLBUFFERDATAPROC)(GLenum target, std::ptrdiff_t size, const void* data, GLenum usage);
    typedef void (APIENTRY* PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);

    typedef GLuint (APIENTRY* PFNGLCREATESHADERPROC)(GLenum type);
    typedef void (APIENTRY* PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const char* const* string, const GLint* length);
    typedef void (APIENTRY* PFNGLCOMPILESHADERPROC)(GLuint shader);
    typedef void (APIENTRY* PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
    typedef void (APIENTRY* PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei maxLength, GLsizei* length, char* infoLog);
    typedef void (APIENTRY* PFNGLDELETESHADERPROC)(GLuint shader);

    typedef GLuint (APIENTRY* PFNGLCREATEPROGRAMPROC)();
    typedef void (APIENTRY* PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
    typedef void (APIENTRY* PFNGLLINKPROGRAMPROC)(GLuint program);
    typedef void (APIENTRY* PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
    typedef void (APIENTRY* PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei maxLength, GLsizei* length, char* infoLog);
    typedef void (APIENTRY* PFNGLDELETEPROGRAMPROC)(GLuint program);

    typedef GLint (APIENTRY* PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const char* name);
    typedef void (APIENTRY* PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
    typedef void (APIENTRY* PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
    typedef void (APIENTRY* PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    typedef void (APIENTRY* PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);

    // Module and OpenGL context.
    extern HMODULE g_Module;
    extern HGLRC g_ResourceContext;
    extern HGLRC g_SceneContext;
    extern HWND g_RenderWindow;

    // OpenGL function pointers.
    extern PFNGLUSEPROGRAMPROC g_UseProgram;
    extern PFNGLACTIVETEXTUREPROC g_ActiveTexture;
    extern PFNGLGENBUFFERSPROC g_GenBuffers;
    extern PFNGLBINDBUFFERPROC g_BindBuffer;
    extern PFNGLBUFFERDATAPROC g_BufferData;
    extern PFNGLDELETEBUFFERSPROC g_DeleteBuffers;

    extern PFNGLCREATESHADERPROC g_CreateShader;
    extern PFNGLSHADERSOURCEPROC g_ShaderSource;
    extern PFNGLCOMPILESHADERPROC g_CompileShader;
    extern PFNGLGETSHADERIVPROC g_GetShaderiv;
    extern PFNGLGETSHADERINFOLOGPROC g_GetShaderInfoLog;
    extern PFNGLDELETESHADERPROC g_DeleteShader;

    extern PFNGLCREATEPROGRAMPROC g_CreateProgram;
    extern PFNGLATTACHSHADERPROC g_AttachShader;
    extern PFNGLLINKPROGRAMPROC g_LinkProgram;
    extern PFNGLGETPROGRAMIVPROC g_GetProgramiv;
    extern PFNGLGETPROGRAMINFOLOGPROC g_GetProgramInfoLog;
    extern PFNGLDELETEPROGRAMPROC g_DeleteProgram;

    extern PFNGLGETUNIFORMLOCATIONPROC g_GetUniformLocation;
    extern PFNGLUNIFORM1IPROC g_Uniform1i;
    extern PFNGLUNIFORM1FPROC g_Uniform1f;
    extern PFNGLUNIFORM3FPROC g_Uniform3f;
    extern PFNGLDRAWARRAYSPROC g_DrawArrays;

    // Shader state.
    extern GLuint g_ShaderProgram;
    extern GLint g_UniformTexture;
    extern GLint g_UniformUseTexture;
    extern GLint g_UniformLightDirection;
    extern GLint g_UniformAmbient;
    extern GLint g_UniformDiffuse;

    // Scene and camera state.
    extern std::vector<Model> g_Models;
    extern std::vector<ObjectConfig> g_ObjectConfigs;
    extern Camera g_Camera;
    extern bool g_CursorCaptured;
    extern bool g_SceneAttempted;

    // Configuration reload state.
    extern std::filesystem::file_time_type g_ConfigLastWriteTime;
    extern bool g_ConfigTimestampValid;
    extern unsigned int g_ConfigCheckCounter;
}
