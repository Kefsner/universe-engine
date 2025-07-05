#include "universe/scene/entity.hpp"
#include "universe/scene/scene.hpp"
#include "universe/scene/components.hpp"

namespace Universe
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = Entity(m_Registry.create(), this);
        entity.AddComponent<NameComponent>(name);
        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity.GetHandle());
    }
}