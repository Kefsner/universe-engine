#pragma once

#include "renderer/Renderer.hpp"
#include "renderer/VoxelRenderer3D.hpp"

#include <glad/glad.h>

#include <spdlog/spdlog.h>


namespace Universe
{
    void Renderer::Init()
    {
        VoxelRenderer3D::Init();

        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}