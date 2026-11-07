#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl/GL.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cstddef>

#include "libzhl.h"
#include "HookSystem.h"


#include "Core/Logger.h"
#include "Core/Types.h"

using namespace ViewPoint;


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "User32.lib")

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

using PFNGLUSEPROGRAMPROC = void(APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void(APIENTRY *)(GLenum);

using PFNGLGENBUFFERSPROC =
    void(APIENTRY *)(GLsizei, GLuint *);

using PFNGLBINDBUFFERPROC =
    void(APIENTRY *)(GLenum, GLuint);

using PFNGLBUFFERDATAPROC =
    void(APIENTRY *)(GLenum, ptrdiff_t, const void *, GLenum);

using PFNGLDELETEBUFFERSPROC =
    void(APIENTRY *)(GLsizei, const GLuint *);

using PFNGLCREATESHADERPROC =
    GLuint(APIENTRY *)(GLenum);

using PFNGLSHADERSOURCEPROC =
    void(APIENTRY *)(GLuint, GLsizei, const char *const *, const GLint *);

using PFNGLCOMPILESHADERPROC =
    void(APIENTRY *)(GLuint);

using PFNGLGETSHADERIVPROC =
    void(APIENTRY *)(GLuint, GLenum, GLint *);

using PFNGLGETSHADERINFOLOGPROC =
    void(APIENTRY *)(GLuint, GLsizei, GLsizei *, char *);

using PFNGLDELETESHADERPROC =
    void(APIENTRY *)(GLuint);

using PFNGLCREATEPROGRAMPROC =
    GLuint(APIENTRY *)();

using PFNGLATTACHSHADERPROC =
    void(APIENTRY *)(GLuint, GLuint);

using PFNGLLINKPROGRAMPROC =
    void(APIENTRY *)(GLuint);

using PFNGLGETPROGRAMIVPROC =
    void(APIENTRY *)(GLuint, GLenum, GLint *);

using PFNGLGETPROGRAMINFOLOGPROC =
    void(APIENTRY *)(GLuint, GLsizei, GLsizei *, char *);

using PFNGLDELETEPROGRAMPROC =
    void(APIENTRY *)(GLuint);

using PFNGLGETUNIFORMLOCATIONPROC =
    GLint(APIENTRY *)(GLuint, const char *);

using PFNGLUNIFORM1IPROC =
    void(APIENTRY *)(GLint, GLint);

using PFNGLUNIFORM1FPROC =
    void(APIENTRY *)(GLint, GLfloat);

using PFNGLUNIFORM3FPROC =
    void(APIENTRY *)(GLint, GLfloat, GLfloat, GLfloat);

using PFNGLDRAWARRAYSPROC =
    void(APIENTRY *)(GLenum, GLint, GLsizei);

namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}

namespace
{
    namespace fs = std::filesystem;

    // CONFIGURATION

    constexpr char DEFAULT_OBJECT[] = "objects/sphere.obj";

    constexpr char LOG_FILE[] = "C:\\IsaacViewPoint.log";
    constexpr char CONFIG_FILE[] = "IsaacViewPoint.ini";

    constexpr float OBJECT_DISTANCE = 5.0f;
    constexpr float OBJECT_ROTATION_SPEED = 0.012f;
    constexpr float OBJECT_TILT = -12.0f;
    constexpr float OBJECT_FOV = 45.0f;

    constexpr float LIGHT_X = -0.35f;
    constexpr float LIGHT_Y = 0.55f;
    constexpr float LIGHT_Z = -0.76f;

    constexpr float AMBIENT_LIGHT = 0.40f;
    constexpr float DIFFUSE_LIGHT = 0.60f;

    // GLOBAL STATE

    static HMODULE g_Module = nullptr;

    static HGLRC g_ResourceContext = nullptr;

    static PFNGLUSEPROGRAMPROC g_UseProgram = nullptr;
    static PFNGLACTIVETEXTUREPROC g_ActiveTexture = nullptr;
    static PFNGLGENBUFFERSPROC g_GenBuffers = nullptr;
    static PFNGLBINDBUFFERPROC g_BindBuffer = nullptr;
    static PFNGLBUFFERDATAPROC g_BufferData = nullptr;
    static PFNGLDELETEBUFFERSPROC g_DeleteBuffers = nullptr;

    static PFNGLCREATESHADERPROC g_CreateShader = nullptr;
    static PFNGLSHADERSOURCEPROC g_ShaderSource = nullptr;
    static PFNGLCOMPILESHADERPROC g_CompileShader = nullptr;
    static PFNGLGETSHADERIVPROC g_GetShaderiv = nullptr;
    static PFNGLGETSHADERINFOLOGPROC g_GetShaderInfoLog = nullptr;
    static PFNGLDELETESHADERPROC g_DeleteShader = nullptr;

    static PFNGLCREATEPROGRAMPROC g_CreateProgram = nullptr;
    static PFNGLATTACHSHADERPROC g_AttachShader = nullptr;
    static PFNGLLINKPROGRAMPROC g_LinkProgram = nullptr;
    static PFNGLGETPROGRAMIVPROC g_GetProgramiv = nullptr;
    static PFNGLGETPROGRAMINFOLOGPROC g_GetProgramInfoLog = nullptr;
    static PFNGLDELETEPROGRAMPROC g_DeleteProgram = nullptr;

    static PFNGLGETUNIFORMLOCATIONPROC g_GetUniformLocation = nullptr;
    static PFNGLUNIFORM1IPROC g_Uniform1i = nullptr;
    static PFNGLUNIFORM1FPROC g_Uniform1f = nullptr;
    static PFNGLUNIFORM3FPROC g_Uniform3f = nullptr;
    static PFNGLDRAWARRAYSPROC g_DrawArrays = nullptr;

    static GLuint g_ShaderProgram = 0;

    static GLint g_UniformTexture = -1;
    static GLint g_UniformUseTexture = -1;
    static GLint g_UniformLightDirection = -1;
    static GLint g_UniformAmbient = -1;
    static GLint g_UniformDiffuse = -1;

    static std::vector<Model> g_Models;

    static std::vector<ObjectConfig> g_ObjectConfigs;
    static Camera g_Camera;

    static bool g_CursorCaptured = false;
    static bool g_SceneAttempted = false;

    // Configuration hot-reload state.
    static fs::file_time_type g_ConfigLastWriteTime{};
    static bool g_ConfigTimestampValid = false;

    static unsigned int g_ConfigCheckCounter = 0;

    constexpr unsigned int CONFIG_CHECK_INTERVAL = 60;

    // STRING HELPERS

    static std::string Trim(const std::string &text)
    {
        const size_t first =
            text.find_first_not_of(" \t\r\n");

        if (first == std::string::npos)
            return {};

        const size_t last =
            text.find_last_not_of(" \t\r\n");

        return text.substr(
            first,
            last - first + 1);
    }

    static std::string NormalizeAssetPath(
        std::string path)
    {
        std::replace(
            path.begin(),
            path.end(),
            '\\',
            '/');

        while (path.rfind("./", 0) == 0)
            path.erase(0, 2);

        if (path.empty() ||
            path[0] == '/' ||
            (path.size() > 1 && path[1] == ':'))
        {
            return {};
        }

        std::stringstream stream(path);

        std::string part;
        std::vector<std::string> parts;

        while (std::getline(stream, part, '/'))
        {
            if (part.empty() || part == ".")
                continue;

            if (part == "..")
                return {};

            parts.push_back(part);
        }

        std::string result;

        for (const std::string &p : parts)
        {
            if (!result.empty())
                result += '/';

            result += p;
        }

        return result;
    }

    static std::string ResolveRelativeAsset(
        const std::string &parent,
        const std::string &child)
    {
        std::string normalizedChild = child;

        std::replace(
            normalizedChild.begin(),
            normalizedChild.end(),
            '\\',
            '/');

        if (normalizedChild.empty() ||
            normalizedChild[0] == '/' ||
            (normalizedChild.size() > 1 &&
             normalizedChild[1] == ':'))
        {
            return {};
        }

        const size_t slash =
            parent.find_last_of('/');

        const std::string directory =
            slash == std::string::npos
                ? ""
                : parent.substr(0, slash + 1);

        return NormalizeAssetPath(
            directory + normalizedChild);
    }

    static std::string ToUpperResourceName(
        const std::string &name)
    {
        std::string result = name;

        for (char &c : result)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = static_cast<char>(
                    c - 'a' + 'A');
            }
        }

        return result;
    }

    // DLL DIRECTORY

    static fs::path GetDllDirectory()
    {
        char modulePath[MAX_PATH] = {};

        DWORD length = GetModuleFileNameA(
            g_Module,
            modulePath,
            MAX_PATH);

        if (!length || length >= MAX_PATH)
            return fs::current_path();

        return fs::path(
                   std::string(modulePath, length))
            .parent_path();
    }
    // CONFIGURATION FILE

    static fs::path GetConfigurationPath()
    {
        return GetDllDirectory() / CONFIG_FILE;
    }

    static bool ParseVector3Text(
        const std::string &text,
        Vertex3 &output)
    {
        std::istringstream stream(text);

        std::string x;
        std::string y;
        std::string z;
        std::string extra;

        if (!std::getline(stream, x, ',') ||
            !std::getline(stream, y, ',') ||
            !std::getline(stream, z, ','))
        {
            return false;
        }

        if (std::getline(stream, extra, ','))
            return false;

        try
        {
            size_t usedX = 0;
            size_t usedY = 0;
            size_t usedZ = 0;

            output.x = std::stof(Trim(x), &usedX);
            output.y = std::stof(Trim(y), &usedY);
            output.z = std::stof(Trim(z), &usedZ);

            if (usedX != Trim(x).size() ||
                usedY != Trim(y).size() ||
                usedZ != Trim(z).size())
            {
                return false;
            }

            return std::isfinite(output.x) &&
                   std::isfinite(output.y) &&
                   std::isfinite(output.z);
        }
        catch (...)
        {
            return false;
        }
    }

    static bool ParseObjectConfiguration(
        const std::string &value,
        ObjectConfig &output)
    {
        std::istringstream stream(value);

        std::string path;
        std::string position;
        std::string rotation;
        std::string scale;
        std::string extra;

        if (!std::getline(stream, path, '|') ||
            !std::getline(stream, position, '|') ||
            !std::getline(stream, rotation, '|') ||
            !std::getline(stream, scale, '|'))
        {
            return false;
        }

        if (std::getline(stream, extra, '|'))
            return false;

        path = Trim(path);
        position = Trim(position);
        rotation = Trim(rotation);
        scale = Trim(scale);

        if (path.size() >= 2 &&
            path.front() == '"' &&
            path.back() == '"')
        {
            path = path.substr(1, path.size() - 2);
        }

        output.path = NormalizeAssetPath(path);

        if (output.path.empty())
            return false;

        if (!ParseVector3Text(position, output.position))
            return false;

        if (!ParseVector3Text(rotation, output.rotation))
            return false;

        try
        {
            size_t used = 0;

            output.scale = std::stof(scale, &used);

            if (used != scale.size() ||
                !std::isfinite(output.scale) ||
                output.scale <= 0.0f)
            {
                return false;
            }
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    static bool ReadConfiguration(
        std::vector<ObjectConfig> &output)
    {
        output.clear();

        const fs::path configPath = GetConfigurationPath();

        std::ifstream file(configPath);

        if (!file)
            return false;

        std::string legacyModel;

        std::string line;

        while (std::getline(file, line))
        {
            line = Trim(line);

            if (line.empty() ||
                line[0] == '#' ||
                line[0] == ';' ||
                line[0] == '[')
            {
                continue;
            }

            const size_t equals = line.find('=');

            if (equals == std::string::npos)
                continue;

            const std::string key =
                Trim(line.substr(0, equals));

            const std::string value =
                Trim(line.substr(equals + 1));

            if (key == "Model")
            {
                legacyModel = value;
            }
            else if (key == "Object")
            {
                ObjectConfig object;

                if (!ParseObjectConfiguration(value, object))
                {
                    ViewPoint::LogMessage(
                        ("Invalid Object configuration: " +
                         value)
                            .c_str());

                    return false;
                }

                output.push_back(std::move(object));
            }
        }

        // Backwards compatibility with the old Model= format.
        if (output.empty())
        {
            ObjectConfig object;

            std::string path =
                legacyModel.empty()
                    ? DEFAULT_OBJECT
                    : legacyModel;

            if (path.size() >= 2 &&
                path.front() == '"' &&
                path.back() == '"')
            {
                path = path.substr(1, path.size() - 2);
            }

            object.path = NormalizeAssetPath(path);

            if (object.path.empty())
            {
                ViewPoint::LogMessage(
                    "Invalid Model path in configuration.");

                return false;
            }

            output.push_back(std::move(object));
        }

        return true;
    }

    static void UpdateConfigurationTimestamp()
    {
        std::error_code error;

        const fs::file_time_type timestamp =
            fs::last_write_time(
                GetConfigurationPath(),
                error);

        if (error)
        {
            g_ConfigTimestampValid = false;
            return;
        }

        g_ConfigLastWriteTime = timestamp;
        g_ConfigTimestampValid = true;
    }

    static void LoadConfiguration()
    {
        std::vector<ObjectConfig> configuredObjects;

        if (!ReadConfiguration(configuredObjects))
        {
            ViewPoint::LogMessage(
                "Configuration file not found or invalid; using default model.");

            configuredObjects.clear();

            ObjectConfig defaultObject;
            defaultObject.path = DEFAULT_OBJECT;

            configuredObjects.push_back(defaultObject);
        }

        g_ObjectConfigs = std::move(configuredObjects);

        ViewPoint::LogNumber(
            "Configured object count",
            g_ObjectConfigs.size());

        for (size_t i = 0; i < g_ObjectConfigs.size(); ++i)
        {
            ViewPoint::LogMessage(
                ("Configured object " +
                 std::to_string(i) + ": " +
                 g_ObjectConfigs[i].path)
                    .c_str());
        }

        UpdateConfigurationTimestamp();
    }

    // EMBEDDED RESOURCE LOOKUP

    static HRSRC FindEmbeddedResource(
        HMODULE module,
        const std::string &assetPath)
    {
        const std::string resourceName =
            ToUpperResourceName(assetPath);

        HRSRC resource = FindResourceA(
            module,
            resourceName.c_str(),
            RT_RCDATA);

        if (resource)
            return resource;

        // The current generated resources use literal
        // quotation marks in their resource names.
        const std::string quotedName =
            "\"" + resourceName + "\"";

        resource = FindResourceA(
            module,
            quotedName.c_str(),
            RT_RCDATA);

        if (resource)
        {
            ViewPoint::LogMessage(
                ("Found quoted resource name: " +
                 quotedName)
                    .c_str());

            return resource;
        }

        char message[512];

        snprintf(
            message,
            sizeof(message),
            "Resource not found: %s",
            assetPath.c_str());

        ViewPoint::LogMessage(message);

        return nullptr;
    }

    // ASSET LOADING

    static bool ReadAsset(
        const std::string &requestedPath,
        std::vector<unsigned char> &output)
    {
        const std::string assetPath =
            NormalizeAssetPath(requestedPath);

        if (assetPath.empty())
            return false;

        output.clear();

        // ----------------------------------------------
        // External assets override embedded assets.
        // ----------------------------------------------

        try
        {
            const fs::path externalPath =
                GetDllDirectory() /
                "resources_ViewPoint" /
                fs::path(assetPath);

            if (fs::exists(externalPath) &&
                fs::is_regular_file(externalPath))
            {
                std::ifstream file(
                    externalPath,
                    std::ios::binary);

                if (file)
                {
                    file.seekg(0, std::ios::end);

                    const std::streamoff size =
                        file.tellg();

                    if (size <= 0)
                        return false;

                    file.seekg(0, std::ios::beg);

                    output.resize(
                        static_cast<size_t>(size));

                    file.read(
                        reinterpret_cast<char *>(
                            output.data()),
                        size);

                    if (file)
                    {
                        ViewPoint::LogMessage(
                            ("Loaded external asset: " +
                             assetPath)
                                .c_str());

                        return true;
                    }

                    output.clear();
                }
            }
        }
        catch (...)
        {
            ViewPoint::LogMessage(
                "External asset access failed.");
        }

        // ----------------------------------------------
        // Embedded Windows resource.
        // ----------------------------------------------

        HRSRC resource = FindEmbeddedResource(
            g_Module,
            assetPath);

        if (!resource)
        {
            ViewPoint::LogMessage(
                ("Asset not found: " +
                 assetPath)
                    .c_str());

            return false;
        }

        HGLOBAL loaded = LoadResource(
            g_Module,
            resource);

        if (!loaded)
            return false;

        const DWORD size = SizeofResource(
            g_Module,
            resource);

        const void *data = LockResource(loaded);

        if (!data || size == 0)
            return false;

        const unsigned char *bytes =
            static_cast<const unsigned char *>(data);

        output.assign(
            bytes,
            bytes + size);

        return true;
    }

    // OBJ INDEX PARSING

    static bool ParseObjIndex(
        const std::string &token,
        int component,
        size_t count,
        int32_t &output)
    {
        size_t start = 0;

        for (int i = 0; i < component; ++i)
        {
            const size_t slash =
                token.find('/', start);

            if (slash == std::string::npos)
                return false;

            start = slash + 1;
        }

        size_t end =
            token.find('/', start);

        if (end == std::string::npos)
            end = token.size();

        if (start >= end)
            return false;

        const std::string number =
            token.substr(start, end - start);

        char *parseEnd = nullptr;

        const long value = strtol(
            number.c_str(),
            &parseEnd,
            10);

        if (!parseEnd || *parseEnd || value == 0)
            return false;

        const long resolved =
            value > 0
                ? value - 1
                : static_cast<long>(count) + value;

        if (resolved < 0 ||
            static_cast<size_t>(resolved) >= count)
        {
            return false;
        }

        output = static_cast<int32_t>(resolved);

        return true;
    }

    // MATERIAL MANAGEMENT

    static int FindOrCreateMaterial(
        const std::string &name,
        std::map<std::string, int> &lookup,
        Model &model)
    {
        auto found = lookup.find(name);

        if (found != lookup.end())
            return found->second;

        Material material;
        material.name = name;

        const int index =
            static_cast<int>(model.materials.size());

        model.materials.push_back(
            std::move(material));

        lookup[name] = index;

        return index;
    }

    // MTL TEXTURE PATH PARSING

    static std::string GetMapFilename(
        std::istringstream &stream)
    {
        std::vector<std::string> tokens;

        std::string token;

        while (stream >> token)
            tokens.push_back(token);

        if (tokens.empty())
            return {};

        // Handle common MTL map options.
        size_t i = 0;

        while (i < tokens.size())
        {
            const std::string &option = tokens[i];

            if (option.empty() || option[0] != '-')
                break;

            size_t argumentCount = 0;

            if (option == "-blendu" ||
                option == "-blendv" ||
                option == "-cc" ||
                option == "-clamp" ||
                option == "-texres" ||
                option == "-bm" ||
                option == "-imfchan" ||
                option == "-type")
            {
                argumentCount = 1;
            }
            else if (option == "-mm")
            {
                argumentCount = 2;
            }
            else if (option == "-o" ||
                     option == "-s" ||
                     option == "-t")
            {
                argumentCount = 3;
            }
            else
            {
                // Unknown option: use the final token
                // as the texture filename.
                return tokens.back();
            }

            ++i;

            for (size_t n = 0;
                 n < argumentCount && i < tokens.size();
                 ++n)
            {
                // Vector options may provide one,
                // two or three values.
                if ((option == "-o" ||
                     option == "-s" ||
                     option == "-t") &&
                    i < tokens.size() &&
                    !tokens[i].empty() &&
                    tokens[i][0] == '-')
                {
                    break;
                }

                ++i;
            }
        }

        if (i >= tokens.size())
            return {};

        // Filenames containing spaces are not supported
        // by this simple whitespace-based parser.
        return tokens[i];
    }

    // MTL LOADING

    static void LoadMTL(
        Model &model,
        const std::string &mtlPath,
        std::map<std::string, int> &lookup)
    {
        std::vector<unsigned char> bytes;

        if (!ReadAsset(mtlPath, bytes))
        {
            ViewPoint::LogMessage(
                ("Cannot load MTL: " +
                 mtlPath)
                    .c_str());

            return;
        }

        const std::string source(
            reinterpret_cast<const char *>(bytes.data()),
            bytes.size());

        std::istringstream input(source);

        std::string line;

        int currentMaterial = -1;

        while (std::getline(input, line))
        {
            line = Trim(line);

            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream stream(line);

            std::string command;
            stream >> command;

            if (command == "newmtl")
            {
                std::string name;

                std::getline(stream, name);
                name = Trim(name);

                if (!name.empty())
                {
                    currentMaterial =
                        FindOrCreateMaterial(
                            name,
                            lookup,
                            model);
                }

                continue;
            }

            if (currentMaterial < 0)
                continue;

            Material &material =
                model.materials[currentMaterial];

            if (command == "Ka")
            {
                stream >>
                    material.ambient[0] >>
                    material.ambient[1] >>
                    material.ambient[2];
            }
            else if (command == "Kd")
            {
                stream >>
                    material.diffuse[0] >>
                    material.diffuse[1] >>
                    material.diffuse[2];
            }
            else if (command == "Ks")
            {
                stream >>
                    material.specular[0] >>
                    material.specular[1] >>
                    material.specular[2];
            }
            else if (command == "Ns")
            {
                stream >> material.shininess;
            }
            else if (command == "map_Kd")
            {
                const std::string texture =
                    GetMapFilename(stream);

                if (!texture.empty())
                {
                    material.diffuseTexturePath =
                        ResolveRelativeAsset(
                            mtlPath,
                            texture);

                    ViewPoint::LogMessage(
                        ("Material texture: " +
                         material.name + " -> " +
                         material.diffuseTexturePath)
                            .c_str());
                }
            }
        }

        ViewPoint::LogMessage(
            ("Loaded MTL: " + mtlPath).c_str());
    }

    // TEXTURE LOADING

    static void LoadMaterialTexture(
        Material &material)
    {
        if (material.textureAttempted)
            return;

        material.textureAttempted = true;

        if (material.diffuseTexturePath.empty())
            return;

        std::vector<unsigned char> bytes;

        if (!ReadAsset(
                material.diffuseTexturePath,
                bytes))
        {
            ViewPoint::LogMessage(
                ("Cannot load texture: " +
                 material.diffuseTexturePath)
                    .c_str());

            return;
        }

        if (bytes.size() >
            static_cast<size_t>(INT_MAX))
        {
            ViewPoint::LogMessage("Texture file is too large.");
            return;
        }

        int channels = 0;

        stbi_set_flip_vertically_on_load(1);

        unsigned char *decoded = stbi_load_from_memory(
            bytes.data(),
            static_cast<int>(bytes.size()),
            &material.width,
            &material.height,
            &channels,
            4);

        if (!decoded)
        {
            ViewPoint::LogMessage(
                ("PNG decoding failed: " +
                 material.diffuseTexturePath)
                    .c_str());

            return;
        }

        const size_t pixelSize =
            static_cast<size_t>(material.width) *
            static_cast<size_t>(material.height) * 4;

        material.pixels.assign(
            decoded,
            decoded + pixelSize);

        stbi_image_free(decoded);

        char message[256];

        snprintf(
            message,
            sizeof(message),
            "Decoded texture: %s (%dx%d, source channels=%d)",
            material.diffuseTexturePath.c_str(),
            material.width,
            material.height,
            channels);

        ViewPoint::LogMessage(message);
    }

    // TEXTURE UPLOAD

    static bool UploadMaterialTexture(
        Material &material)
    {
        LoadMaterialTexture(material);

        if (material.pixels.empty())
            return false;

        if (material.textureId != 0)
            return true;

        glGenTextures(
            1,
            &material.textureId);

        if (!material.textureId)
            return false;

        glBindTexture(
            GL_TEXTURE_2D,
            material.textureId);

        glPixelStorei(
            GL_UNPACK_ALIGNMENT,
            1);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            material.width,
            material.height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            material.pixels.data());

        const GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            char message[128];

            snprintf(
                message,
                sizeof(message),
                "Texture upload failed: 0x%X",
                error);

            ViewPoint::LogMessage(message);

            glDeleteTextures(
                1,
                &material.textureId);

            material.textureId = 0;

            return false;
        }

        return true;
    }

    // MODEL TEXTURE CLEANUP

    static void ReleaseModelTextures(Model &model)
    {
        // OpenGL resources can only be deleted when their
        // owning context is current.
        if (!wglGetCurrentContext())
            return;

        for (Material &material : model.materials)
        {
            if (material.textureId != 0)
            {
                glDeleteTextures(
                    1,
                    &material.textureId);

                material.textureId = 0;
            }
        }
    }
    // MODEL BOUNDING BOX / NORMALIZATION

    static void NormalizeModel(Model &model)
    {
        if (model.vertices.empty())
            return;

        Vertex3 lo = model.vertices.front();
        Vertex3 hi = model.vertices.front();

        for (const Vertex3 &v : model.vertices)
        {
            lo.x = (std::min)(lo.x, v.x);
            lo.y = (std::min)(lo.y, v.y);
            lo.z = (std::min)(lo.z, v.z);

            hi.x = (std::max)(hi.x, v.x);
            hi.y = (std::max)(hi.y, v.y);
            hi.z = (std::max)(hi.z, v.z);
        }

        const float cx = (lo.x + hi.x) * 0.5f;
        const float cy = (lo.y + hi.y) * 0.5f;
        const float cz = (lo.z + hi.z) * 0.5f;

        const float extent = (std::max)((std::max)(hi.x - lo.x, hi.y - lo.y),
                                        (std::max)(hi.z - lo.z, 0.0001f));

        const float scale = 2.0f / extent;

        for (Vertex3 &v : model.vertices)
        {
            v.x = (v.x - cx) * scale;
            v.y = (v.y - cy) * scale;
            v.z = (v.z - cz) * scale;
        }
    }

    // OBJ LOADING

    static bool LoadOBJ(Model &model)
    {
        model.attempted = true;
        model.loaded = false;

        model.vertices.clear();
        model.texcoords.clear();
        model.normals.clear();
        model.triangles.clear();
        model.materials.clear();

        std::vector<unsigned char> bytes;

        if (!ReadAsset(model.path, bytes))
        {
            ViewPoint::LogMessage(
                ("Cannot load OBJ: " +
                 model.path)
                    .c_str());

            return false;
        }

        const std::string source(
            reinterpret_cast<const char *>(bytes.data()),
            bytes.size());

        std::istringstream input(source);

        std::string line;

        std::map<std::string, int> materialLookup;

        Material defaultMaterial;
        defaultMaterial.name = "__default";

        model.materials.push_back(
            std::move(defaultMaterial));

        materialLookup["__default"] = 0;

        int activeMaterial = 0;

        size_t facesWithoutUV = 0;
        size_t facesWithoutNormals = 0;

        while (std::getline(input, line))
        {
            line = Trim(line);

            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream stream(line);

            std::string command;
            stream >> command;

            // ------------------------------------------
            // Vertex position
            // ------------------------------------------

            if (command == "v")
            {
                Vertex3 vertex;

                if (stream >>
                    vertex.x >>
                    vertex.y >>
                    vertex.z)
                {
                    model.vertices.push_back(vertex);
                }
            }

            // ------------------------------------------
            // Texture coordinates
            // ------------------------------------------

            else if (command == "vt")
            {
                Vertex2 uv;

                if (stream >> uv.u >> uv.v)
                {
                    model.texcoords.push_back(uv);
                }
            }

            // ------------------------------------------
            // Normals
            // ------------------------------------------

            else if (command == "vn")
            {
                Vertex3 normal;

                if (stream >>
                    normal.x >>
                    normal.y >>
                    normal.z)
                {
                    model.normals.push_back(normal);
                }
            }

            // ------------------------------------------
            // Material libraries
            // ------------------------------------------

            else if (command == "mtllib")
            {
                std::string filename;

                while (stream >> filename)
                {
                    const std::string mtlPath =
                        ResolveRelativeAsset(
                            model.path,
                            filename);

                    if (!mtlPath.empty())
                    {
                        LoadMTL(
                            model,
                            mtlPath,
                            materialLookup);
                    }
                }
            }

            // ------------------------------------------
            // Active material
            // ------------------------------------------

            else if (command == "usemtl")
            {
                std::string name;

                std::getline(stream, name);
                name = Trim(name);

                auto found =
                    materialLookup.find(name);

                if (found != materialLookup.end())
                {
                    activeMaterial = found->second;
                }
                else
                {
                    activeMaterial = 0;

                    ViewPoint::LogMessage(
                        ("Unknown material: " +
                         name)
                            .c_str());
                }
            }

            // ------------------------------------------
            // Faces
            // ------------------------------------------

            else if (command == "f")
            {
                std::vector<ObjCorner> face;

                std::string token;

                bool faceHasUV = true;
                bool faceHasNormals = true;

                while (stream >> token)
                {
                    ObjCorner corner;

                    if (!ParseObjIndex(
                            token,
                            0,
                            model.vertices.size(),
                            corner.position))
                    {
                        ViewPoint::LogMessage(
                            "Invalid OBJ position index.");

                        face.clear();
                        break;
                    }

                    if (!ParseObjIndex(
                            token,
                            1,
                            model.texcoords.size(),
                            corner.texcoord))
                    {
                        corner.texcoord = -1;
                        faceHasUV = false;
                    }

                    if (!ParseObjIndex(
                            token,
                            2,
                            model.normals.size(),
                            corner.normal))
                    {
                        corner.normal = -1;
                        faceHasNormals = false;
                    }

                    face.push_back(corner);
                }

                if (face.size() < 3)
                    continue;

                if (!faceHasUV)
                    ++facesWithoutUV;

                if (!faceHasNormals)
                    ++facesWithoutNormals;

                // Fan triangulation.
                for (size_t i = 1;
                     i + 1 < face.size();
                     ++i)
                {
                    Triangle triangle{};

                    triangle.corners[0] = face[0];
                    triangle.corners[1] = face[i];
                    triangle.corners[2] = face[i + 1];

                    triangle.materialIndex =
                        activeMaterial;

                    model.triangles.push_back(triangle);
                }
            }
        }

        // ----------------------------------------------
        // Validation
        // ----------------------------------------------

        if (model.vertices.empty() ||
            model.triangles.empty())
        {
            ViewPoint::LogMessage(
                "OBJ contains no usable geometry.");

            return false;
        }

        // ----------------------------------------------
        // Normalize geometry
        // ----------------------------------------------

        NormalizeModel(model);

        model.loaded = true;

        // ----------------------------------------------
        // Diagnostics
        // ----------------------------------------------

        char message[512];

        snprintf(
            message,
            sizeof(message),
            "Loaded OBJ: %s",
            model.path.c_str());

        ViewPoint::LogMessage(message);

        ViewPoint::LogNumber(
            "Vertex count",
            model.vertices.size());

        ViewPoint::LogNumber(
            "UV count",
            model.texcoords.size());

        ViewPoint::LogNumber(
            "Normal count",
            model.normals.size());

        ViewPoint::LogNumber(
            "Triangle count",
            model.triangles.size());

        ViewPoint::LogNumber(
            "Material count",
            model.materials.size());

        ViewPoint::LogNumber(
            "Faces without UV coordinates",
            facesWithoutUV);

        ViewPoint::LogNumber(
            "Faces without normals",
            facesWithoutNormals);

        for (const Material &material : model.materials)
        {
            ViewPoint::LogMessage(
                ("Material loaded: " +
                 material.name)
                    .c_str());

            if (material.diffuseTexturePath.empty())
            {
                ViewPoint::LogMessage(
                    ("Material has no diffuse texture: " +
                     material.name)
                        .c_str());
            }
        }

        return true;
    }

    static Vertex3 CalculateFaceNormal(
        const Vertex3 &a,
        const Vertex3 &b,
        const Vertex3 &c);

    static Vertex3 NormalizeNormal(
        const Vertex3 &normal);

    // GPU MESH MANAGEMENT

    static void ReleaseModelGpu(Model &model)
    {
        if (wglGetCurrentContext() &&
            g_DeleteBuffers)
        {
            for (MaterialBatch &batch : model.gpuBatches)
            {
                if (batch.vertexBuffer)
                {
                    g_DeleteBuffers(
                        1,
                        &batch.vertexBuffer);
                }
            }
        }

        model.gpuBatches.clear();
        model.gpuReady = false;
        model.gpuBuildAttempted = false;
    }

    static bool BuildGpuMesh(Model &model)
    {
        if (model.gpuReady)
            return true;

        if (model.gpuBuildAttempted)
            return false;

        model.gpuBuildAttempted = true;

        if (!model.loaded || model.materials.empty())
            return false;

        std::vector<std::vector<GpuVertex>> materialVertices(
            model.materials.size());

        for (const Triangle &triangle : model.triangles)
        {
            if (triangle.materialIndex < 0 ||
                static_cast<size_t>(triangle.materialIndex) >=
                    model.materials.size())
            {
                continue;
            }

            const int materialIndex = triangle.materialIndex;

            const ObjCorner &a = triangle.corners[0];
            const ObjCorner &b = triangle.corners[1];
            const ObjCorner &c = triangle.corners[2];

            if (a.position < 0 || b.position < 0 || c.position < 0 ||
                static_cast<size_t>(a.position) >= model.vertices.size() ||
                static_cast<size_t>(b.position) >= model.vertices.size() ||
                static_cast<size_t>(c.position) >= model.vertices.size())
            {
                continue;
            }

            const Vertex3 &pa = model.vertices[a.position];
            const Vertex3 &pb = model.vertices[b.position];
            const Vertex3 &pc = model.vertices[c.position];

            const Vertex3 faceNormal =
                CalculateFaceNormal(pa, pb, pc);

            const ObjCorner *corners[3] = {
                &a, &b, &c};

            for (int i = 0; i < 3; ++i)
            {
                const ObjCorner &corner = *corners[i];

                GpuVertex vertex{};

                vertex.position =
                    model.vertices[corner.position];

                vertex.normal = faceNormal;

                if (corner.normal >= 0 &&
                    static_cast<size_t>(corner.normal) <
                        model.normals.size())
                {
                    vertex.normal = NormalizeNormal(
                        model.normals[corner.normal]);
                }

                if (corner.texcoord >= 0 &&
                    static_cast<size_t>(corner.texcoord) <
                        model.texcoords.size())
                {
                    vertex.texcoord =
                        model.texcoords[corner.texcoord];
                }

                materialVertices[materialIndex].push_back(vertex);
            }
        }

        std::vector<MaterialBatch> newBatches;

        newBatches.reserve(materialVertices.size());

        for (size_t i = 0; i < materialVertices.size(); ++i)
        {
            std::vector<GpuVertex> &vertices =
                materialVertices[i];

            if (vertices.empty())
                continue;

            if (vertices.size() >
                static_cast<size_t>(INT_MAX))
            {
                ViewPoint::LogMessage("GPU mesh contains too many vertices.");
                return false;
            }

            MaterialBatch batch;

            batch.materialIndex = static_cast<int>(i);
            batch.vertexCount =
                static_cast<GLsizei>(vertices.size());

            g_GenBuffers(
                1,
                &batch.vertexBuffer);

            if (!batch.vertexBuffer)
            {
                ViewPoint::LogMessage("Failed to create a VBO.");
                return false;
            }

            g_BindBuffer(
                GL_ARRAY_BUFFER,
                batch.vertexBuffer);

            g_BufferData(
                GL_ARRAY_BUFFER,
                static_cast<ptrdiff_t>(
                    vertices.size() * sizeof(GpuVertex)),
                vertices.data(),
                GL_STATIC_DRAW);

            const GLenum error = glGetError();

            if (error != GL_NO_ERROR)
            {
                char message[128];

                snprintf(
                    message,
                    sizeof(message),
                    "VBO upload failed: 0x%X",
                    error);

                ViewPoint::LogMessage(message);

                g_DeleteBuffers(
                    1,
                    &batch.vertexBuffer);

                return false;
            }

            newBatches.push_back(batch);
        }

        g_BindBuffer(GL_ARRAY_BUFFER, 0);

        if (newBatches.empty())
        {
            ViewPoint::LogMessage("GPU mesh contains no drawable batches.");
            return false;
        }

        model.gpuBatches = std::move(newBatches);
        model.gpuReady = true;

        ViewPoint::LogMessage(
            ("GPU mesh created: " + model.path).c_str());

        ViewPoint::LogNumber(
            "GPU material batches",
            model.gpuBatches.size());

        return true;
    }

    // SCENE LOADING

    static bool LoadScene(
        const std::vector<ObjectConfig> &configs,
        std::vector<Model> &output)
    {
        output.clear();

        if (configs.empty())
        {
            ViewPoint::LogMessage("Scene contains no objects.");
            return false;
        }

        std::vector<Model> newModels;

        newModels.reserve(configs.size());

        for (size_t i = 0; i < configs.size(); ++i)
        {
            const ObjectConfig &config = configs[i];

            Model model;

            model.path = config.path;
            model.position = config.position;
            model.rotation = config.rotation;
            model.scale = config.scale;

            ViewPoint::LogMessage(
                ("Loading scene object " +
                 std::to_string(i) + ": " +
                 model.path)
                    .c_str());

            if (!LoadOBJ(model))
            {
                ViewPoint::LogMessage(
                    ("Scene loading failed at object " +
                     std::to_string(i) + ": " +
                     model.path)
                        .c_str());

                return false;
            }

            newModels.push_back(std::move(model));
        }

        output = std::move(newModels);

        ViewPoint::LogNumber(
            "Successfully loaded scene objects",
            output.size());

        return true;
    }

    static bool LoadConfiguredScene()
    {
        std::vector<Model> newModels;

        if (!LoadScene(g_ObjectConfigs, newModels))
            return false;

        // Only replace the active scene after every object
        // has loaded successfully.
        for (Model &model : g_Models)
        {
            ReleaseModelTextures(model);
            ReleaseModelGpu(model);
        }

        g_Models = std::move(newModels);

        return true;
    }
    // LIVE CONFIGURATION RELOADING

    static void CheckConfigurationReload()
    {
        ++g_ConfigCheckCounter;

        if (g_ConfigCheckCounter < CONFIG_CHECK_INTERVAL)
            return;

        g_ConfigCheckCounter = 0;

        std::error_code error;

        const fs::file_time_type currentTimestamp =
            fs::last_write_time(
                GetConfigurationPath(),
                error);

        if (error)
            return;

        if (g_ConfigTimestampValid &&
            currentTimestamp == g_ConfigLastWriteTime)
        {
            return;
        }

        g_ConfigLastWriteTime = currentTimestamp;
        g_ConfigTimestampValid = true;

        std::vector<ObjectConfig> newConfigs;

        if (!ReadConfiguration(newConfigs))
        {
            ViewPoint::LogMessage(
                "Configuration reload failed; keeping previous scene.");

            return;
        }

        // Load the complete new scene before touching the old one.
        std::vector<Model> newModels;

        if (!LoadScene(newConfigs, newModels))
        {
            ViewPoint::LogMessage(
                "Scene reload failed; keeping previous scene.");

            // Remember this timestamp so a failed configuration
            // is not repeatedly loaded every 60 frames.
            g_ConfigLastWriteTime = currentTimestamp;

            return;
        }

        // Release old GPU textures while the OpenGL context is current.
        for (Model &model : g_Models)
        {
            ReleaseModelTextures(model);
            ReleaseModelGpu(model);
        }

        g_Models = std::move(newModels);
        g_ObjectConfigs = std::move(newConfigs);

        g_ConfigLastWriteTime = currentTimestamp;

        ViewPoint::LogMessage(
            "Scene successfully reloaded.");

        ViewPoint::LogNumber(
            "Active scene objects",
            g_Models.size());
    }

    // NORMAL CALCULATIONS

    static Vertex3 CalculateFaceNormal(
        const Vertex3 &a,
        const Vertex3 &b,
        const Vertex3 &c)
    {
        const float ux = b.x - a.x;
        const float uy = b.y - a.y;
        const float uz = b.z - a.z;

        const float vx = c.x - a.x;
        const float vy = c.y - a.y;
        const float vz = c.z - a.z;

        Vertex3 normal;

        normal.x = uy * vz - uz * vy;
        normal.y = uz * vx - ux * vz;
        normal.z = ux * vy - uy * vx;

        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z);

        if (length < 1e-8f)
            return {0.0f, 0.0f, 1.0f};

        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        return normal;
    }

    static Vertex3 NormalizeNormal(
        const Vertex3 &normal)
    {
        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z);

        if (length < 1e-8f)
            return {0.0f, 0.0f, 1.0f};

        return {
            normal.x / length,
            normal.y / length,
            normal.z / length};
    }

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
    // FIRST-PERSON CAMERA

    static void ReleaseCameraCursor()
    {
        ClipCursor(nullptr);
        g_CursorCaptured = false;
    }

    static void UpdateCamera(HWND window)
    {
        const ULONGLONG currentTime = GetTickCount64();

        float deltaTime = 0.0f;

        if (g_Camera.lastUpdateTime != 0)
        {
            deltaTime = static_cast<float>(
                            currentTime - g_Camera.lastUpdateTime) /
                        1000.0f;
        }

        g_Camera.lastUpdateTime = currentTime;

        // Prevent large movement after pauses or window stalls.
        deltaTime = (std::min)(deltaTime, 0.05f);

        // ----------------------------------------------
        // F1 camera toggle
        // ----------------------------------------------

        const bool f1Down =
            (GetAsyncKeyState(VK_F1) & 0x8000) != 0;

        if (f1Down && !g_Camera.previousF1State)
        {
            g_Camera.enabled = !g_Camera.enabled;

            if (!g_Camera.enabled)
            {
                ReleaseCameraCursor();
                ViewPoint::LogMessage("First-person camera disabled.");
            }
            else
            {
                g_CursorCaptured = false;
                ViewPoint::LogMessage("First-person camera enabled.");
            }
        }

        g_Camera.previousF1State = f1Down;

        if (!g_Camera.enabled || !window)
        {
            if (g_CursorCaptured)
                ReleaseCameraCursor();

            return;
        }

        // ----------------------------------------------
        // Window and cursor coordinates
        // ----------------------------------------------

        RECT clientRect{};

        if (!GetClientRect(window, &clientRect))
            return;

        const int clientWidth =
            clientRect.right - clientRect.left;

        const int clientHeight =
            clientRect.bottom - clientRect.top;

        if (clientWidth <= 0 || clientHeight <= 0)
            return;

        POINT topLeft = {
            clientRect.left,
            clientRect.top};

        POINT bottomRight = {
            clientRect.right,
            clientRect.bottom};

        if (!ClientToScreen(window, &topLeft) ||
            !ClientToScreen(window, &bottomRight))
        {
            return;
        }

        RECT screenRect = {
            topLeft.x,
            topLeft.y,
            bottomRight.x,
            bottomRight.y};

        const int centerX =
            (topLeft.x + bottomRight.x) / 2;

        const int centerY =
            (topLeft.y + bottomRight.y) / 2;

        // ----------------------------------------------
        // Mouse capture
        // ----------------------------------------------

        if (!g_CursorCaptured)
        {
            ClipCursor(&screenRect);
            SetCursorPos(centerX, centerY);

            g_CursorCaptured = true;
        }

        POINT mousePosition{};

        if (GetCursorPos(&mousePosition))
        {
            const int mouseDeltaX =
                mousePosition.x - centerX;

            const int mouseDeltaY =
                mousePosition.y - centerY;

            g_Camera.yaw -=
                static_cast<float>(mouseDeltaX) *
                g_Camera.mouseSensitivity;

            g_Camera.pitch -=
                static_cast<float>(mouseDeltaY) *
                g_Camera.mouseSensitivity;

            // Prevent the camera from flipping upside down.
            g_Camera.pitch = (std::max)(-89.0f,
                                        (std::min)(89.0f, g_Camera.pitch));
        }

        SetCursorPos(centerX, centerY);

        // ----------------------------------------------
        // Movement input
        // ----------------------------------------------

        const auto KeyDown = [](int key) -> bool
        {
            return (GetAsyncKeyState(key) & 0x8000) != 0;
        };

        float forwardInput = 0.0f;
        float rightInput = 0.0f;
        float verticalInput = 0.0f;

        if (KeyDown('W'))
            forwardInput += 1.0f;

        if (KeyDown('S'))
            forwardInput -= 1.0f;

        if (KeyDown('D'))
            rightInput += 1.0f;

        if (KeyDown('A'))
            rightInput -= 1.0f;

        if (KeyDown(VK_SPACE))
            verticalInput += 1.0f;

        if (KeyDown(VK_CONTROL))
            verticalInput -= 1.0f;

        // Normalize horizontal movement so diagonal movement
        // is not faster than straight movement.
        const float movementLength = std::sqrt(
            forwardInput * forwardInput +
            rightInput * rightInput);

        if (movementLength > 1.0f)
        {
            forwardInput /= movementLength;
            rightInput /= movementLength;
        }

        // ----------------------------------------------
        // Calculate camera direction
        // ----------------------------------------------

        const float yawRadians =
            g_Camera.yaw *
            3.14159265358979323846f / 180.0f;

        const float forwardX = -std::sin(yawRadians);
        const float forwardZ = -std::cos(yawRadians);

        const float rightX = std::cos(yawRadians);
        const float rightZ = -std::sin(yawRadians);

        // ----------------------------------------------
        // Movement speed
        // ----------------------------------------------

        float speed = g_Camera.movementSpeed;

        if (KeyDown(VK_SHIFT))
        {
            speed *= g_Camera.sprintMultiplier;
        }

        const float movement =
            speed * deltaTime;

        g_Camera.position.x +=
            (forwardX * forwardInput +
             rightX * rightInput) *
            movement;

        g_Camera.position.z +=
            (forwardZ * forwardInput +
             rightZ * rightInput) *
            movement;

        g_Camera.position.y +=
            verticalInput * movement;
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

    // RESOURCE DIAGNOSTICS

    static BOOL CALLBACK EnumerateResourceNames(
        HMODULE module,
        LPCSTR type,
        LPSTR name,
        LONG_PTR)
    {
        char message[512];

        if (IS_INTRESOURCE(name))
        {
            snprintf(
                message,
                sizeof(message),
                "Embedded numeric resource ID: %u",
                static_cast<unsigned>(
                    reinterpret_cast<ULONG_PTR>(name)));

            ViewPoint::LogMessage(message);
            return TRUE;
        }

        snprintf(
            message,
            sizeof(message),
            "Enumerated resource: %s",
            name);

        ViewPoint::LogMessage(message);

        SetLastError(ERROR_SUCCESS);

        HRSRC resource = FindResourceA(
            module,
            name,
            type);

        if (resource)
        {
            ViewPoint::LogMessage(
                "Lookup using enumerated name: SUCCESS");
        }
        else
        {
            snprintf(
                message,
                sizeof(message),
                "Resource lookup failed: %lu",
                static_cast<unsigned long>(
                    GetLastError()));

            ViewPoint::LogMessage(message);
        }

        return TRUE;
    }

    static void DiagnoseEmbeddedResources()
    {
        char message[256];

        snprintf(
            message,
            sizeof(message),
            "Resource enumeration module: %p",
            static_cast<void *>(g_Module));

        ViewPoint::LogMessage(message);

        EnumResourceNamesA(
            g_Module,
            RT_RCDATA,
            EnumerateResourceNames,
            0);
    }
}
// REPENTOGON HOO

HOOK_GLOBAL(
    OpenGL::wglSwapBuffers,
    (HDC hdc)->bool,
    __stdcall)
{
    if (wglGetCurrentContext())
    {
        HWND window = WindowFromDC(hdc);

        RenderTriangleMesh(window);
    }

    return super(hdc);
}
// DLL ENTRY POIN

BOOL WINAPI DllMain(
    HINSTANCE instance,
    DWORD reason,
    LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        g_Module = instance;

        DisableThreadLibraryCalls(instance);
    }

    return TRUE;
}
// MOD INITIALIZATIO

extern "C" __declspec(dllexport) int ModInit()
{
    // Reset the log before writing initialization data.
    ViewPoint::ResetLogFile();

    ViewPoint::LogMessage(
        "Isaac: ViewPoint initialized.");

    LoadConfiguration();

    ViewPoint::LogMessage(
        ("Default model: " +
         std::string(DEFAULT_OBJECT))
            .c_str());

    ViewPoint::LogNumber(
        "Configured scene objects",
        g_ObjectConfigs.size());

    DiagnoseEmbeddedResources();

    return 0;
}
