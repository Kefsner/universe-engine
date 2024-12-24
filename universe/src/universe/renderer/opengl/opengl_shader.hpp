#pragma once

#include "universe/renderer/shader.hpp"

namespace Universe
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t m_ShaderID;
        const char* m_Name;
    };
}