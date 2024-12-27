#include "pch.hpp"

#include "universe/renderer/texture.hpp"
#include "universe/renderer/opengl/opengl_texture.hpp"

namespace Universe
{
    Ref<Texture2D> Texture2D::Create(std::string path)
    {
        return CreateRef<OpenGLTexture2D>(path);
    }

    Ref<Texture2D> Texture2D::Create(TextureSpecification spec)
    {
        return CreateRef<OpenGLTexture2D>(spec);
    }
}