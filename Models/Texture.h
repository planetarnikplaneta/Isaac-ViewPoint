#pragma once

#include "../Core/Types.h"

namespace ViewPoint
{
    bool UploadMaterialTexture(Material& material);

    void ReleaseModelTextures(Model& model);

    bool UpdateMaterialTexture(
        Material& material,
        int width,
        int height,
        std::vector<unsigned char>&& pixels);
}
