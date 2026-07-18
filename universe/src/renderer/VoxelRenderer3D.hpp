#pragma once

#include "renderer/Texture.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Universe
{
    class VoxelRenderer3D
    {
    public:
        static void Init();

        static void DrawCube(glm::vec3 position, std::shared_ptr<Texture> texture, glm::vec2 texCoord);
    };
}