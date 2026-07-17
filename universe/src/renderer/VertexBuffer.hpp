#pragma once

#include <glad/glad.h>

namespace Universe
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        GLuint GetID() const { return m_ID; }

    private:
        GLuint m_ID;
    };
}