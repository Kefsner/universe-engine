#pragma once

#include <entt.hpp>

#include "universe/base/base.hpp"
#include "universe/base/assert.hpp"
#include "universe/scene/scene.hpp"

namespace Universe
{
    class Entity
    {
    public:
        Entity() : m_EntityHandle(entt::null), m_Scene(nullptr) {}
        Entity(entt::entity handle, Scene* scene)
            : m_EntityHandle(handle), m_Scene(scene) {}

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            UE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
            return m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent()
        {
            UE_CORE_ASSERT(HasComponent<T>(), "Missing component!");
            return m_Scene->GetRegistry().get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->GetRegistry().all_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            UE_CORE_ASSERT(HasComponent<T>(), "Missing component!");
            m_Scene->GetRegistry().remove<T>(m_EntityHandle);
        }

        entt::entity GetHandle() const { return m_EntityHandle; }

        operator bool() const { return m_EntityHandle != entt::null; }

    private:
        entt::entity m_EntityHandle;
        Scene* m_Scene;
    };
}
