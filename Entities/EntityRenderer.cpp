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

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#ifndef GL_QUADS
#define GL_QUADS 0x0007
#endif

namespace ViewPoint
{
    namespace
    {
        constexpr float PI = 3.14159265358979323846f;
        constexpr float PIXELS_PER_TILE = 40.0f;
        constexpr float FLOOR_Y = -1.5f;
        constexpr float COLLISION_Y_OFFSET = 0.035f;
        constexpr int CAPSULE_SEGMENTS = 24;

        struct SpriteTexture
        {
            GLuint id = 0;
            int width = 0;
            int height = 0;
        };

        std::unordered_map<KAGE_Graphics_ImageBase *, SpriteTexture>
            g_SpriteTextures;

        HGLRC g_TextureContext = nullptr;

        struct WorldPoint
        {
            float x;
            float y;
            float z;
        };

        struct SpriteVertex
        {
            float x;
            float y;
            float z;
            float u;
            float v;
        };

        // ------------------------------------------------------------
        // ISAAC POSITION TO VIEWPOINT WORLD POSITION
        // ------------------------------------------------------------

        static WorldPoint IsaacToWorld(
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

            WorldPoint result{};

            result.x =
                (position.x - roomCenterX) /
                PIXELS_PER_TILE;

            result.y = FLOOR_Y;

            result.z =
                (roomCenterY - position.y) /
                PIXELS_PER_TILE;

            return result;
        }

        static float GetEntityRenderHeightOffset(
            Entity *entity)
        {
            if (!entity)
                return 0.0f;

            float offset = entity->_depthOffset;

            if (entity->_type == ENTITY_TEAR)
            {
                Entity_Tear *tear =
                    static_cast<Entity_Tear *>(entity);

                const float tearHeight =
                    tear->_height;

                const float tearRenderHeight =
                    tear->GetRenderHeight();

                if (tearHeight > 0.0f)
                    offset = tearHeight;
                else if (tearRenderHeight > 0.0f)
                    offset = tearRenderHeight;
            }

            return offset / PIXELS_PER_TILE;
        }

        // ------------------------------------------------------------
        // SPRITESHEET TEXTURE CACHE
        // ------------------------------------------------------------

        static SpriteTexture *GetSpriteTexture(
            KAGE_Graphics_ImageBase *image)
        {
            if (!image)
                return nullptr;

            auto found = g_SpriteTextures.find(image);

            if (found != g_SpriteTextures.end())
                return &found->second;

            const int width =
                static_cast<int>(image->GetWidth());

            const int height =
                static_cast<int>(image->GetHeight());

            if (width <= 0 || height <= 0)
                return nullptr;

            const size_t pixelCount =
                static_cast<size_t>(width) *
                static_cast<size_t>(height);

            if (pixelCount > 64u * 1024u * 1024u)
                return nullptr;

            std::vector<unsigned char> pixels(pixelCount * 4u);

            image->GetTexelRegion(
                0,
                0,
                static_cast<unsigned int>(width),
                static_cast<unsigned int>(height),
                pixels.data());

            // Do not let an old OpenGL error invalidate this upload.
            while (glGetError() != GL_NO_ERROR)
            {
            }

            SpriteTexture texture{};
            texture.width = width;
            texture.height = height;

            glGenTextures(1, &texture.id);

            if (!texture.id)
                return nullptr;

            glBindTexture(GL_TEXTURE_2D, texture.id);

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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
                glDeleteTextures(1, &texture.id);
                return nullptr;
            }

            auto inserted =
                g_SpriteTextures.emplace(image, texture);

            return &inserted.first->second;
        }

        // ------------------------------------------------------------
        // SPRITE COLOR
        // ------------------------------------------------------------

        static void GetSpriteColor(
            const ANM2 *sprite,
            const LayerState *layer,
            const AnimationFrame *frame,
            float &red,
            float &green,
            float &blue,
            float &alpha)
        {
            red = 1.0f;
            green = 1.0f;
            blue = 1.0f;
            alpha = 1.0f;

            if (sprite)
            {
                red *= sprite->_color._tint[0];
                green *= sprite->_color._tint[1];
                blue *= sprite->_color._tint[2];
                alpha *= sprite->_color._tint[3];
            }

            if (layer)
            {
                red *= layer->_color._tint[0];
                green *= layer->_color._tint[1];
                blue *= layer->_color._tint[2];
                alpha *= layer->_color._tint[3];
            }

            if (frame)
            {
                red *= frame->color._tint[0];
                green *= frame->color._tint[1];
                blue *= frame->color._tint[2];
                alpha *= frame->color._tint[3];
            }

            red = std::max(0.0f, std::min(1.0f, red));
            green = std::max(0.0f, std::min(1.0f, green));
            blue = std::max(0.0f, std::min(1.0f, blue));
            alpha = std::max(0.0f, std::min(1.0f, alpha));
        }

        // ------------------------------------------------------------
        // SPRITE QUAD GENERATION
        // ------------------------------------------------------------

        static void RotateSpritePoint(
            float &x,
            float &y,
            float radians)
        {
            if (std::fabs(radians) < 0.0001f)
                return;

            const float cosine = std::cos(radians);
            const float sine = std::sin(radians);

            const float oldX = x;
            const float oldY = y;

            x = oldX * cosine - oldY * sine;
            y = oldX * sine + oldY * cosine;
        }

        static bool BuildSpriteQuad(
            Entity *entity,
            Room *room,
            ANM2 *sprite,
            LayerState *layer,
            AnimationFrame *frame,
            SpriteTexture *texture,
            float cameraRightX,
            float cameraRightZ,
            SpriteVertex (&vertices)[4])
        {
            if (!entity || !room || !sprite ||
                !layer || !frame || !texture)
            {
                return false;
            }

            if (frame->width <= 0.0f ||
                frame->height <= 0.0f)
            {
                return false;
            }

            const Vector *entityPosition =
                entity->GetPosition();

            if (!entityPosition)
                return false;

            const WorldPoint base =
                IsaacToWorld(*entityPosition, room);

            const float entityHeightOffset =
                GetEntityRenderHeightOffset(entity);

            // Atlas rectangle.
            const float cropX = frame->crop.x;
            const float cropY = frame->crop.y;
            const float cropWidth = frame->width;
            const float cropHeight = frame->height;

            if (cropX < 0.0f ||
                cropY < 0.0f ||
                cropX + cropWidth > texture->width ||
                cropY + cropHeight > texture->height)
            {
                return false;
            }

            // GetTexelRegion returns image pixels in top-to-bottom order.
            // OpenGL places the first uploaded row at the bottom of the texture.
            float u0 = cropX / static_cast<float>(texture->width);
            float u1 = (cropX + cropWidth) /
                       static_cast<float>(texture->width);

            float v0 = cropY / static_cast<float>(texture->height);
            float v1 = (cropY + cropHeight) /
                       static_cast<float>(texture->height);

            if (layer->_flipX != sprite->_flipX)
                std::swap(u0, u1);

            if (layer->_flipY != sprite->_flipY)
                std::swap(v0, v1);

            // Combine the frame, ANM2 and layer scales.
            const float scaleX =
                frame->scale.x * sprite->_scale.x;

            const float scaleY =
                frame->scale.y * sprite->_scale.y;

            const float width =
                cropWidth * std::fabs(scaleX);

            const float height =
                cropHeight * std::fabs(scaleY);

            if (width <= 0.001f || height <= 0.001f)
                return false;

            // The frame pivot is the local origin.
            // Positive local Y points down in Isaac's 2D space.
            const float left =
                frame->pos.x +
                layer->_pos.x +
                sprite->_offset.x -
                frame->pivot.x;

            const float top =
                frame->pos.y +
                layer->_pos.y +
                sprite->_offset.y -
                frame->pivot.y;

            // Apply the sprite's local rotation.
            const float rotation =
                (frame->rotation +
                 layer->_rotation +
                 sprite->_rotation) *
                PI / 180.0f;

            float localX[4] =
                {
                    left,
                    left + width,
                    left + width,
                    left};

            float localY[4] =
                {
                    top,
                    top,
                    top + height,
                    top + height};

            for (int i = 0; i < 4; ++i)
            {
                RotateSpritePoint(
                    localX[i],
                    localY[i],
                    rotation);
            }

            const float u[4] = {u0, u1, u1, u0};
            const float v[4] = {v0, v0, v1, v1};

            for (int i = 0; i < 4; ++i)
            {
                const float horizontal =
                    localX[i] / PIXELS_PER_TILE;

                const float vertical =
                    localY[i] / PIXELS_PER_TILE;

                vertices[i].x =
                    base.x +
                    cameraRightX * horizontal;

                vertices[i].y =
                    base.y + entityHeightOffset - vertical;

                vertices[i].z =
                    base.z +
                    cameraRightZ * horizontal;

                vertices[i].u = u[i];
                vertices[i].v = v[i];
            }

            // A negative scale mirrors the geometry as well as
            // the atlas coordinates.
            if (scaleX < 0.0f)
            {
                std::swap(vertices[0], vertices[1]);
                std::swap(vertices[3], vertices[2]);
            }

            if (scaleY < 0.0f)
            {
                std::swap(vertices[0], vertices[3]);
                std::swap(vertices[1], vertices[2]);
            }

            return true;
        }

        // ------------------------------------------------------------
        // ONE ANIMATION LAYER
        // ------------------------------------------------------------


static void RenderSpriteLayer(
    Entity* entity,
    Room* room,
    ANM2* sprite,
    AnimationState* animationState,
    AnimationLayer* animationLayer,
    float cameraRightX,
    float cameraRightZ)
{
    if (!entity || !room || !sprite ||
        !animationState || !animationLayer)
        return;

    if (!animationState->_layerFrames ||
        !animationState->_animData)
        return;

    const int layerID = animationLayer->_layerID;

    if (layerID < 0 || layerID >= 64)
        return;

    // Animation frame storage is indexed by layer ID,
    // not by animation draw order.
    const int frameIndex =
        animationState->_layerFrames[layerID];

    if (frameIndex < 0)
        return;

    AnimationFrame* frame =
        animationLayer->GetFrame(frameIndex);

    if (!frame)
        return;

    if (!animationLayer->IsVisible() ||
        !frame->visible)
        return;

    // Get the corresponding ANM2 layer state.
    LayerState* layer =
        sprite->GetLayer(layerID);

    if (!layer || !layer->_visible)
        return;

    if (!layer->_spriteSheetLoaded)
        return;

    KAGE_SmartPointer_ImageBase sheet =
        layer->GetSpriteSheet();

    if (!sheet.image)
        return;

    SpriteTexture* texture =
        GetSpriteTexture(sheet.image);

    if (!texture || !texture->id)
        return;

    SpriteVertex vertices[4]{};

    if (!BuildSpriteQuad(
            entity,
            room,
            sprite,
            layer,
            frame,
            texture,
            cameraRightX,
            cameraRightZ,
            vertices))
        return;

    float red;
    float green;
    float blue;
    float alpha;

    GetSpriteColor(
        sprite,
        layer,
        frame,
        red,
        green,
        blue,
        alpha);

    if (alpha <= 0.001f)
        return;

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glColor4f(red, green, blue, alpha);

    glBegin(GL_QUADS);

    for (int i = 0; i < 4; ++i)
    {
        glTexCoord2f(vertices[i].u, vertices[i].v);
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }

    glEnd();
}

        // ------------------------------------------------------------
        // ENTITY SPRITE
        // ------------------------------------------------------------

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

            ANM2 *sprite = &entity->_sprite;

            if (!sprite->_loaded ||
                !sprite->_layerState ||
                sprite->_layerCount == 0)
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

            // AnimationData's order is the draw order.
            // The ANM2 layer state is retrieved separately by ID.
            for (int i = 0; i < animationData->_layerCount; ++i)
            {
                AnimationLayer* animationLayer =
                    animationData->GetLayerByOrder(i);

                if (!animationLayer)
                    continue;

                RenderSpriteLayer(
                    entity,
                    room,
                    sprite,
                    animationState,
                    animationLayer,
                    cameraRightX,
                    cameraRightZ);
            }
        }

        // ------------------------------------------------------------
        // COLLISION CAPSULE
        // ------------------------------------------------------------

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

                glVertex3f(
                    centerX + std::cos(angle) * radius,
                    FLOOR_Y + COLLISION_Y_OFFSET,
                    centerZ + std::sin(angle) * radius);
            }

            glEnd();
        }

        static void RenderCollisionCapsule(
            Entity *entity,
            Room *room)
        {
            if (!entity || !room)
                return;

            if (!entity->_exists || entity->_dead)
                return;

            Vector offset(0.0f, 0.0f);

            const Capsule capsule =
                entity->GetCollisionCapsule(&offset);

            const WorldPoint start =
                IsaacToWorld(capsule._vec2, room);

            const WorldPoint end =
                IsaacToWorld(capsule._vec3, room);

            const float radius =
                std::fabs(capsule._unkFloat1) /
                PIXELS_PER_TILE;

            if (radius <= 0.001f)
                return;

            const float dx = end.x - start.x;
            const float dz = end.z - start.z;

            const float length =
                std::sqrt(dx * dx + dz * dz);

            glColor4f(
                0.1f,
                1.0f,
                0.2f,
                1.0f);

            glLineWidth(1.5f);

            if (length <= 0.001f)
            {
                RenderCapsuleCircle(
                    start.x,
                    start.z,
                    radius);

                return;
            }

            const float normalX = -dz / length;
            const float normalZ = dx / length;

            const float offsetX = normalX * radius;
            const float offsetZ = normalZ * radius;

            const float y =
                FLOOR_Y + COLLISION_Y_OFFSET;

            glBegin(GL_LINES);

            glVertex3f(
                start.x + offsetX,
                y,
                start.z + offsetZ);

            glVertex3f(
                end.x + offsetX,
                y,
                end.z + offsetZ);

            glVertex3f(
                start.x - offsetX,
                y,
                start.z - offsetZ);

            glVertex3f(
                end.x - offsetX,
                y,
                end.z - offsetZ);

            glEnd();

            RenderCapsuleCircle(
                start.x,
                start.z,
                radius);

            RenderCapsuleCircle(
                end.x,
                end.z,
                radius);
        }

        // ------------------------------------------------------------
        // RENDER STATE
        // ------------------------------------------------------------

        struct RenderState
        {
            GLint program = 0;
            GLint matrixMode = GL_MODELVIEW;
            GLint activeTexture = GL_TEXTURE0;
            bool matricesPushed = false;
            bool attributesPushed = false;
        };

        static bool BeginEntityRendering(RenderState &state)
        {
            GLint viewport[4] = {};

            glGetIntegerv(GL_VIEWPORT, viewport);

            if (viewport[2] <= 0 || viewport[3] <= 0)
                return false;

            GLint depthBits = 0;

            glGetIntegerv(GL_DEPTH_BITS, &depthBits);

            if (depthBits <= 0)
                return false;

            glGetIntegerv(
                GL_CURRENT_PROGRAM,
                &state.program);

            glGetIntegerv(
                GL_MATRIX_MODE,
                &state.matrixMode);

            glGetIntegerv(
                GL_ACTIVE_TEXTURE,
                &state.activeTexture);

            glPushAttrib(GL_ALL_ATTRIB_BITS);
            state.attributesPushed = true;

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();

            state.matricesPushed = true;

            // The entity renderer uses the compatibility pipeline.
            if (g_UseProgram)
                g_UseProgram(0);

            if (g_ActiveTexture)
                g_ActiveTexture(GL_TEXTURE0);

            glDisable(GL_CULL_FACE);
            glDisable(GL_LIGHTING);
            glDisable(GL_FOG);
            glDisable(GL_SCISSOR_TEST);
            glDisable(GL_STENCIL_TEST);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glDepthMask(GL_TRUE);

            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);

            glBlendFunc(
                GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA);

            glDisable(GL_ALPHA_TEST);

            glEnable(GL_TEXTURE_2D);

            const double aspect =
                static_cast<double>(viewport[2]) /
                static_cast<double>(viewport[3]);

            const double nearPlane =
                g_Camera.nearPlane;

            const double farPlane =
                g_Camera.farPlane;

            const double halfFov =
                static_cast<double>(g_Camera.fieldOfView) *
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

        static void EndEntityRendering(const RenderState &state)
        {
            if (state.matricesPushed)
            {
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();

                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
            }

            if (state.attributesPushed)
                glPopAttrib();

            if (g_UseProgram)
            {
                g_UseProgram(
                    static_cast<GLuint>(state.program));
            }

            if (g_ActiveTexture)
            {
                g_ActiveTexture(
                    static_cast<GLenum>(state.activeTexture));
            }

            glMatrixMode(
                static_cast<GLenum>(state.matrixMode));
        }
    }

    // ================================================================
    // PUBLIC ENTRY POINT
    // ================================================================

    void RenderEntities()
    {
        if (!g_Camera.enabled || !g_Game)
            return;

        Room *room = g_Game->GetCurrentRoom();

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

        const HGLRC currentContext =
            wglGetCurrentContext();

        if (!currentContext)
            return;

        if (currentContext != g_TextureContext)
        {
            // Texture IDs from a previous context cannot be reused.
            g_SpriteTextures.clear();
            g_TextureContext = currentContext;
        }

        RenderState state{};

        if (!BeginEntityRendering(state))
            return;

        const float yawRadians =
            g_Camera.yaw * PI / 180.0f;

        const float cameraRightX =
            std::cos(yawRadians);

        const float cameraRightZ =
            -std::sin(yawRadians);

        // ------------------------------------------------------------
        // ENTITY SPRITES
        // ------------------------------------------------------------

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        std::vector<Entity *> orderedEntities;
        orderedEntities.reserve(renderList->_size);

        for (unsigned int i = 0;
             i < renderList->_size;
             ++i)
        {
            Entity *entity = renderList->_data[i];

            if (!entity ||
                !entity->_exists ||
                entity->_dead ||
                !entity->_visible)
            {
                continue;
            }

            const Vector *entityPosition = entity->GetPosition();

            if (!entityPosition)
                continue;

            orderedEntities.push_back(entity);
        }

        std::sort(
            orderedEntities.begin(),
            orderedEntities.end(),
            [room](Entity *left, Entity *right)
            {
                const Vector *leftPos = left ? left->GetPosition() : nullptr;
                const Vector *rightPos = right ? right->GetPosition() : nullptr;

                if (!leftPos && !rightPos)
                    return false;
                if (!leftPos)
                    return false;
                if (!rightPos)
                    return true;

                const WorldPoint leftWorld = IsaacToWorld(*leftPos, room);
                const WorldPoint rightWorld = IsaacToWorld(*rightPos, room);

                const float leftDx = leftWorld.x - g_Camera.position.x;
                const float leftDz = leftWorld.z - g_Camera.position.z;
                const float leftDy = (leftWorld.y + GetEntityRenderHeightOffset(left)) - g_Camera.position.y;

                const float rightDx = rightWorld.x - g_Camera.position.x;
                const float rightDz = rightWorld.z - g_Camera.position.z;
                const float rightDy = (rightWorld.y + GetEntityRenderHeightOffset(right)) - g_Camera.position.y;

                const float leftDistance =
                    leftDx * leftDx + leftDy * leftDy + leftDz * leftDz;
                const float rightDistance =
                    rightDx * rightDx + rightDy * rightDy + rightDz * rightDz;

                return leftDistance > rightDistance;
            });

        for (Entity *entity : orderedEntities)
        {
            RenderEntitySprite(
                entity,
                room,
                cameraRightX,
                cameraRightZ);
        }

        glDepthMask(GL_TRUE);

        // ------------------------------------------------------------
        // COLLISION OUTLINES
        // ------------------------------------------------------------

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        if (g_UseProgram)
            g_UseProgram(0);

        for (unsigned int i = 0;
             i < renderList->_size;
             ++i)
        {
            Entity *entity = renderList->_data[i];

            if (!entity)
                continue;

            RenderCollisionCapsule(
                entity,
                room);
        }

        EndEntityRendering(state);
    }
}