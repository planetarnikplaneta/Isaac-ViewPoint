#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "GpuMesh.h"

#include <Windows.h>
#include <gl/GL.h>

#include <algorithm>
#include <cmath>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <vector>
#include <utility>

#include "../Core/Logger.h"
#include "../Core/State.h"

#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

namespace ViewPoint
{
      static void ReleaseModelGpu(Model &model)
    {
        if (wglGetCurrentContext() &&
            g_DeleteBuffers)
        {
            for (MaterialBatch &batch : model.gpuBatches)
            {
                if (batch.vertexBuffer)
                {
                    g_DeleteBuffers(
                        1,
                        &batch.vertexBuffer);
                }
            }
        }

        model.gpuBatches.clear();
        model.gpuReady = false;
        model.gpuBuildAttempted = false;
    }

    static bool BuildGpuMesh(Model &model)
    {
        if (model.gpuReady)
            return true;

        if (model.gpuBuildAttempted)
            return false;

        model.gpuBuildAttempted = true;

        if (!model.loaded || model.materials.empty())
            return false;

        std::vector<std::vector<GpuVertex>> materialVertices(
            model.materials.size());

        for (const Triangle &triangle : model.triangles)
        {
            if (triangle.materialIndex < 0 ||
                static_cast<size_t>(triangle.materialIndex) >=
                    model.materials.size())
            {
                continue;
            }

            const int materialIndex = triangle.materialIndex;

            const ObjCorner &a = triangle.corners[0];
            const ObjCorner &b = triangle.corners[1];
            const ObjCorner &c = triangle.corners[2];

            if (a.position < 0 || b.position < 0 || c.position < 0 ||
                static_cast<size_t>(a.position) >= model.vertices.size() ||
                static_cast<size_t>(b.position) >= model.vertices.size() ||
                static_cast<size_t>(c.position) >= model.vertices.size())
            {
                continue;
            }

            const Vertex3 &pa = model.vertices[a.position];
            const Vertex3 &pb = model.vertices[b.position];
            const Vertex3 &pc = model.vertices[c.position];

            const Vertex3 faceNormal =
                CalculateFaceNormal(pa, pb, pc);

            const ObjCorner *corners[3] = {
                &a, &b, &c};

            for (int i = 0; i < 3; ++i)
            {
                const ObjCorner &corner = *corners[i];

                GpuVertex vertex{};

                vertex.position =
                    model.vertices[corner.position];

                vertex.normal = faceNormal;

                if (corner.normal >= 0 &&
                    static_cast<size_t>(corner.normal) <
                        model.normals.size())
                {
                    vertex.normal = NormalizeNormal(
                        model.normals[corner.normal]);
                }

                if (corner.texcoord >= 0 &&
                    static_cast<size_t>(corner.texcoord) <
                        model.texcoords.size())
                {
                    vertex.texcoord =
                        model.texcoords[corner.texcoord];
                }

                materialVertices[materialIndex].push_back(vertex);
            }
        }

        std::vector<MaterialBatch> newBatches;

        newBatches.reserve(materialVertices.size());

        for (size_t i = 0; i < materialVertices.size(); ++i)
        {
            std::vector<GpuVertex> &vertices =
                materialVertices[i];

            if (vertices.empty())
                continue;

            if (vertices.size() >
                static_cast<size_t>(INT_MAX))
            {
                ViewPoint::LogMessage("GPU mesh contains too many vertices.");
                return false;
            }

            MaterialBatch batch;

            batch.materialIndex = static_cast<int>(i);
            batch.vertexCount =
                static_cast<GLsizei>(vertices.size());

            g_GenBuffers(
                1,
                &batch.vertexBuffer);

            if (!batch.vertexBuffer)
            {
                ViewPoint::LogMessage("Failed to create a VBO.");
                return false;
            }

            g_BindBuffer(
                GL_ARRAY_BUFFER,
                batch.vertexBuffer);

            g_BufferData(
                GL_ARRAY_BUFFER,
                static_cast<ptrdiff_t>(
                    vertices.size() * sizeof(GpuVertex)),
                vertices.data(),
                GL_STATIC_DRAW);

            const GLenum error = glGetError();

            if (error != GL_NO_ERROR)
            {
                char message[128];

                snprintf(
                    message,
                    sizeof(message),
                    "VBO upload failed: 0x%X",
                    error);

                ViewPoint::LogMessage(message);

                g_DeleteBuffers(
                    1,
                    &batch.vertexBuffer);

                return false;
            }

            newBatches.push_back(batch);
        }

        g_BindBuffer(GL_ARRAY_BUFFER, 0);

        if (newBatches.empty())
        {
            ViewPoint::LogMessage("GPU mesh contains no drawable batches.");
            return false;
        }

        model.gpuBatches = std::move(newBatches);
        model.gpuReady = true;

        ViewPoint::LogMessage(
            ("GPU mesh created: " + model.path).c_str());

        ViewPoint::LogNumber(
            "GPU material batches",
            model.gpuBatches.size());

        return true;
    }
    static Vertex3 CalculateFaceNormal(
        const Vertex3 &a,
        const Vertex3 &b,
        const Vertex3 &c)
    {
        const float ux = b.x - a.x;
        const float uy = b.y - a.y;
        const float uz = b.z - a.z;

        const float vx = c.x - a.x;
        const float vy = c.y - a.y;
        const float vz = c.z - a.z;

        Vertex3 normal;

        normal.x = uy * vz - uz * vy;
        normal.y = uz * vx - ux * vz;
        normal.z = ux * vy - uy * vx;

        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z);

        if (length < 1e-8f)
            return {0.0f, 0.0f, 1.0f};

        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        return normal;
    }

    static Vertex3 NormalizeNormal(
        const Vertex3 &normal)
    {
        const float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z);

        if (length < 1e-8f)
            return {0.0f, 0.0f, 1.0f};

        return {
            normal.x / length,
            normal.y / length,
            normal.z / length};
    }

}
