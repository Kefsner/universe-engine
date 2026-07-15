#pragma once

#include <glad/glad.h>

namespace Universe
{
    class Texture
    {
    public:
        Texture(const char* texturePath, int count);
        Texture(const Texture& other) = delete;
        ~Texture();

        void Bind(GLuint shaderProgram);
        GLuint GetTextureID() const { return m_ID; }

    private:
        GLuint m_ID;
        int m_Count;
    };
}
