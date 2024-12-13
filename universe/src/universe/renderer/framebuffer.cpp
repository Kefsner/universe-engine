#include "pch.hpp"

#include "universe/core/core.hpp"
#include "universe/core/assert.hpp"
#include "universe/renderer/framebuffer.hpp"
#include "universe/renderer/renderer.hpp"
#include "universe/renderer/opengl/opengl_framebuffer.hpp"


namespace Universe {

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLFramebuffer>(spec);
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}