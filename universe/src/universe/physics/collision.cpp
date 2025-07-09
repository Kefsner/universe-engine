#include "universe/physics/collision.hpp"
#include <glm/glm.hpp>

namespace Universe {

    bool Collision::AABBvsAABB(const glm::vec2& aPos, const glm::vec2& aSize,
                               const glm::vec2& bPos, const glm::vec2& bSize)
    {
        return (aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x &&
                aPos.y < bPos.y + bSize.y && aPos.y + aSize.y > bPos.y);
    }

    bool Collision::AABBvsCircle(const glm::vec2& boxPos, const glm::vec2& boxSize,
                                 const glm::vec2& circleCenter, float radius)
    {
        float closestX = glm::clamp(circleCenter.x, boxPos.x, boxPos.x + boxSize.x);
        float closestY = glm::clamp(circleCenter.y, boxPos.y, boxPos.y + boxSize.y);

        float distanceX = circleCenter.x - closestX;
        float distanceY = circleCenter.y - closestY;

        return (distanceX * distanceX + distanceY * distanceY) < (radius * radius);
    }

    bool Collision::CirclevsCircle(const glm::vec2& centerA, float radiusA,
                                   const glm::vec2& centerB, float radiusB)
    {
        float distSq = glm::dot(centerA - centerB, centerA - centerB);
        float radiusSum = radiusA + radiusB;
        return distSq < (radiusSum * radiusSum);
    }

}
