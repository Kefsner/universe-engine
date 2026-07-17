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

        void SetData(const float* vertices, int count);
        GLsizei GetStride() const;

    private:
        GLuint m_ID;
    };
}