#pragma once

#include <glad/glad.h>

namespace Universe
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        GLuint GetID() { return m_ID; }

    private:
        GLuint m_ID;
    };
}