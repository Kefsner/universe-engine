#include "core/AssetManager.hpp"

#include "renderer/Texture.hpp"
#include "renderer/Shader.hpp"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>

namespace Universe
{
    Texture::Texture(const char* texturePath, int count)
        : m_Count(count)
    {
        spdlog::info("Constructor Texture");
        stbi_set_flip_vertically_on_load(true); 
        
        int width, height, nChannels;
        unsigned char* textureData = stbi_load(texturePath, &width, &height, &nChannels, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);

        glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureStorage2D(m_ID, 1, GL_RGBA8, width, height);
        glTextureSubImage2D(m_ID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

        stbi_image_free(textureData);

        m_Width = width;
        m_Height = height;
    }

    void Texture::Bind(GLuint shaderProgram)
    {
        std::string locationStr = "u_Textures[" + std::to_string(m_Count) + "]";
        GLint location = glGetUniformLocation(shaderProgram, locationStr.c_str());
        glProgramUniform1i(shaderProgram, location, m_Count);
        glBindTextureUnit(m_Count, m_ID);

        GLint textureIndexLocation = glGetUniformLocation(shaderProgram, "textureIndex");
        glProgramUniform1i(shaderProgram, textureIndexLocation, m_Count);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_ID);
    }
}