#include "Config.h"

#include "State.h"
#include "Logger.h"
#include "AssetPaths.h"

#include <Windows.h>

#include <cmath>
#include <fstream>
#include <sstream>
#include <utility>

namespace
{
    namespace fs = std::filesystem;

    constexpr char CONFIG_FILE[] = "IsaacViewPoint.ini";

    fs::path GetDllDirectory()
    {
        char modulePath[MAX_PATH] = {};

        DWORD length = GetModuleFileNameA(
            ViewPoint::g_Module,
            modulePath,
            MAX_PATH);

        if (!length || length >= MAX_PATH)
            return fs::current_path();

        return fs::path(
            std::string(modulePath, length))
            .parent_path();
    }

    bool ParseVector3Text(
        const std::string& text,
        ViewPoint::Vertex3& output)
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
            const std::string trimmedX = ViewPoint::Trim(x);
            const std::string trimmedY = ViewPoint::Trim(y);
            const std::string trimmedZ = ViewPoint::Trim(z);

            size_t usedX = 0;
            size_t usedY = 0;
            size_t usedZ = 0;

            output.x = std::stof(trimmedX, &usedX);
            output.y = std::stof(trimmedY, &usedY);
            output.z = std::stof(trimmedZ, &usedZ);

            if (usedX != trimmedX.size() ||
                usedY != trimmedY.size() ||
                usedZ != trimmedZ.size())
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

    bool ParseObjectConfiguration(
        const std::string& value,
        ViewPoint::ObjectConfig& output)
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

        path = ViewPoint::Trim(path);
        position = ViewPoint::Trim(position);
        rotation = ViewPoint::Trim(rotation);
        scale = ViewPoint::Trim(scale);

        if (path.size() >= 2 &&
            path.front() == '"' &&
            path.back() == '"')
        {
            path = path.substr(1, path.size() - 2);
        }

        output.path = ViewPoint::NormalizeAssetPath(path);

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
}

namespace ViewPoint
{
    std::filesystem::path GetConfigurationPath()
    {
        return GetDllDirectory() / CONFIG_FILE;
    }

    bool ReadConfiguration(
        std::vector<ObjectConfig>& output)
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
                    LogMessage(
                        ("Invalid Object configuration: " +
                         value).c_str());

                    return false;
                }

                output.push_back(std::move(object));
            }
        }

        // Backwards compatibility with the old Model= format.
        // A missing or invalid config should not silently inject an
        // extra sphere into the scene; only a real configured object
        // should be loaded.
        if (output.empty() && !legacyModel.empty())
        {
            ObjectConfig object;

            std::string path = legacyModel;

            if (path.size() >= 2 &&
                path.front() == '"' &&
                path.back() == '"')
            {
                path = path.substr(1, path.size() - 2);
            }

            object.path = NormalizeAssetPath(path);

            if (object.path.empty())
            {
                LogMessage(
                    "Invalid Model path in configuration.");

                return false;
            }

            output.push_back(std::move(object));
        }

        return true;
    }

    void LoadConfiguration()
    {
        std::vector<ObjectConfig> configuredObjects;

        if (!ReadConfiguration(configuredObjects))
        {
            LogMessage(
                "Configuration file not found or invalid; leaving scene empty until a valid object is configured.");

            configuredObjects.clear();
        }

        g_ObjectConfigs = std::move(configuredObjects);

        LogNumber(
            "Configured object count",
            g_ObjectConfigs.size());

        for (size_t i = 0; i < g_ObjectConfigs.size(); ++i)
        {
            LogMessage(
                ("Configured object " +
                 std::to_string(i) + ": " +
                 g_ObjectConfigs[i].path).c_str());
        }

        std::error_code error;

        const fs::file_time_type timestamp =
            fs::last_write_time(
                GetConfigurationPath(),
                error);

        if (error)
        {
            g_ConfigTimestampValid = false;
        }
        else
        {
            g_ConfigLastWriteTime = timestamp;
            g_ConfigTimestampValid = true;
        }
    }
}
