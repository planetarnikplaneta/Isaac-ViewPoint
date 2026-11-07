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

using PFNGLUSEPROGRAMPROC = void (APIENTRY *)(GLuint);
using PFNGLACTIVETEXTUREPROC = void (APIENTRY *)(GLenum);

namespace OpenGL
{
    bool __stdcall wglSwapBuffers(HDC hdc);
}

namespace
{
    namespace fs = std::filesystem;

    // --------------------------------------------------
    // Configuration
    // --------------------------------------------------

    constexpr char DEFAULT_OBJECT[] = "objects/sphere.obj";

    constexpr float OBJECT_DISTANCE = 5.0f;
    constexpr float OBJECT_ROTATION_SPEED = 0.012f;
    constexpr float OBJECT_TILT = -12.0f;
    constexpr float OBJECT_FOV = 45.0f;

    constexpr float LIGHT_X = -0.35f;
    constexpr float LIGHT_Y = 0.55f;
    constexpr float LIGHT_Z = -0.76f;

    constexpr float AMBIENT_LIGHT = 0.40f;
    constexpr float DIFFUSE_LIGHT = 0.60f;

    // --------------------------------------------------
    // Structures
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

        float ambient[3] = { 0.2f, 0.2f, 0.2f };
        float diffuse[3] = { 1.0f, 1.0f, 1.0f };
        float specular[3] = { 0.0f, 0.0f, 0.0f };

        float shininess = 32.0f;

        std::string diffuseTexturePath;

        unsigned char* pixels = nullptr;

        int width = 0;
        int height = 0;

        GLuint textureId = 0;

        bool textureAttempted = false;
    };

    // --------------------------------------------------
    // Global state
    // --------------------------------------------------

    static HMODULE g_Module = nullptr;
    static HGLRC g_ResourceContext = nullptr;

    static PFNGLUSEPROGRAMPROC g_UseProgram = nullptr;
    static PFNGLACTIVETEXTUREPROC g_ActiveTexture = nullptr;

    static bool g_MeshAttempted = false;
    static bool g_MeshLoaded = false;

    static std::vector<Vertex3> g_Vertices;
    static std::vector<Vertex2> g_Texcoords;
    static std::vector<Vertex3> g_Normals;

    static std::vector<Triangle> g_Triangles;
    static std::vector<Material> g_Materials;

    // --------------------------------------------------
    // Logging
    // --------------------------------------------------

    static void LogMessage(const char* message)
    {
        FILE* file = fopen("C:\\MyNativeMod.log", "a");

        if (file)
        {
            fprintf(file, "Isaac ViewPoint: %s\n", message);
            fclose(file);
        }
    }

    // --------------------------------------------------
    // String helpers
    // --------------------------------------------------

    static std::string Trim(const std::string& text)
    {
        const size_t first = text.find_first_not_of(" \t\r\n");

        if (first == std::string::npos)
            return {};

        const size_t last = text.find_last_not_of(" \t\r\n");

        return text.substr(first, last - first + 1);
    }

    static std::string NormalizeAssetPath(std::string path)
    {
        std::replace(path.begin(), path.end(), '\\', '/');

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

        const size_t slash = parent.find_last_of('/');

        const std::string directory =
            slash == std::string::npos
                ? ""
                : parent.substr(0, slash + 1);

        return NormalizeAssetPath(directory + normalizedChild);
    }

    // --------------------------------------------------
    // DLL directory
    // --------------------------------------------------

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

    // --------------------------------------------------
    // Asset loading
    // --------------------------------------------------

    // First checks:
    // <DLL directory>/resources_ViewPoint/<asset path>
    //
    // If the external file does not exist, checks the
    // embedded Windows resource with the same name.
static std::string ToUpperResourceName(const std::string& name)
{
    std::string result = name;

    for (char& c : result)
    {
        if (c >= 'a' && c <= 'z')
            c = static_cast<char>(c - 'a' + 'A');
    }

    return result;
}

static HRSRC FindEmbeddedResource(
    HMODULE module,
    const std::string& assetPath)
{
    const std::string resourceName =
        ToUpperResourceName(assetPath);

    char message[512];

    snprintf(
        message,
        sizeof(message),
        "Resource lookup: module=%p, requested=\"%s\", lookup=\"%s\"",
        static_cast<void*>(module),
        assetPath.c_str(),
        resourceName.c_str()
    );

    LogMessage(message);

    SetLastError(ERROR_SUCCESS);

    HRSRC resource = FindResourceA(
        module,
        resourceName.c_str(),
        RT_RCDATA
    );

    if (!resource)
    {
        const DWORD error = GetLastError();

        snprintf(
            message,
            sizeof(message),
            "FindResourceA failed: error=%lu, lookup=\"%s\"",
            static_cast<unsigned long>(error),
            resourceName.c_str()
        );

        LogMessage(message);
    }
    else
    {
        LogMessage("FindResourceA succeeded.");
    }

    return resource;
}

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
        // External resource
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

                    const std::streamoff size = file.tellg();

                    if (size <= 0)
                        return false;

                    file.seekg(0, std::ios::beg);

                    output.resize(
                        static_cast<size_t>(size)
                    );

                    file.read(
                        reinterpret_cast<char*>(output.data()),
                        size
                    );

                    if (file)
                        return true;

                    output.clear();
                }
            }
        }
        catch (...)
        {
            LogMessage("External asset access failed");
        }

        // ----------------------------------------------
        // Embedded resource
        // ----------------------------------------------



HRSRC resource = FindEmbeddedResource(
    g_Module,
    assetPath
);

        if (!resource)
        {
            LogMessage(
                ("Embedded asset not found: " + assetPath).c_str()
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

        output.assign(bytes, bytes + size);

        return true;
    }

    // --------------------------------------------------
    // OBJ index parsing
    // --------------------------------------------------

    static bool ParseObjIndex(
        const std::string& token,
        int component,
        size_t count,
        int32_t& output)
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

        std::string number = token.substr(
            start,
            end - start
        );

        char* parseEnd = nullptr;

        long value = strtol(
            number.c_str(),
            &parseEnd,
            10
        );

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

        output = static_cast<int32_t>(resolved);

        return true;
    }

    // --------------------------------------------------
    // Material management
    // --------------------------------------------------

    static int FindOrCreateMaterial(
        const std::string& name,
        std::map<std::string, int>& lookup)
    {
        auto found = lookup.find(name);

        if (found != lookup.end())
            return found->second;

        Material material;
        material.name = name;

        const int index = static_cast<int>(
            g_Materials.size()
        );

        g_Materials.push_back(material);

        lookup[name] = index;

        return index;
    }

    // --------------------------------------------------
    // MTL loading
    // --------------------------------------------------

    static void LoadMTL(
        const std::string& mtlPath,
        std::map<std::string, int>& lookup)
    {
        std::vector<unsigned char> bytes;

        if (!ReadAsset(mtlPath, bytes))
        {
            LogMessage(
                ("Cannot load MTL: " + mtlPath).c_str()
            );

            return;
        }

        std::string source(
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

            // ------------------------------------------
            // Material name
            // ------------------------------------------

            if (command == "newmtl")
            {
                std::string name;

                std::getline(stream, name);
                name = Trim(name);

                if (!name.empty())
                {
                    currentMaterial =
                        FindOrCreateMaterial(name, lookup);
                }

                continue;
            }

            if (currentMaterial < 0)
                continue;

            Material& material =
                g_Materials[currentMaterial];

            // ------------------------------------------
            // Ambient
            // ------------------------------------------

            if (command == "Ka")
            {
                stream >>
                    material.ambient[0] >>
                    material.ambient[1] >>
                    material.ambient[2];
            }

            // ------------------------------------------
            // Diffuse
            // ------------------------------------------

            else if (command == "Kd")
            {
                stream >>
                    material.diffuse[0] >>
                    material.diffuse[1] >>
                    material.diffuse[2];
            }

            // ------------------------------------------
            // Specular
            // ------------------------------------------

            else if (command == "Ks")
            {
                stream >>
                    material.specular[0] >>
                    material.specular[1] >>
                    material.specular[2];
            }

            // ------------------------------------------
            // Shininess
            // ------------------------------------------

            else if (command == "Ns")
            {
                stream >> material.shininess;
            }

            // ------------------------------------------
            // Diffuse texture
            // ------------------------------------------

            else if (command == "map_Kd")
            {
                // Supports:
                // map_Kd texture.png
                //
                // Also tolerates common map options by
                // using the final whitespace-separated token.
                std::string texture;
                std::string token;

                while (stream >> token)
                    texture = token;

                if (!texture.empty())
                {
                    material.diffuseTexturePath =
                        ResolveRelativeAsset(
                            mtlPath,
                            texture
                        );
                }
            }
        }

        LogMessage(
            ("Loaded MTL: " + mtlPath).c_str()
        );
    }

    // --------------------------------------------------
    // PNG loading
    // --------------------------------------------------

    static void LoadMaterialTexture(Material& material)
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

        if (bytes.size() > static_cast<size_t>(INT_MAX))
            return;

        stbi_set_flip_vertically_on_load(1);

        material.pixels = stbi_load_from_memory(
            bytes.data(),
            static_cast<int>(bytes.size()),
            &material.width,
            &material.height,
            nullptr,
            4
        );

        if (!material.pixels)
        {
            LogMessage(
                ("PNG decoding failed: " +
                 material.diffuseTexturePath).c_str()
            );

            return;
        }

        LogMessage(
            ("Decoded PNG: " +
             material.diffuseTexturePath).c_str()
        );
    }

    // --------------------------------------------------
    // OpenGL texture upload
    // --------------------------------------------------

    static bool UploadMaterialTexture(Material& material)
    {
        LoadMaterialTexture(material);

        if (!material.pixels)
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
            material.pixels
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

    // --------------------------------------------------
    // OBJ loading
    // --------------------------------------------------

    static void LoadOBJ()
    {
        g_MeshAttempted = true;

        std::vector<unsigned char> bytes;

        if (!ReadAsset(DEFAULT_OBJECT, bytes))
        {
            LogMessage(
                ("Cannot load OBJ: " +
                 std::string(DEFAULT_OBJECT)).c_str()
            );

            return;
        }

        std::string source(
            reinterpret_cast<const char*>(bytes.data()),
            bytes.size()
        );

        std::istringstream input(source);

        std::string line;

        std::map<std::string, int> materialLookup;

        g_Vertices.clear();
        g_Texcoords.clear();
        g_Normals.clear();
        g_Triangles.clear();
        g_Materials.clear();

        // Default material for faces without usemtl.
        Material defaultMaterial;
        defaultMaterial.name = "__default";

        g_Materials.push_back(defaultMaterial);
        materialLookup["__default"] = 0;

        int activeMaterial = 0;

        while (std::getline(input, line))
        {
            line = Trim(line);

            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream stream(line);

            std::string command;
            stream >> command;

            // ------------------------------------------
            // Position
            // ------------------------------------------

            if (command == "v")
            {
                Vertex3 vertex{};

                if (stream >>
                    vertex.x >>
                    vertex.y >>
                    vertex.z)
                {
                    g_Vertices.push_back(vertex);
                }
            }

            // ------------------------------------------
            // UV
            // ------------------------------------------

            else if (command == "vt")
            {
                Vertex2 uv{};

                if (stream >> uv.u >> uv.v)
                    g_Texcoords.push_back(uv);
            }

            // ------------------------------------------
            // Normal
            // ------------------------------------------

            else if (command == "vn")
            {
                Vertex3 normal{};

                if (stream >>
                    normal.x >>
                    normal.y >>
                    normal.z)
                {
                    g_Normals.push_back(normal);
                }
            }

            // ------------------------------------------
            // Material library
            // ------------------------------------------

            else if (command == "mtllib")
            {
                std::string filename;

                std::getline(stream, filename);
                filename = Trim(filename);

                if (!filename.empty())
                {
                    const std::string mtlPath =
                        ResolveRelativeAsset(
                            DEFAULT_OBJECT,
                            filename
                        );

                    if (!mtlPath.empty())
                    {
                        LoadMTL(
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

                auto found = materialLookup.find(name);

                activeMaterial =
                    found != materialLookup.end()
                        ? found->second
                        : 0;
            }

            // ------------------------------------------
            // Faces
            // ------------------------------------------

            else if (command == "f")
            {
                std::vector<ObjCorner> face;

                std::string token;

                while (stream >> token)
                {
                    ObjCorner corner;

                    if (!ParseObjIndex(
                        token,
                        0,
                        g_Vertices.size(),
                        corner.position))
                    {
                        continue;
                    }

                    ParseObjIndex(
                        token,
                        1,
                        g_Texcoords.size(),
                        corner.texcoord
                    );

                    ParseObjIndex(
                        token,
                        2,
                        g_Normals.size(),
                        corner.normal
                    );

                    face.push_back(corner);
                }

                // Triangulate polygon faces.
                for (size_t i = 1; i + 1 < face.size(); ++i)
                {
                    Triangle triangle{};

                    triangle.corners[0] = face[0];
                    triangle.corners[1] = face[i];
                    triangle.corners[2] = face[i + 1];

                    triangle.materialIndex = activeMaterial;

                    g_Triangles.push_back(triangle);
                }
            }
        }

        // ----------------------------------------------
        // Validate mesh
        // ----------------------------------------------

        if (g_Vertices.empty() || g_Triangles.empty())
        {
            LogMessage("OBJ has no usable vertices or faces");
            return;
        }

        // ----------------------------------------------
        // Bounding box
        // ----------------------------------------------

        Vertex3 lo = g_Vertices.front();
        Vertex3 hi = g_Vertices.front();

        for (const Vertex3& v : g_Vertices)
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

        for (Vertex3& v : g_Vertices)
        {
            v.x = (v.x - cx) * scale;
            v.y = (v.y - cy) * scale;
            v.z = (v.z - cz) * scale;
        }

        g_MeshLoaded = true;

        char message[256];

        snprintf(
            message,
            sizeof(message),
            "Loaded OBJ: %zu vertices, %zu UVs, %zu normals, %zu triangles, %zu materials",
            g_Vertices.size(),
            g_Texcoords.size(),
            g_Normals.size(),
            g_Triangles.size(),
            g_Materials.size()
        );

        LogMessage(message);
    }

    // --------------------------------------------------
    // Normal calculations
    // --------------------------------------------------

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

    static Vertex3 NormalizeNormal(const Vertex3& normal)
    {
        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z
        );

        if (length < 1e-8f)
            return { 0.0f, 0.0f, 1.0f };

        return {
            normal.x / length,
            normal.y / length,
            normal.z / length
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

    // --------------------------------------------------
    // OpenGL function loading
    // --------------------------------------------------

    static PROC GetGLProc(const char* name)
    {
        PROC proc = wglGetProcAddress(name);

        if (!proc ||
            proc == reinterpret_cast<PROC>(1) ||
            proc == reinterpret_cast<PROC>(2) ||
            proc == reinterpret_cast<PROC>(3) ||
            proc == reinterpret_cast<PROC>(-1))
        {
            HMODULE gl = GetModuleHandleA("opengl32.dll");

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

            // Texture IDs belong to their OpenGL context.
            for (Material& material : g_Materials)
                material.textureId = 0;

            LogMessage("OpenGL context changed");
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
            LogMessage("glUseProgram unavailable");
            return false;
        }

        return true;
    }

    // --------------------------------------------------
    // Triangle rendering
    // --------------------------------------------------

    static void RenderTriangle(const Triangle& triangle)
    {
        const ObjCorner* corners[3] = {
            &triangle.corners[0],
            &triangle.corners[1],
            &triangle.corners[2]
        };

        const Vertex3* positions[3] = {
            &g_Vertices[corners[0]->position],
            &g_Vertices[corners[1]->position],
            &g_Vertices[corners[2]->position]
        };

        const Vertex3 faceNormal = CalculateFaceNormal(
            *positions[0],
            *positions[1],
            *positions[2]
        );

        const int materialIndex =
            triangle.materialIndex >= 0 &&
            static_cast<size_t>(triangle.materialIndex) <
                g_Materials.size()
                ? triangle.materialIndex
                : 0;

        const Material& material =
            g_Materials[materialIndex];

        for (int i = 0; i < 3; ++i)
        {
            const ObjCorner& corner = *corners[i];

            Vertex3 normal = faceNormal;

            if (corner.normal >= 0 &&
                static_cast<size_t>(corner.normal) <
                    g_Normals.size())
            {
                normal = NormalizeNormal(
                    g_Normals[corner.normal]
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
                    g_Texcoords.size())
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
                positions[i]->x,
                positions[i]->y,
                positions[i]->z
            );
        }
    }

    // --------------------------------------------------
    // Main renderer
    // --------------------------------------------------

    static void RenderTriangleMesh()
    {
        if (!EnsureContext())
            return;

        if (!g_MeshAttempted)
            LoadOBJ();

        if (!g_MeshLoaded)
            return;

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

        // ----------------------------------------------
        // Save OpenGL state
        // ----------------------------------------------

        glPushAttrib(GL_ALL_ATTRIB_BITS);

        if (g_ActiveTexture)
            g_ActiveTexture(GL_TEXTURE0);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // ----------------------------------------------
        // Configure rendering
        // ----------------------------------------------

        g_UseProgram(0);

        glDisable(GL_CULL_FACE);
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
        // Perspective
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
        // Render each material separately
        // ----------------------------------------------

        for (size_t materialIndex = 0;
             materialIndex < g_Materials.size();
             ++materialIndex)
        {
            Material& material =
                g_Materials[materialIndex];

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

            for (const Triangle& triangle : g_Triangles)
            {
                if (triangle.materialIndex !=
                    static_cast<int>(materialIndex))
                {
                    continue;
                }

                bool valid = true;

                for (const ObjCorner& corner : triangle.corners)
                {
                    if (corner.position < 0 ||
                        static_cast<size_t>(corner.position) >=
                            g_Vertices.size())
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                    RenderTriangle(triangle);
            }

            glEnd();
        }

        // ----------------------------------------------
        // Restore OpenGL state
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
// some debug
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
            static_cast<unsigned>(reinterpret_cast<ULONG_PTR>(name))
        );

        LogMessage(message);
        return TRUE;
    }

    snprintf(
        message,
        sizeof(message),
        "Enumerated resource: module=%p, name=\"%s\"",
        static_cast<void*>(module),
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
        LogMessage("Lookup using enumerated name: SUCCESS");
    }
    else
    {
        snprintf(
            message,
            sizeof(message),
            "Lookup using enumerated name: FAILED, error=%lu",
            static_cast<unsigned long>(GetLastError())
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
// --------------------------------------------------
// Mod initialization
// --------------------------------------------------

extern "C" __declspec(dllexport) int ModInit()
{
    LogMessage("Isaac: ViewPoint initialized");
    LogMessage(("Default model: " + std::string(DEFAULT_OBJECT)).c_str());

    DiagnoseEmbeddedResources();

    return 0;
}
