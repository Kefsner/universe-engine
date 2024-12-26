#include "pch.hpp"

#include <stb_image.h>
#include <glad/glad.h>

#include "universe/base/assert.hpp"
#include "universe/renderer/opengl/opengl_texture.hpp"

namespace Universe
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(true);
        int32_t channels;
        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0); // 0 means do not force the number of channels
        UE_CORE_ASSERT(data, "Failed to load texture!");

        const GLuint numberOfTextures = 1;
        glCreateTextures(GL_TEXTURE_2D, numberOfTextures, &m_TextureID);
    
        GLuint levels = 1;
        GLuint format = (channels == 4) ? GL_RGBA8 : GL_RGB8;
        GLuint internalFormat = (channels == 4) ? GL_RGBA : GL_RGB;

        glTextureStorage2D(m_TextureID, levels, format, m_Width, m_Height);
        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, internalFormat, GL_UNSIGNED_BYTE, data);

        // Set the texture wrapping parameters
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set the texture filtering parameters
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_TextureID);
    }
}