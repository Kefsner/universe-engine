#pragma once

#include "universe/renderer/texture.hpp"

namespace Universe
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();

        virtual int32_t GetWidth() const override { return m_Width; }
        virtual int32_t GetHeight() const override { return m_Height; }

        virtual void Bind(uint32_t slot = 0) const override;

    private:
        uint32_t m_TextureID;
        int32_t m_Width, m_Height;
    };
}