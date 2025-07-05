#pragma once

#include <entt.hpp>

#include "universe/base/base.hpp"

namespace Universe
{
    class Entity;

    class Scene
    {
    public:
        static Ref<Scene> Create()
        {
            return CreateRef<Scene>();
        }

        Scene() = default;
        ~Scene() = default;

        Entity CreateEntity(const std::string& name = "Unnamed");
        void DestroyEntity(Entity entity);

        entt::registry& GetRegistry() { return m_Registry; }
        const entt::registry& GetRegistry() const { return m_Registry; }

    private:
        entt::registry m_Registry;
    };
}