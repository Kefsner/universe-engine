#include "pch.hpp"

#include "universe/renderer/shader.hpp"
#include "universe/renderer/opengl/opengl_shader.hpp"

namespace Universe
{
    Ref<Shader> Shader::Create(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

    Ref<Shader> Shader::Create(const char* filepath)
    {
        return CreateRef<OpenGLShader>(filepath);
    }
}