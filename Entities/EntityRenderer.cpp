#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "EntityRenderer.h"

#include "../Core/Logger.h"
#include "../Core/State.h"
#include "../Core/Types.h"
#include "../Camera/Camera.h"

#include <Windows.h>
#include <gl/GL.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "../IsaacRepentance.h"

#ifndef GL_CURRENT_PROGRAM
#define GL_CURRENT_PROGRAM 0x8B8D
#endif

#ifndef GL_ACTIVE_TEXTURE
#define GL_ACTIVE_TEXTURE 0x84E0
#endif

#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif

#ifndef GL_RGBA
#define GL_RGBA 0x1908
#endif

#ifndef GL_UNSIGNED_BYTE
#define GL_UNSIGNED_BYTE 0x1401
#endif

#ifndef GL_TEXTURE_MIN_FILTER
#define GL_TEXTURE_MIN_FILTER 0x2801
#endif

#ifndef GL_TEXTURE_MAG_FILTER
#define GL_TEXTURE_MAG_FILTER 0x2800
#endif

#ifndef GL_TEXTURE_WRAP_S
#define GL_TEXTURE_WRAP_S 0x2802
#endif

#ifndef GL_TEXTURE_WRAP_T
#define GL_TEXTURE_WRAP_T 0x2803
#endif

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#ifndef GL_QUADS
#define GL_QUADS 0x0007
#endif

#ifndef GL_LINES
#define GL_LINES 0x0001
#endif

#ifndef GL_LINE_LOOP
#define GL_LINE_LOOP 0x0002
#endif

namespace ViewPoint
{
    namespace
    {
        constexpr float PI = 3.14159265358979323846f;

        constexpr float ISAAC_PIXELS_PER_TILE = 40.0f;

        constexpr float ROOM_FLOOR_Y = -1.5f;

        constexpr float CAPSULE_HEIGHT_OFFSET = 0.025f;

        constexpr int CAPSULE_SEGMENTS = 16;

        struct SpriteTexture
        {
            GLuint texture = 0;
            int width = 0;
            int height = 0;
        };

        // Keyed by the actual REPENTOGON image pointer.
        std::unordered_map<
            KAGE_Graphics_ImageBase *,
            SpriteTexture>
            g_SpriteTextures;

        HGLRC g_EntityTextureContext = nullptr;

        // --------------------------------------------------
        // ROOM POSITION CONVERSION
        // --------------------------------------------------

        static Vector IsaacPositionToWorld(
            const Vector &position,
            Room *room)
        {
            const float roomCenterX =
                320.0f +
                (static_cast<float>(room->_gridWidth) - 15.0f) *
                    20.0f;

            const float roomCenterY =
                280.0f +
                (static_cast<float>(room->_gridHeight) - 9.0f) *
                    20.0f;

            return Vector(
                (position.x - roomCenterX) /
                    ISAAC_PIXELS_PER_TILE,

                (roomCenterY - position.y) /
                    ISAAC_PIXELS_PER_TILE);
        }

        // --------------------------------------------------
        // SPRITE TEXTURE CACHE
        // --------------------------------------------------

        static SpriteTexture *GetSpriteTexture(
            KAGE_Graphics_ImageBase *image)
        {
            if (!image)
                return nullptr;

            auto found = g_SpriteTextures.find(image);

            if (found != g_SpriteTextures.end())
                return &found->second;

            const int width = static_cast<int>(
                image->GetWidth());

            const int height = static_cast<int>(
                image->GetHeight());

            if (width <= 0 || height <= 0)
                return nullptr;

            const size_t pixelCount =
                static_cast<size_t>(width) *
                static_cast<size_t>(height);

            if (pixelCount > 64u * 1024u * 1024u)
                return nullptr;

            std::vector<unsigned char> pixels(
                pixelCount * 4u);

            // REPENTOGON returns raw RGBA pixels.
            image->GetTexelRegion(
                0,
                0,
                static_cast<unsigned int>(width),
                static_cast<unsigned int>(height),
                pixels.data());

            SpriteTexture result;

            result.width = width;
            result.height = height;

            glGenTextures(
                1,
                &result.texture);

            if (!result.texture)
                return nullptr;

            glBindTexture(
                GL_TEXTURE_2D,
                result.texture);

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
                GL_CLAMP_TO_EDGE);

            glTexParameteri(
                GL_TEXTURE_2D,
                GL_TEXTURE_WRAP_T,
                GL_CLAMP_TO_EDGE);

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                pixels.data());

            if (glGetError() != GL_NO_ERROR)
            {
                glDeleteTextures(
                    1,
                    &result.texture);

                return nullptr;
            }

            auto inserted = g_SpriteTextures.emplace(
                image,
                result);

            return &inserted.first->second;
        }

        // --------------------------------------------------
        // SPRITE LAYER RENDERING
        // --------------------------------------------------

        static void RenderSpriteLayer(
            Entity *entity,
            ANM2 *sprite,
            AnimationState *animationState,
            AnimationLayer *animationLayer,
            LayerState *layerState,
            Room *room,
            float cameraRightX,
            float cameraRightZ)
        {
            if (!entity ||
                !sprite ||
                !animationState ||
                !animationLayer ||
                !layerState ||
                !room)
            {
                return;
            }

            if (!animationState->_layerFrames)
                return;

            if (!layerState->IsVisible())
                return;

            const int layerID =
                animationLayer->_layerID;

            if (layerID < 0 || layerID >= 64)
                return;

            const int frameIndex =
                animationState->_layerFrames[layerID];

            if (frameIndex < 0)
                return;

            AnimationFrame *frame =
                animationLayer->GetFrame(frameIndex);

            if (!frame || !frame->visible)
                return;

            if (frame->width <= 0.0f ||
                frame->height <= 0.0f)
            {
                return;
            }

            // Obtain the actual REPENTOGON spritesheet.
            KAGE_SmartPointer_ImageBase sheet =
                layerState->GetSpriteSheet();

            if (!sheet.image)
                return;

            SpriteTexture *texture =
                GetSpriteTexture(sheet.image);

            if (!texture || !texture->texture)
                return;

            // AnimationFrame crop coordinates refer to the
            // original spritesheet.
            const float cropX = frame->crop.x;
            const float cropY = frame->crop.y;

            const float cropWidth = frame->width;
            const float cropHeight = frame->height;

            if (cropX < 0.0f ||
                cropY < 0.0f ||
                cropX + cropWidth > texture->width ||
                cropY + cropHeight > texture->height)
            {
                return;
            }

            float u0 =
                cropX / static_cast<float>(texture->width);

            float u1 =
                (cropX + cropWidth) /
                static_cast<float>(texture->width);

            // GetTexelRegion uses image coordinates;
            // OpenGL texture coordinates have their origin
            // at the bottom-left.
            float v0 =
                1.0f -
                (cropY + cropHeight) /
                    static_cast<float>(texture->height);

            float v1 =
                1.0f -
                cropY /
                    static_cast<float>(texture->height);

            if (layerState->_flipX || sprite->_flipX)
                std::swap(u0, u1);

            if (layerState->_flipY || sprite->_flipY)
                std::swap(v0, v1);

            // Frame dimensions and offsets are in Isaac pixels.
            float width =
                cropWidth *
                std::fabs(frame->scale.x) /
                ISAAC_PIXELS_PER_TILE;

            float height =
                cropHeight *
                std::fabs(frame->scale.y) /
                ISAAC_PIXELS_PER_TILE;

            if (width <= 0.0f || height <= 0.0f)
                return;

            const Vector *entityPosition =
                entity->GetPosition();

            if (!entityPosition)
                return;

            const Vector worldPosition =
                IsaacPositionToWorld(
                    *entityPosition,
                    room);

            const float offsetX =
                (frame->pos.x + layerState->_pos.x) /
                ISAAC_PIXELS_PER_TILE;

            const float offsetZ =
                -(frame->pos.y + layerState->_pos.y) /
                ISAAC_PIXELS_PER_TILE;

            const float centerX =
                worldPosition.x +
                offsetX;

            const float centerZ =
                worldPosition.y +
                offsetZ;

            // Keep the sprite upright and face it toward
            // the camera horizontally.
            const float halfWidth = width * 0.5f;
            const float halfHeight = height * 0.5f;

            const float rightX =
                cameraRightX * halfWidth;

            const float rightZ =
                cameraRightZ * halfWidth;

            const float bottomY =
                ROOM_FLOOR_Y;

            const float topY =
                bottomY + height;

            const float leftX =
                centerX - rightX;

            const float leftZ =
                centerZ - rightZ;

            const float rightSideX =
                centerX + rightX;

            const float rightSideZ =
                centerZ + rightZ;

            glBindTexture(
                GL_TEXTURE_2D,
                texture->texture);

            glColor4f(
                1.0f,
                1.0f,
                1.0f,
                1.0f);

            glNormal3f(
                0.0f,
                0.0f,
                1.0f);

            glBegin(GL_QUADS);

            // Bottom-left
            glTexCoord2f(u0, v0);
            glVertex3f(
                leftX,
                bottomY,
                leftZ);

            // Bottom-right
            glTexCoord2f(u1, v0);
            glVertex3f(
                rightSideX,
                bottomY,
                rightSideZ);

            // Top-right
            glTexCoord2f(u1, v1);
            glVertex3f(
                rightSideX,
                topY,
                rightSideZ);

            // Top-left
            glTexCoord2f(u0, v1);
            glVertex3f(
                leftX,
                topY,
                leftZ);

            glEnd();
        }

        // --------------------------------------------------
        // ENTITY SPRITE RENDERING
        // --------------------------------------------------

        static void RenderEntitySprite(
            Entity *entity,
            Room *room,
            float cameraRightX,
            float cameraRightZ)
        {
            if (!entity || !room)
                return;

            if (!entity->_exists ||
                entity->_dead ||
                !entity->_visible)
            {
                return;
            }

            ANM2 *sprite =
                &entity->_sprite;

            if (!sprite->_loaded ||
                !sprite->_layerState ||
                sprite->_layerCount <= 0)
            {
                return;
            }

            AnimationState *animationState =
                sprite->GetAnimationState();

            if (!animationState ||
                !animationState->_animData)
            {
                return;
            }

            AnimationData *animationData =
                animationState->_animData;

            if (!animationData->_animLayers ||
                animationData->_layerCount <= 0)
            {
                return;
            }

            const int layerCount = std::min(
                animationData->_layerCount,
                static_cast<int>(sprite->_layerCount));

            for (int i = 0; i < layerCount; ++i)
            {
                AnimationLayer *animationLayer =
                    animationData->GetLayerByOrder(i);

                LayerState *layerState =
                    &sprite->_layerState[i];

                if (!animationLayer || !layerState)
                    continue;

                RenderSpriteLayer(
                    entity,
                    sprite,
                    animationState,
                    animationLayer,
                    layerState,
                    room,
                    cameraRightX,
                    cameraRightZ);
            }
        }

        // --------------------------------------------------
        // CAPSULE RENDERING
        // --------------------------------------------------

        static void RenderCapsuleCircle(
            float centerX,
            float centerZ,
            float radius)
        {
            glBegin(GL_LINE_LOOP);

            for (int i = 0; i < CAPSULE_SEGMENTS; ++i)
            {
                const float angle =
                    2.0f * PI *
                    static_cast<float>(i) /
                    static_cast<float>(CAPSULE_SEGMENTS);

                const float x =
                    centerX + std::cos(angle) * radius;

                const float z =
                    centerZ + std::sin(angle) * radius;

                glVertex3f(
                    x,
                    ROOM_FLOOR_Y + CAPSULE_HEIGHT_OFFSET,
                    z);
            }

            glEnd();
        }

        static void RenderCollisionCapsule(
            Entity *entity,
            Room *room)
        {
            if (!entity || !room)
                return;

            if (!entity->_exists ||
                entity->_dead ||
                !entity->_visible)
            {
                return;
            }

            Vector offset(0.0f, 0.0f);

            // GetCollisionCapsule returns a Capsule by value.
            Capsule capsule =
                entity->GetCollisionCapsule(&offset);

            // The REPENTOGON Capsule getters expose:
            // _vec2 = start point
            // _vec3 = end point
            // _unkFloat1 = size
            const Vector start =
                IsaacPositionToWorld(
                    capsule._vec2,
                    room);

            const Vector end =
                IsaacPositionToWorld(
                    capsule._vec3,
                    room);

            const float radius =
                std::fabs(capsule._unkFloat1) /
                ISAAC_PIXELS_PER_TILE;

            if (radius <= 0.001f)
                return;

            const float dx =
                end.x - start.x;

            const float dz =
                end.y - start.y;

            const float length =
                std::sqrt(dx * dx + dz * dz);

            glColor4f(
                0.1f,
                1.0f,
                0.2f,
                1.0f);

            glLineWidth(1.5f);

            // A capsule is two endpoint circles joined
            // by two parallel tangent lines.
            if (length <= 0.001f)
            {
                RenderCapsuleCircle(
                    start.x,
                    start.y,
                    radius);

                return;
            }

            const float normalX =
                -dz / length;

            const float normalZ =
                dx / length;

            const float offsetX =
                normalX * radius;

            const float offsetZ =
                normalZ * radius;

            const float y =
                ROOM_FLOOR_Y +
                CAPSULE_HEIGHT_OFFSET;

            glBegin(GL_LINES);

            // First tangent.
            glVertex3f(
                start.x + offsetX,
                y,
                start.y + offsetZ);

            glVertex3f(
                end.x + offsetX,
                y,
                end.y + offsetZ);

            // Second tangent.
            glVertex3f(
                start.x - offsetX,
                y,
                start.y - offsetZ);

            glVertex3f(
                end.x - offsetX,
                y,
                end.y - offsetZ);

            glEnd();

            RenderCapsuleCircle(
                start.x,
                start.y,
                radius);

            RenderCapsuleCircle(
                end.x,
                end.y,
                radius);
        }

        // --------------------------------------------------
        // RENDER STATE AND PROJECTION
        // --------------------------------------------------

        static bool BeginEntityRendering(
            GLint &oldProgram,
            GLint &oldMatrixMode,
            GLint &oldActiveTexture)
        {
            GLint viewport[4] = {};

            glGetIntegerv(
                GL_VIEWPORT,
                viewport);

            if (viewport[2] <= 0 ||
                viewport[3] <= 0)
            {
                return false;
            }

            GLint depthBits = 0;

            glGetIntegerv(
                GL_DEPTH_BITS,
                &depthBits);

            if (depthBits <= 0)
                return false;

            glGetIntegerv(
                GL_CURRENT_PROGRAM,
                &oldProgram);

            glGetIntegerv(
                GL_MATRIX_MODE,
                &oldMatrixMode);

            glGetIntegerv(
                GL_ACTIVE_TEXTURE,
                &oldActiveTexture);

            glPushAttrib(GL_ALL_ATTRIB_BITS);

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();

            glDisable(GL_CULL_FACE);
            glDisable(GL_LIGHTING);
            glDisable(GL_FOG);
            glDisable(GL_SCISSOR_TEST);
            glDisable(GL_STENCIL_TEST);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glDepthMask(GL_TRUE);

            glEnable(GL_BLEND);

            glBlendFunc(
                GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.01f);

            glEnable(GL_TEXTURE_2D);

            const double aspect =
                static_cast<double>(viewport[2]) /
                static_cast<double>(viewport[3]);

            const double nearPlane =
                g_Camera.nearPlane;

            const double farPlane =
                g_Camera.farPlane;

            const double halfFov =
                g_Camera.fieldOfView *
                PI / 360.0;

            const double halfHeight =
                nearPlane * std::tan(halfFov);

            const double halfWidth =
                halfHeight * aspect;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glFrustum(
                -halfWidth,
                halfWidth,
                -halfHeight,
                halfHeight,
                nearPlane,
                farPlane);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glRotatef(
                -g_Camera.pitch,
                1.0f,
                0.0f,
                0.0f);

            glRotatef(
                -g_Camera.yaw,
                0.0f,
                1.0f,
                0.0f);

            glTranslatef(
                -g_Camera.position.x,
                -g_Camera.position.y,
                -g_Camera.position.z);

            return true;
        }

        static void EndEntityRendering(
            GLint oldProgram,
            GLint oldMatrixMode,
            GLint oldActiveTexture)
        {
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();

            glPopAttrib();

            g_UseProgram(
                static_cast<GLuint>(oldProgram));

            if (g_ActiveTexture)
            {
                g_ActiveTexture(
                    static_cast<GLenum>(oldActiveTexture));
            }

            glMatrixMode(
                static_cast<GLenum>(oldMatrixMode));
        }
    }

    // ==================================================
    // PUBLIC ENTITY RENDERER
    // ==================================================

    void RenderEntities()
    {
        if (!g_Camera.enabled)
            return;

        if (!g_Game)
            return;

        Room *room =
            g_Game->GetCurrentRoom();

        if (!room)
            return;

        EntityList *entityList =
            room->GetEntityList();

        if (!entityList)
            return;

        EntityList_EL *renderList =
            entityList->GetRenderEL();

        if (!renderList ||
            !renderList->_data ||
            renderList->_size == 0)
        {
            return;
        }

        // OpenGL texture objects belong to a context.
        // Discard cached IDs if the context changes.
        const HGLRC currentContext =
            wglGetCurrentContext();

        if (!currentContext)
            return;

        if (currentContext != g_EntityTextureContext)
        {
            g_SpriteTextures.clear();

            g_EntityTextureContext =
                currentContext;
        }

        GLint oldProgram = 0;
        GLint oldMatrixMode = GL_MODELVIEW;
        GLint oldActiveTexture = GL_TEXTURE0;

        if (!BeginEntityRendering(
                oldProgram,
                oldMatrixMode,
                oldActiveTexture))
        {
            return;
        }

        const float yawRadians =
            g_Camera.yaw * PI / 180.0f;

        const float cameraRightX =
            std::cos(yawRadians);

        const float cameraRightZ =
            -std::sin(yawRadians);

        // --------------------------------------------------
        // SPRITES
        // --------------------------------------------------

        g_UseProgram(g_ShaderProgram);

        g_Uniform1i(
            g_UniformTexture,
            0);

        g_Uniform1i(
            g_UniformUseTexture,
            1);

        g_Uniform3f(
            g_UniformLightDirection,
            0.0f,
            0.0f,
            1.0f);

        g_Uniform1f(
            g_UniformAmbient,
            1.0f);

        g_Uniform1f(
            g_UniformDiffuse,
            0.0f);

        if (g_ActiveTexture)
            g_ActiveTexture(GL_TEXTURE0);

        for (unsigned int i = 0;
             i < renderList->_size;
             ++i)
        {
            Entity *entity =
                renderList->_data[i];

            if (!entity)
                continue;

            RenderEntitySprite(
                entity,
                room,
                cameraRightX,
                cameraRightZ);
        }

        // --------------------------------------------------
        // COLLISION CAPSULES
        // --------------------------------------------------

        // Use the fixed-function pipeline for the wireframes.
        g_UseProgram(0);

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        for (unsigned int i = 0;
             i < renderList->_size;
             ++i)
        {
            Entity *entity =
                renderList->_data[i];

            if (!entity)
                continue;

            RenderCollisionCapsule(
                entity,
                room);
        }

        EndEntityRendering(
            oldProgram,
            oldMatrixMode,
            oldActiveTexture);
    }
}