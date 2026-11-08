#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Types.h"

namespace ViewPoint
{
    // Default object rendering is intentionally disabled.
    // This must remain empty so no accidental fallback loads a model.
    inline constexpr char DEFAULT_OBJECT[] = "";

    std::filesystem::path GetConfigurationPath();

    bool ReadConfiguration(std::vector<ObjectConfig>& output);

    void LoadConfiguration();
}
