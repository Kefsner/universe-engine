#pragma once

#include "renderer/VertexBuffer.hpp"
#include "renderer/IndexBuffer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Universe
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec2 TexCoords;
    };

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void AttachBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer);

    private:
        GLuint m_ID;
        GLuint m_ID2;
    };
}