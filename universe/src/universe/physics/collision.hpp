#pragma once

#include <glm/glm.hpp>

namespace Universe
{
    class Collision {
    public:
        static bool AABBvsAABB(const glm::vec2& aPos, const glm::vec2& aSize,
                               const glm::vec2& bPos, const glm::vec2& bSize);

        static bool AABBvsCircle(const glm::vec2& boxPos, const glm::vec2& boxSize,
                                 const glm::vec2& circleCenter, float radius);

        static bool CirclevsCircle(const glm::vec2& centerA, float radiusA,
                                   const glm::vec2& centerB, float radiusB);
    };

}
