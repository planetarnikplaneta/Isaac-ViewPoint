#pragma once

#include <string>

namespace ViewPoint
{
    std::string Trim(const std::string& text);

    std::string NormalizeAssetPath(std::string path);

    std::string ResolveRelativeAsset(
        const std::string& parent,
        const std::string& child);

    std::string ToUpperResourceName(const std::string& name);
}
