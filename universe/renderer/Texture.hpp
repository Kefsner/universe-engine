#pragma once

#include <glad/glad.h>

namespace Universe
{
    class Texture
    {
    public:
        Texture(const char* texturePath);
        ~Texture() = default;

    private:
        GLuint m_ID;
    };
}
