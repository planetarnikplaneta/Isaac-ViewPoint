
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Texture.h"

#include <Windows.h>
#include <gl/GL.h>

#include <climits>
#include <cstdio>
#include <utility>
#include <vector>

#include "../Core/Logger.h"
#include "../Resources/ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#ifndef GL_UNPACK_ROW_LENGTH
#define GL_UNPACK_ROW_LENGTH 0x0CF2
#endif

#ifndef GL_UNPACK_SKIP_ROWS
#define GL_UNPACK_SKIP_ROWS 0x0CF3
#endif

#ifndef GL_UNPACK_SKIP_PIXELS
#define GL_UNPACK_SKIP_PIXELS 0x0CF4
#endif

namespace
{
    struct UnpackState
    {
        GLint alignment = 4;
        GLint rowLength = 0;
        GLint skipRows = 0;
        GLint skipPixels = 0;
    };

    UnpackState SetTightUnpackState()
    {
        UnpackState old;

        glGetIntegerv(GL_UNPACK_ALIGNMENT, &old.alignment);
        glGetIntegerv(GL_UNPACK_ROW_LENGTH, &old.rowLength);
        glGetIntegerv(GL_UNPACK_SKIP_ROWS, &old.skipRows);
        glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &old.skipPixels);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

        return old;
    }

    void RestoreUnpackState(const UnpackState& old)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, old.alignment);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, old.rowLength);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, old.skipRows);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, old.skipPixels);
    }

    void LoadMaterialTexture(ViewPoint::Material& material)
    {
        if (material.textureAttempted)
            return;

        material.textureAttempted = true;

        if (material.diffuseTexturePath.empty())
            return;

        std::vector<unsigned char> bytes;

        if (!ViewPoint::ReadAsset(material.diffuseTexturePath, bytes))
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

        material.pixels.assign(decoded, decoded + pixelSize);

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

    bool UploadPixels(
        GLuint textureId,
        int width,
        int height,
        const unsigned char* pixels,
        bool recreate)
    {
        if (!textureId || width <= 0 || height <= 0 || !pixels)
            return false;

        GLint oldBinding = 0;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldBinding);

        glBindTexture(GL_TEXTURE_2D, textureId);

        const UnpackState oldUnpack = SetTightUnpackState();

        if (recreate)
        {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                pixels);
        }
        else
        {
            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                0,
                0,
                width,
                height,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                pixels);
        }

        RestoreUnpackState(oldUnpack);

        const GLenum error = glGetError();

        glBindTexture(
            GL_TEXTURE_2D,
            static_cast<GLuint>(oldBinding));

        if (error != GL_NO_ERROR)
        {
            char message[128];

            snprintf(
                message,
                sizeof(message),
                "Texture upload failed: 0x%X",
                error);

            ViewPoint::LogMessage(message);
            return false;
        }

        return true;
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

        glGenTextures(1, &material.textureId);

        if (!material.textureId)
            return false;

        glBindTexture(GL_TEXTURE_2D, material.textureId);

glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER,
    GL_NEAREST);

glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MAG_FILTER,
    GL_NEAREST);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT);

        if (!UploadPixels(
                material.textureId,
                material.width,
                material.height,
                material.pixels.data(),
                true))
        {
            glDeleteTextures(1, &material.textureId);
            material.textureId = 0;
            return false;
        }

        return true;
    }

    bool UpdateMaterialTexture(
        Material& material,
        int width,
        int height,
        std::vector<unsigned char>&& pixels)
    {
        if (width <= 0 || height <= 0)
            return false;

        const size_t expected =
            static_cast<size_t>(width) *
            static_cast<size_t>(height) * 4;

        if (pixels.size() != expected)
            return false;

        const bool dimensionsChanged =
            material.width != width ||
            material.height != height;

        material.width = width;
        material.height = height;
        material.pixels = std::move(pixels);
        material.textureAttempted = true;
        material.diffuseTexturePath.clear();

        if (!material.textureId)
            return true;

        if (!wglGetCurrentContext())
            return true;

        return UploadPixels(
            material.textureId,
            width,
            height,
            material.pixels.data(),
            dimensionsChanged);
    }

    void ReleaseModelTextures(Model& model)
    {
        if (!wglGetCurrentContext())
            return;

        for (Material& material : model.materials)
        {
            if (material.textureId != 0)
            {
                glDeleteTextures(1, &material.textureId);
                material.textureId = 0;
            }
        }
    }
}
