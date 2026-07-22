#pragma once

#include "renderer/TextureAtlas.hpp"
#include "renderer/Camera.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Universe
{
    class VoxelRenderer3D
    {
    public:
        static void Init();

        static void DrawCube(glm::vec3 position, std::shared_ptr<TextureAtlas> atlas, int cellID);

        static void BeginScene(Camera& camera);
    };
}