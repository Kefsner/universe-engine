#include "pch.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/opengl/opengl_shader.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

    std::unique_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::OpenGL:
                return std::make_unique<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}