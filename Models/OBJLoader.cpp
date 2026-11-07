#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "OBJLoader.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../Core/Logger.h"
#include "../Core/AssetPaths.h"
#include "../Resources/ResourceManager.h"

namespace
{
    // OBJ INDEX PARSING

    bool ParseObjIndex(
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

    int FindOrCreateMaterial(
        const std::string& name,
        std::map<std::string, int>& lookup,
        ViewPoint::Model& model)
    {
        auto found = lookup.find(name);

        if (found != lookup.end())
            return found->second;

        ViewPoint::Material material;
        material.name = name;

        const int index =
            static_cast<int>(model.materials.size());

        model.materials.push_back(
            std::move(material));

        lookup[name] = index;

        return index;
    }

    // MTL TEXTURE PATH PARSING

    std::string GetMapFilename(
        std::istringstream& stream)
    {
        std::vector<std::string> tokens;

        std::string token;

        while (stream >> token)
            tokens.push_back(token);

        if (tokens.empty())
            return {};

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
                return tokens.back();
            }

            ++i;

            for (size_t n = 0;
                 n < argumentCount && i < tokens.size();
                 ++n)
            {
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

        return tokens[i];
    }

    // MTL LOADING

    void LoadMTL(
        ViewPoint::Model& model,
        const std::string& mtlPath,
        std::map<std::string, int>& lookup)
    {
        std::vector<unsigned char> bytes;

        if (!ViewPoint::ReadAsset(mtlPath, bytes))
        {
            ViewPoint::LogMessage(
                ("Cannot load MTL: " + mtlPath).c_str());

            return;
        }

        const std::string source(
            reinterpret_cast<const char*>(bytes.data()),
            bytes.size());

        std::istringstream input(source);

        std::string line;

        int currentMaterial = -1;

        while (std::getline(input, line))
        {
            line = ViewPoint::Trim(line);

            if (line.empty() || line[0] == '#')
                continue;

            std::istringstream stream(line);

            std::string command;
            stream >> command;

            if (command == "newmtl")
            {
                std::string name;

                std::getline(stream, name);
                name = ViewPoint::Trim(name);

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

            ViewPoint::Material& material =
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
                        ViewPoint::ResolveRelativeAsset(
                            mtlPath,
                            texture);

                    ViewPoint::LogMessage(
                        ("Material texture: " +
                         material.name + " -> " +
                         material.diffuseTexturePath).c_str());
                }
            }
        }

        ViewPoint::LogMessage(
            ("Loaded MTL: " + mtlPath).c_str());
    }

    // MODEL BOUNDING BOX / NORMALIZATION

    void NormalizeModel(ViewPoint::Model& model)
    {
        if (model.vertices.empty())
            return;

        ViewPoint::Vertex3 lo = model.vertices.front();
        ViewPoint::Vertex3 hi = model.vertices.front();

        for (const ViewPoint::Vertex3& v : model.vertices)
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

        const float extent =
            (std::max)(
                (std::max)(hi.x - lo.x, hi.y - lo.y),
                (std::max)(hi.z - lo.z, 0.0001f));

        const float scale = 2.0f / extent;

        for (ViewPoint::Vertex3& v : model.vertices)
        {
            v.x = (v.x - cx) * scale;
            v.y = (v.y - cy) * scale;
            v.z = (v.z - cz) * scale;
        }
    }
}

namespace ViewPoint
{
    // OBJ LOADING

    bool LoadOBJ(Model& model)
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
                ("Cannot load OBJ: " + model.path).c_str());

            return false;
        }

        const std::string source(
            reinterpret_cast<const char*>(bytes.data()),
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
            else if (command == "vt")
            {
                Vertex2 uv;

                if (stream >> uv.u >> uv.v)
                {
                    model.texcoords.push_back(uv);
                }
            }
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
                        ("Unknown material: " + name).c_str());
                }
            }
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

                    triangle.materialIndex = activeMaterial;

                    model.triangles.push_back(triangle);
                }
            }
        }

        // VALIDATION

        if (model.vertices.empty() ||
            model.triangles.empty())
        {
            LogMessage(
                "OBJ contains no usable geometry.");

            return false;
        }

        // NORMALIZE GEOMETRY

        NormalizeModel(model);

        model.loaded = true;

        // DIAGNOSTICS

        char message[512];

        snprintf(
            message,
            sizeof(message),
            "Loaded OBJ: %s",
            model.path.c_str());

        LogMessage(message);

        LogNumber("Vertex count", model.vertices.size());
        LogNumber("UV count", model.texcoords.size());
        LogNumber("Normal count", model.normals.size());
        LogNumber("Triangle count", model.triangles.size());
        LogNumber("Material count", model.materials.size());

        LogNumber(
            "Faces without UV coordinates",
            facesWithoutUV);

        LogNumber(
            "Faces without normals",
            facesWithoutNormals);

        for (const Material& material : model.materials)
        {
            LogMessage(
                ("Material loaded: " + material.name).c_str());

            if (material.diffuseTexturePath.empty())
            {
                LogMessage(
                    ("Material has no diffuse texture: " +
                     material.name).c_str());
            }
        }

        return true;
    }
}
