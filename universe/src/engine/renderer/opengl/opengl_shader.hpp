#pragma once
#include "engine/renderer/shader.hpp"
#include <glm/glm.hpp>

namespace Universe {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        uint32_t m_RendererID;
    };
}