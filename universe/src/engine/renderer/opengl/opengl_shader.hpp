#pragma once
#include "engine/renderer/shader.hpp"

namespace Universe {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;

    private:
        uint32_t m_RendererID;
    };
}