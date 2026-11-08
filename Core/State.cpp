#include "State.h"

namespace ViewPoint
{
    HMODULE g_Module = nullptr;
    HGLRC g_ResourceContext = nullptr;
    HGLRC g_SceneContext = nullptr;

    PFNGLUSEPROGRAMPROC g_UseProgram = nullptr;
    PFNGLACTIVETEXTUREPROC g_ActiveTexture = nullptr;
    PFNGLGENBUFFERSPROC g_GenBuffers = nullptr;
    PFNGLBINDBUFFERPROC g_BindBuffer = nullptr;
    PFNGLBUFFERDATAPROC g_BufferData = nullptr;
    PFNGLDELETEBUFFERSPROC g_DeleteBuffers = nullptr;

    PFNGLCREATESHADERPROC g_CreateShader = nullptr;
    PFNGLSHADERSOURCEPROC g_ShaderSource = nullptr;
    PFNGLCOMPILESHADERPROC g_CompileShader = nullptr;
    PFNGLGETSHADERIVPROC g_GetShaderiv = nullptr;
    PFNGLGETSHADERINFOLOGPROC g_GetShaderInfoLog = nullptr;
    PFNGLDELETESHADERPROC g_DeleteShader = nullptr;

    PFNGLCREATEPROGRAMPROC g_CreateProgram = nullptr;
    PFNGLATTACHSHADERPROC g_AttachShader = nullptr;
    PFNGLLINKPROGRAMPROC g_LinkProgram = nullptr;
    PFNGLGETPROGRAMIVPROC g_GetProgramiv = nullptr;
    PFNGLGETPROGRAMINFOLOGPROC g_GetProgramInfoLog = nullptr;
    PFNGLDELETEPROGRAMPROC g_DeleteProgram = nullptr;

    PFNGLGETUNIFORMLOCATIONPROC g_GetUniformLocation = nullptr;
    PFNGLUNIFORM1IPROC g_Uniform1i = nullptr;
    PFNGLUNIFORM1FPROC g_Uniform1f = nullptr;
    PFNGLUNIFORM3FPROC g_Uniform3f = nullptr;
    PFNGLDRAWARRAYSPROC g_DrawArrays = nullptr;

    GLuint g_ShaderProgram = 0;
    GLint g_UniformTexture = -1;
    GLint g_UniformUseTexture = -1;
    GLint g_UniformLightDirection = -1;
    GLint g_UniformAmbient = -1;
    GLint g_UniformDiffuse = -1;

    std::vector<Model> g_Models;
    std::vector<ObjectConfig> g_ObjectConfigs;
    Camera g_Camera;

    bool g_CursorCaptured = false;
    bool g_SceneAttempted = false;

    std::filesystem::file_time_type g_ConfigLastWriteTime{};
    bool g_ConfigTimestampValid = false;
    unsigned int g_ConfigCheckCounter = 0;
}
