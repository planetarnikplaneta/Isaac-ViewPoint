#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Texture.h"

#include <Windows.h>
#include <gl/GL.h>

#include <climits>
#include <cstdio>
#include <vector>

#include "../Core/Logger.h"
#include "../Resources/ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

namespace
{
    void LoadMaterialTexture(ViewPoint::Material& material)
    {
        if (material.textureAttempted)
            return;

        material.textureAttempted = true;

        if (material.diffuseTexturePath.empty())
            return;

        std::vector<unsigned char> bytes;

        if (!ViewPoint::ReadAsset(
                material.diffuseTexturePath,
                bytes))
        {
            ViewPoint::LogMessage(
                ("Cannot load texture: " +
                 material.diffuseTexturePath).c_str());

            return;
        }

        if (bytes.size() > static_cast<size_t>(INT_MAX))
        {
            ViewPoint::LogMessage("Texture file is too large.");
            return;
        }

        int channels = 0;

        stbi_set_flip_vertically_on_load(1);

        unsigned char* decoded = stbi_load_from_memory(
            bytes.data(),
            static_cast<int>(bytes.size()),
            &material.width,
            &material.height,
            &channels,
            4);

        if (!decoded)
        {
            ViewPoint::LogMessage(
                ("PNG decoding failed: " +
                 material.diffuseTexturePath).c_str());

            return;
        }

        const size_t pixelSize =
            static_cast<size_t>(material.width) *
            static_cast<size_t>(material.height) * 4;

        material.pixels.assign(
            decoded,
            decoded + pixelSize);

        stbi_image_free(decoded);

        char message[256];

        snprintf(
            message,
            sizeof(message),
            "Decoded texture: %s (%dx%d, source channels=%d)",
            material.diffuseTexturePath.c_str(),
            material.width,
            material.height,
            channels);

        ViewPoint::LogMessage(message);
    }
}

namespace ViewPoint
{
    bool UploadMaterialTexture(Material& material)
    {
        LoadMaterialTexture(material);

        if (material.pixels.empty())
            return false;

        if (material.textureId != 0)
            return true;

        glGenTextures(
            1,
            &material.textureId);

        if (!material.textureId)
            return false;

        glBindTexture(
            GL_TEXTURE_2D,
            material.textureId);

        glPixelStorei(
            GL_UNPACK_ALIGNMENT,
            1);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            material.width,
            material.height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            material.pixels.data());

        const GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            char message[128];

            snprintf(
                message,
                sizeof(message),
                "Texture upload failed: 0x%X",
                error);

            LogMessage(message);

            glDeleteTextures(
                1,
                &material.textureId);

            material.textureId = 0;

            return false;
        }

        return true;
    }

    void ReleaseModelTextures(Model& model)
    {
        // OpenGL resources can only be deleted when their
        // owning context is current.
        if (!wglGetCurrentContext())
            return;

        for (Material& material : model.materials)
        {
            if (material.textureId != 0)
            {
                glDeleteTextures(
                    1,
                    &material.textureId);

                material.textureId = 0;
            }
        }
    }
}
