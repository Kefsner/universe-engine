#pragma once

#include <string>

#include "universe/renderer/texture.hpp"

namespace Universe {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        // Constructor and Destructor
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();

        // Virtual functions
        void Bind(uint32_t slot = 0) const override;

        // Getters
        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

    private:
        std::string m_Path;     // Path to the texture
        uint32_t m_Width;       // Width of the texture
        uint32_t m_Height;      // Height of the texture
        uint32_t m_RendererID;  // OpenGL texture ID
    };
}