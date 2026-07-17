#pragma once

#include <glad/glad.h>

namespace Universe
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        GLuint GetID() const { return m_ID; }

        void SetData(const unsigned int* indices, int count);

    private:
        GLuint m_ID;
    };
}