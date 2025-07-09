#pragma once

#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"
#include "universe/renderer/texture.hpp"
#include "universe/renderer/animation.hpp"
#include <string>

namespace Universe
{
    struct NameComponent
    {
        std::string name;

        NameComponent() = default;
        NameComponent(const std::string& name) : name(name) {}
    };

    struct TagComponent
    {
        std::string tag;

        TagComponent() = default;
        TagComponent(const std::string& tag) : tag(tag) {}
    };

    struct TransformComponent
    {
        glm::vec3 position = { 0.0f, 0.0f, 0.0f };

        TransformComponent() = default;
        TransformComponent(float x, float y, float z)
            : position{ x, y, z } {}
    };

    struct AnimatorComponent
    {
        std::unordered_map<std::string, Ref<Animation>> animations;
        std::string current;

        float timer = 0.0f;
        uint32_t currentFrame = 0;
        bool playing = false;

        void Update(Timestep ts)
        {
            if (!playing || animations.empty())
                return;
            
            auto anim = animations.find(current);
            if (anim == animations.end())
                return;

            timer += ts;

           while (timer >= anim->second->GetFrameDuration())
            {
                timer -= anim->second->GetFrameDuration();
                currentFrame++;

                if (currentFrame >= anim->second->GetTotalFrames())
                {
                    if (anim->second->IsLooping())
                        currentFrame = 0;
                    else {
                        currentFrame = anim->second->GetTotalFrames() - 1;
                        playing = false;
                    }
                }
            }
        }

        Ref<Animation> GetCurrentAnimation() const
        {
            auto it = animations.find(current);
            if (it != animations.end())
                return it->second;
            return nullptr;
        }

        uint32_t GetCurrentFrame() const
        {
            return currentFrame;
        }

        const std::string& GetCurrentName() const
        {
            return current;
        }

        void SetCurrentAnimation(const std::string& name)
        {
            auto it = animations.find(name);
            if (it == animations.end())
            {
                UE_CORE_ERROR("Animation '{0}' not found!", name);
                return;
            }

            if (current != name)
            {
                current = name;
                currentFrame = 0;
                timer = 0.0f;
                playing = true;
            }
        }

        void AddAnimation(const std::string& name, const Ref<Animation>& anim)
        {
            UE_CORE_ASSERT(!animations.contains(name), "Animation '{}' already exists", name);
            animations[name] = anim;
        }
    };

    struct AABBComponent
    {
        glm::vec2 size = { 1.0f, 1.0f };

        AABBComponent() = default;
        AABBComponent(const glm::vec2& sz)
            : size(sz) {}
    };

    struct SpriteRendererComponent
    {
        Ref<Texture2D> texture;
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const Ref<Texture2D>& tex, const glm::vec4& col = { 1.0f, 1.0f, 1.0f, 1.0f })
            : texture(tex), color(col) {}
    };
}