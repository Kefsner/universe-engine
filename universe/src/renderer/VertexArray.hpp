#pragma once

#include "renderer/VertexBuffer.hpp"
#include "renderer/IndexBuffer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Universe
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void AttachBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer);
        void SetAttributes();

    private:
        GLuint m_ID;
    };
}