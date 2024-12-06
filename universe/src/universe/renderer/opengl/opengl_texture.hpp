#pragma once

#include <string>
#include <glad/glad.h>

#include "universe/renderer/texture.hpp"

namespace Universe {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        // Constructor and Destructor
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();

        // Virtual functions
        void SetData(void* data, uint32_t size) override;
        void Bind(uint32_t slot = 0) const override;

        // Getters
        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

    private:
        std::string m_Path;         // Path to the texture
        uint32_t m_Width;           // Width of the texture
        uint32_t m_Height;          // Height of the texture
        uint32_t m_RendererID;      // OpenGL texture ID
        GLenum m_InternalFormat;    // Internal format of the texture
        GLenum m_DataFormat;        // Data format of the texture
    };
}