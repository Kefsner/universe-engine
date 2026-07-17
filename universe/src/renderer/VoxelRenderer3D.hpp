#pragma once

#include <glm/glm.hpp>

namespace Universe
{
    class VoxelRenderer3D
    {
    public:
        static void Init();

        static void DrawBlock(glm::vec3 position);
    };
}