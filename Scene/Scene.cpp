#include "Scene.h"

#include "../Core/State.h"
#include "../Core/Logger.h"
#include "../Core/Config.h"

#include "../Models/OBJLoader.h"
#include "../Models/Texture.h"
#include "../Models/GpuMesh.h"

#include <filesystem>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

namespace ViewPoint
{
    namespace fs = std::filesystem;

    constexpr unsigned int CONFIG_CHECK_INTERVAL = 60;

    // SCENE LOADING

    bool LoadScene(
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

    bool LoadConfiguredScene()
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

    void CheckConfigurationReload()
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

}
