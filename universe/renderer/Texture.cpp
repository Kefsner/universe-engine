#include "renderer/Texture.hpp"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Universe
{
    Texture::Texture(const char* texturePath)
    {
        stbi_set_flip_vertically_on_load(true); 
        
        int width, height, nChannels;
        unsigned char* textureData = stbi_load(texturePath, &width, &height, &nChannels, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);

        glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureStorage2D(m_ID, 1, GL_RGBA8, width, height);
        glTextureSubImage2D(m_ID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateTextureMipmap(m_ID);
        glBindTextureUnit(0, m_ID);

        stbi_image_free(textureData);
    }
}