#pragma once

#include <string>
#include <vector>

#include <Windows.h>

namespace ViewPoint
{
    bool ReadAsset(
        const std::string& requestedPath,
        std::vector<unsigned char>& output);

    void DiagnoseEmbeddedResources();
}
