#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <glad/glad.h>

namespace Universe
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void AttachBuffers(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);

    private:
        GLuint m_ID;
    };
}