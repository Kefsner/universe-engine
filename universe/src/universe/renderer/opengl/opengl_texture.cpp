#include "pch.hpp"

#include <stb_image.h>
#include <glad/glad.h>

#include "universe/base/assert.hpp"
#include "universe/renderer/opengl/opengl_texture.hpp"

namespace Universe
{
    static GLenum ImageFormatToGLDataFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGBA8: return GL_RGBA;
        }

        UE_CORE_ASSERT(false, "Unknown ImageFormat!");
        return 0;
    }

    static GLenum ImageFormatToGLInternalFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGBA8: return GL_RGBA8;
        }

        UE_CORE_ASSERT(false, "Unknown ImageFormat!");
        return 0;
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(true);
        int32_t channels;
        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0); // 0 means do not force the number of channels
        UE_CORE_ASSERT(data, "Failed to load texture!");

        const GLuint numberOfTextures = 1;
        glCreateTextures(GL_TEXTURE_2D, numberOfTextures, &m_TextureID);
    
        GLuint levels = 1;
        if (channels == 4) {
            // 4 channels means RGBA
            m_InternalFormat = GL_RGBA8;  // <- GPU internal storage
            m_DataFormat     = GL_RGBA;   // <- CPU data layout
        } else {
            // 3 channels means RGB
            m_InternalFormat = GL_RGB8;   // <- GPU internal storage
            m_DataFormat     = GL_RGB;    // <- CPU data layout
        }

        // Allocate storage on the GPU
        glTextureStorage2D(m_TextureID, levels, m_InternalFormat, m_Width, m_Height);

        // Set the texture wrapping parameters
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set the texture filtering parameters
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        SetData(data, m_Width * m_Height * channels);
        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(TextureSpecification spec)
        : m_Width(spec.width), m_Height(spec.height)
    {
        const GLuint numberOfTextures = 1;
        glCreateTextures(GL_TEXTURE_2D, numberOfTextures, &m_TextureID);
    
        GLuint levels = 1;
        m_InternalFormat = ImageFormatToGLInternalFormat(spec.format);
        m_DataFormat = ImageFormatToGLDataFormat(spec.format);

        glTextureStorage2D(m_TextureID, levels, m_InternalFormat, m_Width, m_Height);

        // Set the texture wrapping parameters
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set the texture filtering parameters
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_TextureID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {        
        // Upload the actual pixel data
        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }
}