#define NOMINMAX

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

using PFNGLUSEPROGRAMPROC = void(APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void(APIENTRY *)(GLenum);

namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}

namespace
{
    namespace fs = std::filesystem;

    // ==================================================
    // CONFIGURATION
    // ==================================================

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

    // ==================================================
    // STRUCTURES
    // ==================================================

    struct Vertex3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct Vertex2
    {
        float u = 0.0f;
        float v = 0.0f;
    };

    struct ObjCorner
    {
        int32_t position = -1;
        int32_t texcoord = -1;
        int32_t normal = -1;
    };

    struct Triangle
    {
        ObjCorner corners[3];
        int materialIndex = 0;
    };

    struct Material
    {
        std::string name;

        float ambient[3] = {
            0.2f, 0.2f, 0.2f
        };

        float diffuse[3] = {
            1.0f, 1.0f, 1.0f
        };

        float specular[3] = {
            0.0f, 0.0f, 0.0f
        };

        float shininess = 32.0f;

        std::string diffuseTexturePath;

        std::vector<unsigned char> pixels;

        int width = 0;
        int height = 0;

        GLuint textureId = 0;

        bool textureAttempted = false;
    };

    // Every model owns its own geometry and materials.
    struct Model
    {
        std::string path;

        std::vector<Vertex3> vertices;
        std::vector<Vertex2> texcoords;
        std::vector<Vertex3> normals;

        std::vector<Triangle> triangles;
        std::vector<Material> materials;

        bool attempted = false;
        bool loaded = false;
    };

    // ==================================================
    // GLOBAL STATE
    // ==================================================

    static HMODULE g_Module = nullptr;

    static HGLRC g_ResourceContext = nullptr;

    static PFNGLUSEPROGRAMPROC g_UseProgram = nullptr;
    static PFNGLACTIVETEXTUREPROC g_ActiveTexture = nullptr;

    static Model g_Model;
    
    static std::string g_ModelPath = DEFAULT_OBJECT;
    
    // Configuration hot-reload state.
    static fs::file_time_type g_ConfigLastWriteTime{};
    static bool g_ConfigTimestampValid = false;
    
    static unsigned int g_ConfigCheckCounter = 0;
    
    constexpr unsigned int CONFIG_CHECK_INTERVAL = 60;

    // ==================================================
    // LOGGING
    // ==================================================

    static bool ResetLogFile()
    {
        FILE* file = fopen(LOG_FILE, "w");

        if (!file)
        {
            OutputDebugStringA(
                "Isaac ViewPoint: Cannot reset log file.\n"
            );

            return false;
        }

        fprintf(file, "Isaac ViewPoint: Log started\n");
        fclose(file);

        return true;
    }

    static void LogMessage(const char* message)
    {
        FILE* file = fopen(LOG_FILE, "a");

        if (!file)
        {
            OutputDebugStringA(
                "Isaac ViewPoint: Cannot write log.\n"
            );

            return;
        }

        fprintf(
            file,
            "Isaac ViewPoint: %s\n",
            message
        );

        fclose(file);
    }

    static void LogNumber(
        const char* label,
        size_t value)
    {
        char message[256];

        snprintf(
            message,
            sizeof(message),
            "%s: %zu",
            label,
            value
        );

        LogMessage(message);
    }

    // ==================================================
    // STRING HELPERS
    // ==================================================

    static std::string Trim(const std::string& text)
    {
        const size_t first =
            text.find_first_not_of(" \t\r\n");

        if (first == std::string::npos)
            return {};

        const size_t last =
            text.find_last_not_of(" \t\r\n");

        return text.substr(
            first,
            last - first + 1
        );
    }

    static std::string NormalizeAssetPath(
        std::string path)
    {
        std::replace(
            path.begin(),
            path.end(),
            '\\',
            '/'
        );

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

        for (const std::string& p : parts)
        {
            if (!result.empty())
                result += '/';

            result += p;
        }

        return result;
    }

    static std::string ResolveRelativeAsset(
        const std::string& parent,
        const std::string& child)
    {
        std::string normalizedChild = child;

        std::replace(
            normalizedChild.begin(),
            normalizedChild.end(),
            '\\',
            '/'
        );

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
            directory + normalizedChild
        );
    }

    static std::string ToUpperResourceName(
        const std::string& name)
    {
        std::string result = name;

        for (char& c : result)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = static_cast<char>(
                    c - 'a' + 'A'
                );
            }
        }

        return result;
    }

    // ==================================================
    // DLL DIRECTORY
    // ==================================================

    static fs::path GetDllDirectory()
    {
        char modulePath[MAX_PATH] = {};

        DWORD length = GetModuleFileNameA(
            g_Module,
            modulePath,
            MAX_PATH
        );

        if (!length || length >= MAX_PATH)
            return fs::current_path();

        return fs::path(
            std::string(modulePath, length)
        ).parent_path();
    }
    // ==================================================
    // CONFIGURATION FILE
    // ==================================================
    
    static fs::path GetConfigurationPath()
    {
        return GetDllDirectory() / CONFIG_FILE;
    }
    
    static bool ReadConfiguration(std::string& output)
    {
        const fs::path configPath = GetConfigurationPath();
    
        std::ifstream file(configPath);
    
        if (!file)
            return false;
    
        // Default value if the file exists but Model is absent.
        output = DEFAULT_OBJECT;
    
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
    
            std::string value =
                Trim(line.substr(equals + 1));
    
            if (key == "Model")
            {
                // Allow quoted paths.
                if (value.size() >= 2 &&
                    value.front() == '"' &&
                    value.back() == '"')
                {
                    value = value.substr(
                        1,
                        value.size() - 2
                    );
                }
    
                const std::string normalized =
                    NormalizeAssetPath(value);
    
                if (normalized.empty())
                {
                    LogMessage(
                        "Invalid model path in configuration."
                    );
    
                    return false;
                }
    
                output = normalized;
            }
        }
    
        return true;
    }
    
    static void UpdateConfigurationTimestamp()
    {
        std::error_code error;
    
        const fs::file_time_type timestamp =
            fs::last_write_time(
                GetConfigurationPath(),
                error
            );
    
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
        std::string configuredModel;
    
        if (!ReadConfiguration(configuredModel))
        {
            LogMessage(
                "Configuration file not found or unreadable; using default model."
            );
    
            g_ModelPath = DEFAULT_OBJECT;
        }
        else
        {
            g_ModelPath = configuredModel;
        }
    
        LogMessage(
            ("Configured model: " + g_ModelPath).c_str()
        );
    
        UpdateConfigurationTimestamp();
    }

    // ==================================================
    // EMBEDDED RESOURCE LOOKUP
    // ==================================================

    static HRSRC FindEmbeddedResource(
        HMODULE module,
        const std::string& assetPath)
    {
        const std::string resourceName =
            ToUpperResourceName(assetPath);

        HRSRC resource = FindResourceA(
            module,
            resourceName.c_str(),
            RT_RCDATA
        );

        if (resource)
            return resource;

        // The current generated resources use literal
        // quotation marks in their resource names.
        const std::string quotedName =
            "\"" + resourceName + "\"";

        resource = FindResourceA(
            module,
            quotedName.c_str(),
            RT_RCDATA
        );

        if (resource)
        {
            LogMessage(
                ("Found quoted resource name: " +
                 quotedName).c_str()
            );

            return resource;
        }

        char message[512];

        snprintf(
            message,
            sizeof(message),
            "Resource not found: %s",
            assetPath.c_str()
        );

        LogMessage(message);

        return nullptr;
    }

    // ==================================================
    // ASSET LOADING
    // ==================================================

    static bool ReadAsset(
        const std::string& requestedPath,
        std::vector<unsigned char>& output)
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
                    std::ios::binary
                );

                if (file)
                {
                    file.seekg(0, std::ios::end);

                    const std::streamoff size =
                        file.tellg();

                    if (size <= 0)
                        return false;

                    file.seekg(0, std::ios::beg);

                    output.resize(
                        static_cast<size_t>(size)
                    );

                    file.read(
                        reinterpret_cast<char*>(
                            output.data()
                        ),
                        size
                    );

                    if (file)
                    {
                        LogMessage(
                            ("Loaded external asset: " +
                             assetPath).c_str()
                        );

                        return true;
                    }

                    output.clear();
                }
            }
        }
        catch (...)
        {
            LogMessage(
                "External asset access failed."
            );
        }

        // ----------------------------------------------
        // Embedded Windows resource.
        // ----------------------------------------------

        HRSRC resource = FindEmbeddedResource(
            g_Module,
            assetPath
        );

        if (!resource)
        {
            LogMessage(
                ("Asset not found: " +
                 assetPath).c_str()
            );

            return false;
        }

        HGLOBAL loaded = LoadResource(
            g_Module,
            resource
        );

        if (!loaded)
            return false;

        const DWORD size = SizeofResource(
            g_Module,
            resource
        );

        const void* data = LockResource(loaded);

        if (!data || size == 0)
            return false;

        const unsigned char* bytes =
            static_cast<const unsigned char*>(data);

        output.assign(
            bytes,
            bytes + size
        );

        return true;
    }

    // ==================================================
    // OBJ INDEX PARSING
    // ==================================================

    static bool ParseObjIndex(
        const std::string& token,
        int component,
        size_t count,
        int32_t& output)
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

        char* parseEnd = nullptr;

        const long value = strtol(
            number.c_str(),
            &parseEnd,
            10
        );

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

    // ==================================================
    // MATERIAL MANAGEMENT
    // ==================================================

    static int FindOrCreateMaterial(
        const std::string& name,
        std::map<std::string, int>& lookup,
        Model& model)
    {
        auto found = lookup.find(name);

        if (found != lookup.end())
            return found->second;

        Material material;
        material.name = name;

        const int index =
            static_cast<int>(model.materials.size());

        model.materials.push_back(
            std::move(material)
        );

        lookup[name] = index;

        return index;
    }

    // ==================================================
    // MTL TEXTURE PATH PARSING
    // ==================================================

    static std::string GetMapFilename(
        std::istringstream& stream)
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
            const std::string& option = tokens[i];

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

    // ==================================================
    // MTL LOADING
    // ==================================================

    static void LoadMTL(
        Model& model,
        const std::string& mtlPath,
        std::map<std::string, int>& lookup)
    {
        std::vector<unsigned char> bytes;

        if (!ReadAsset(mtlPath, bytes))
        {
            LogMessage(
                ("Cannot load MTL: " +
                 mtlPath).c_str()
            );

            return;
        }

        const std::string source(
            reinterpret_cast<const char*>(bytes.data()),
            bytes.size()
        );

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
                            model
                        );
                }

                continue;
            }

            if (currentMaterial < 0)
                continue;

            Material& material =
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
                            texture
                        );

                    LogMessage(
                        ("Material texture: " +
                         material.name + " -> " +
                         material.diffuseTexturePath).c_str()
                    );
                }
            }
        }

        LogMessage(
            ("Loaded MTL: " + mtlPath).c_str()
        );
    }

    // ==================================================
    // TEXTURE LOADING
    // ==================================================

    static void LoadMaterialTexture(
        Material& material)
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
            LogMessage(
                ("Cannot load texture: " +
                 material.diffuseTexturePath).c_str()
            );

            return;
        }

        if (bytes.size() >
            static_cast<size_t>(INT_MAX))
        {
            LogMessage("Texture file is too large.");
            return;
        }

        int channels = 0;

        stbi_set_flip_vertically_on_load(1);

        unsigned char* decoded = stbi_load_from_memory(
            bytes.data(),
            static_cast<int>(bytes.size()),
            &material.width,
            &material.height,
            &channels,
            4
        );

        if (!decoded)
        {
            LogMessage(
                ("PNG decoding failed: " +
                 material.diffuseTexturePath).c_str()
            );

            return;
        }

        const size_t pixelSize =
            static_cast<size_t>(material.width) *
            static_cast<size_t>(material.height) * 4;

        material.pixels.assign(
            decoded,
            decoded + pixelSize
        );

        stbi_image_free(decoded);

        char message[256];

        snprintf(
            message,
            sizeof(message),
            "Decoded texture: %s (%dx%d, source channels=%d)",
            material.diffuseTexturePath.c_str(),
            material.width,
            material.height,
            channels
        );

        LogMessage(message);
    }

    // ==================================================
    // TEXTURE UPLOAD
    // ==================================================

    static bool UploadMaterialTexture(
        Material& material)
    {
        LoadMaterialTexture(material);

        if (material.pixels.empty())
            return false;

        if (material.textureId != 0)
            return true;

        glGenTextures(
            1,
            &material.textureId
        );

        if (!material.textureId)
            return false;

        glBindTexture(
            GL_TEXTURE_2D,
            material.textureId
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
            material.width,
            material.height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            material.pixels.data()
        );

        const GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            char message[128];

            snprintf(
                message,
                sizeof(message),
                "Texture upload failed: 0x%X",
                error
            );

            LogMessage(message);

            glDeleteTextures(
                1,
                &material.textureId
            );

            material.textureId = 0;

            return false;
        }

        return true;
    }

    // ==================================================
    // MODEL TEXTURE CLEANUP
    // ==================================================
    
    static void ReleaseModelTextures(Model& model)
    {
        // OpenGL resources can only be deleted when their
        // owning context is current.
        if (!wglGetCurrentContext())
            return;
    
        for (Material& material : model.materials)
        {
            if (material.textureId != 0)
            {
                glDeleteTextures(
                    1,
                    &material.textureId
                );
    
                material.textureId = 0;
            }
        }
    }
    // ==================================================
    // MODEL BOUNDING BOX / NORMALIZATION
    // ==================================================

    static void NormalizeModel(Model& model)
    {
        if (model.vertices.empty())
            return;

        Vertex3 lo = model.vertices.front();
        Vertex3 hi = model.vertices.front();

        for (const Vertex3& v : model.vertices)
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

        const float extent = (std::max)(
            (std::max)(hi.x - lo.x, hi.y - lo.y),
            (std::max)(hi.z - lo.z, 0.0001f)
        );

        const float scale = 2.0f / extent;

        for (Vertex3& v : model.vertices)
        {
            v.x = (v.x - cx) * scale;
            v.y = (v.y - cy) * scale;
            v.z = (v.z - cz) * scale;
        }
    }

    // ==================================================
    // OBJ LOADING
    // ==================================================

    static bool LoadOBJ(Model& model)
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
            LogMessage(
                ("Cannot load OBJ: " +
                 model.path).c_str()
            );

            return false;
        }

        const std::string source(
            reinterpret_cast<const char*>(bytes.data()),
            bytes.size()
        );

        std::istringstream input(source);

        std::string line;

        std::map<std::string, int> materialLookup;

        Material defaultMaterial;
        defaultMaterial.name = "__default";

        model.materials.push_back(
            std::move(defaultMaterial)
        );

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
                            filename
                        );

                    if (!mtlPath.empty())
                    {
                        LoadMTL(
                            model,
                            mtlPath,
                            materialLookup
                        );
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

                    LogMessage(
                        ("Unknown material: " +
                         name).c_str()
                    );
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
                        LogMessage(
                            "Invalid OBJ position index."
                        );

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
            LogMessage(
                "OBJ contains no usable geometry."
            );

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
            model.path.c_str()
        );

        LogMessage(message);

        LogNumber(
            "Vertex count",
            model.vertices.size()
        );

        LogNumber(
            "UV count",
            model.texcoords.size()
        );

        LogNumber(
            "Normal count",
            model.normals.size()
        );

        LogNumber(
            "Triangle count",
            model.triangles.size()
        );

        LogNumber(
            "Material count",
            model.materials.size()
        );

        LogNumber(
            "Faces without UV coordinates",
            facesWithoutUV
        );

        LogNumber(
            "Faces without normals",
            facesWithoutNormals
        );

        for (const Material& material : model.materials)
        {
            LogMessage(
                ("Material loaded: " +
                 material.name).c_str()
            );

            if (material.diffuseTexturePath.empty())
            {
                LogMessage(
                    ("Material has no diffuse texture: " +
                     material.name).c_str()
                );
            }
        }

        return true;
    }

    // ==================================================
    // LIVE CONFIGURATION RELOADING
    // ==================================================
    
    static void CheckConfigurationReload()
    {
        ++g_ConfigCheckCounter;
    
        if (g_ConfigCheckCounter < CONFIG_CHECK_INTERVAL)
            return;
    
        g_ConfigCheckCounter = 0;
    
        const fs::path configPath = GetConfigurationPath();
    
        std::error_code error;
    
        const fs::file_time_type currentTimestamp =
            fs::last_write_time(
                configPath,
                error
            );
    
        // The file may temporarily disappear while being saved.
        // Keep the current model and try again later.
        if (error)
            return;
    
        // First timestamp observation.
        if (!g_ConfigTimestampValid)
        {
            g_ConfigLastWriteTime = currentTimestamp;
            g_ConfigTimestampValid = true;
            return;
        }
    
        // Nothing changed.
        if (currentTimestamp == g_ConfigLastWriteTime)
            return;
    
        std::string newModelPath;
    
        if (!ReadConfiguration(newModelPath))
        {
            LogMessage(
                "Configuration reload failed; keeping current model."
            );
    
            return;
        }
    
        // Remember the new timestamp after successfully reading
        // the configuration.
        g_ConfigLastWriteTime = currentTimestamp;
    
        // No model change is necessary.
        if (newModelPath == g_ModelPath)
            return;
    
        LogMessage(
            ("Configuration changed. Requested model: " +
             newModelPath).c_str()
        );
    
        // Load into a temporary object. The active model remains
        // untouched if the new model cannot be loaded.
        Model newModel;
    
        newModel.path = newModelPath;
    
        if (!LoadOBJ(newModel))
        {
            LogMessage(
                ("Model reload failed: " +
                 newModelPath).c_str()
            );
    
            LogMessage(
                "Previous model will remain active."
            );
    
            return;
        }
    
        // The old model can now be safely replaced.
        ReleaseModelTextures(g_Model);
    
        g_Model = std::move(newModel);
    
        g_ModelPath = newModelPath;
    
        LogMessage(
            ("Successfully switched model to: " +
             g_ModelPath).c_str()
        );
    }
    // ==================================================
    // NORMAL CALCULATIONS
    // ==================================================

    static Vertex3 CalculateFaceNormal(
        const Vertex3& a,
        const Vertex3& b,
        const Vertex3& c)
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
            normal.z * normal.z
        );

        if (length < 1e-8f)
            return {0.0f, 0.0f, 1.0f};

        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        return normal;
    }

    static Vertex3 NormalizeNormal(
        const Vertex3& normal)
    {
        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z
        );

        if (length < 1e-8f)
            return {0.0f, 0.0f, 1.0f};

        return {
            normal.x / length,
            normal.y / length,
            normal.z / length
        };
    }

    // ==================================================
    // LIGHTING
    // ==================================================

    static float CalculateBrightness(
        const Vertex3& normal)
    {
        const float lightLength = std::sqrt(
            LIGHT_X * LIGHT_X +
            LIGHT_Y * LIGHT_Y +
            LIGHT_Z * LIGHT_Z
        );

        const float diffuse = (std::max)(
            0.0f,
            (
                normal.x * LIGHT_X +
                normal.y * LIGHT_Y +
                normal.z * LIGHT_Z
            ) / lightLength
        );

        return (std::min)(
            1.0f,
            AMBIENT_LIGHT + DIFFUSE_LIGHT * diffuse
        );
    }

    // ==================================================
    // OPENGL FUNCTION LOADING
    // ==================================================

    static PROC GetGLProc(const char* name)
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

            for (Material& material : g_Model.materials)
                material.textureId = 0;

            LogMessage("OpenGL context changed.");
        }

        if (!g_UseProgram)
        {
            g_UseProgram =
                reinterpret_cast<PFNGLUSEPROGRAMPROC>(
                    GetGLProc("glUseProgram")
                );
        }

        if (!g_ActiveTexture)
        {
            g_ActiveTexture =
                reinterpret_cast<PFNGLACTIVETEXTUREPROC>(
                    GetGLProc("glActiveTexture")
                );
        }

        if (!g_UseProgram)
        {
            LogMessage("glUseProgram unavailable.");
            return false;
        }

        return true;
    }

    // ==================================================
    // TRIANGLE RENDERING
    // ==================================================

    static void RenderTriangle(
        const Model& model,
        const Triangle& triangle)
    {
        const ObjCorner* corners[3] = {
            &triangle.corners[0],
            &triangle.corners[1],
            &triangle.corners[2]
        };

        const Vertex3* positions[3] = {
            &model.vertices[corners[0]->position],
            &model.vertices[corners[1]->position],
            &model.vertices[corners[2]->position]
        };

        const Vertex3 faceNormal =
            CalculateFaceNormal(
                *positions[0],
                *positions[1],
                *positions[2]
            );

        const int materialIndex =
            triangle.materialIndex >= 0 &&
            static_cast<size_t>(
                triangle.materialIndex
            ) < model.materials.size()
                ? triangle.materialIndex
                : 0;

        const Material& material =
            model.materials[materialIndex];

        for (int i = 0; i < 3; ++i)
        {
            const ObjCorner& corner =
                *corners[i];

            Vertex3 normal = faceNormal;

            if (corner.normal >= 0 &&
                static_cast<size_t>(corner.normal) <
                    model.normals.size())
            {
                normal = NormalizeNormal(
                    model.normals[corner.normal]
                );
            }

            const float brightness =
                CalculateBrightness(normal);

            glColor4f(
                material.diffuse[0] * brightness,
                material.diffuse[1] * brightness,
                material.diffuse[2] * brightness,
                1.0f
            );

            glNormal3f(
                normal.x,
                normal.y,
                normal.z
            );

            if (corner.texcoord >= 0 &&
                static_cast<size_t>(corner.texcoord) <
                    model.texcoords.size())
            {
                const Vertex2& uv =
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
                positions[i]->z
            );
        }
    }

    // ==================================================
    // MODEL RENDERING
    // ==================================================

    static void RenderModel(Model& model)
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
            viewport
        );

        if (viewport[2] <= 0 ||
            viewport[3] <= 0)
        {
            return;
        }

        glGetIntegerv(
            GL_CURRENT_PROGRAM,
            &oldProgram
        );

        glGetIntegerv(
            GL_MATRIX_MODE,
            &oldMatrixMode
        );

        glGetIntegerv(
            GL_DEPTH_BITS,
            &depthBits
        );

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

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);

        glEnable(GL_BLEND);

        glBlendFunc(
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA
        );

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.01f);

        glClearDepth(1.0);
        glClear(GL_DEPTH_BUFFER_BIT);

        // ----------------------------------------------
        // Projection
        // ----------------------------------------------

        const double aspect =
            static_cast<double>(viewport[2]) /
            static_cast<double>(viewport[3]);

        const double nearPlane = 0.1;
        const double farPlane = 100.0;

        const double halfFov =
            OBJECT_FOV *
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
            farPlane
        );

        // ----------------------------------------------
        // Model transformation
        // ----------------------------------------------

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

        // ----------------------------------------------
        // Render materials
        // ----------------------------------------------

        for (size_t materialIndex = 0;
             materialIndex < model.materials.size();
             ++materialIndex)
        {
            Material& material =
                model.materials[materialIndex];

            const bool textured =
                UploadMaterialTexture(material);

            if (textured)
            {
                glEnable(GL_TEXTURE_2D);

                glBindTexture(
                    GL_TEXTURE_2D,
                    material.textureId
                );

                glTexEnvi(
                    GL_TEXTURE_ENV,
                    GL_TEXTURE_ENV_MODE,
                    GL_MODULATE
                );
            }
            else
            {
                glDisable(GL_TEXTURE_2D);
            }

            glBegin(GL_TRIANGLES);

            for (const Triangle& triangle :
                 model.triangles)
            {
                if (triangle.materialIndex !=
                    static_cast<int>(materialIndex))
                {
                    continue;
                }

                bool valid = true;

                for (const ObjCorner& corner :
                     triangle.corners)
                {
                    if (corner.position < 0 ||
                        static_cast<size_t>(
                            corner.position
                        ) >= model.vertices.size())
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    RenderTriangle(
                        model,
                        triangle
                    );
                }
            }

            glEnd();
        }

        // ----------------------------------------------
        // Restore state
        // ----------------------------------------------

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

    // ==================================================
    // MAIN RENDERER
    // ==================================================
    
    static void RenderTriangleMesh()
    {
        if (!EnsureContext())
            return;
    
        // Check for configuration changes.
        CheckConfigurationReload();
    
        // Initial model loading.
        if (!g_Model.attempted)
        {
            g_Model.path = g_ModelPath;
    
            LoadOBJ(g_Model);
        }
    
        if (!g_Model.loaded)
            return;
    
        RenderModel(g_Model);
    }

    // ==================================================
    // RESOURCE DIAGNOSTICS
    // ==================================================

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
                    reinterpret_cast<ULONG_PTR>(name)
                )
            );

            LogMessage(message);
            return TRUE;
        }

        snprintf(
            message,
            sizeof(message),
            "Enumerated resource: %s",
            name
        );

        LogMessage(message);

        SetLastError(ERROR_SUCCESS);

        HRSRC resource = FindResourceA(
            module,
            name,
            type
        );

        if (resource)
        {
            LogMessage(
                "Lookup using enumerated name: SUCCESS"
            );
        }
        else
        {
            snprintf(
                message,
                sizeof(message),
                "Resource lookup failed: %lu",
                static_cast<unsigned long>(
                    GetLastError()
                )
            );

            LogMessage(message);
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
            static_cast<void*>(g_Module)
        );

        LogMessage(message);

        EnumResourceNamesA(
            g_Module,
            RT_RCDATA,
            EnumerateResourceNames,
            0
        );
    }
}

// ==================================================
// REPENTOGON HOOK
// ==================================================

HOOK_GLOBAL(
    OpenGL::wglSwapBuffers,
    (HDC hdc)->bool,
    __stdcall
)
{
    if (wglGetCurrentContext())
        RenderTriangleMesh();

    return super(hdc);
}

// ==================================================
// DLL ENTRY POINT
// ==================================================

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

// ==================================================
// MOD INITIALIZATION
// ==================================================

extern "C" __declspec(dllexport)
int ModInit()
{
    // Reset the log before writing initialization data.
    ResetLogFile();

    LogMessage(
        "Isaac: ViewPoint initialized."
    );

    LoadConfiguration();

    LogMessage(
        ("Default model: " +
         std::string(DEFAULT_OBJECT)).c_str()
    );

    LogMessage(
        ("Selected model: " +
         g_ModelPath).c_str()
    );

    DiagnoseEmbeddedResources();

    return 0;
}
