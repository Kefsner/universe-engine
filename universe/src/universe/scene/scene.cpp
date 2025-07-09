#include "universe/scene/entity.hpp"
#include "universe/scene/scene.hpp"
#include "universe/scene/components.hpp"

namespace Universe
{
    Entity Scene::CreateEntity(const std::string& name, const glm::vec3& position)
    {
        Entity entity = Entity(m_Registry.create(), this);
        entity.AddComponent<NameComponent>(name);
        entity.AddComponent<TransformComponent>(position.x, position.y, position.z);
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity.GetHandle());
    }
}