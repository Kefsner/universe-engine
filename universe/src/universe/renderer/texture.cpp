#include "pch.hpp"

#include "universe/renderer/renderer.hpp"
#include "universe/renderer/texture.hpp"
#include "universe/renderer/opengl/opengl_texture.hpp"

namespace Universe {

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(width, height);
        }
        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);
        }
        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}