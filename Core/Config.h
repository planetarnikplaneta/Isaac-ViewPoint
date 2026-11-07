#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Types.h"

namespace ViewPoint
{
    inline constexpr char DEFAULT_OBJECT[] = "objects/sphere.obj";

    std::filesystem::path GetConfigurationPath();

    bool ReadConfiguration(std::vector<ObjectConfig>& output);

    void LoadConfiguration();
}
