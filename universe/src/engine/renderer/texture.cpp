#include "pch.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/opengl/opengl_texture.hpp"

namespace Universe {

    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(path);
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}