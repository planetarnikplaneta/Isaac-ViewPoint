#pragma once

#include "../Core/Types.h"

namespace ViewPoint
{
    bool BuildGpuMesh(Model& model);
    void ReleaseModelGpu(Model& model);

    Vertex3 CalculateFaceNormal(
        const Vertex3& a,
        const Vertex3& b,
        const Vertex3& c);

    Vertex3 NormalizeNormal(const Vertex3& normal);
}
