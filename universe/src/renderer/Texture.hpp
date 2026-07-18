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

        float GetWidth() const { return m_Width; }
        float GetHeight() const { return m_Height; }

    private:
        GLuint m_ID;
        int m_Count;
        float m_Width, m_Height;
    };
}
