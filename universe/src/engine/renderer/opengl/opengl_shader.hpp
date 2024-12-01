#pragma once
#include "engine/renderer/shader.hpp"
#include <glm/glm.hpp>
#include <glad/glad.h>


namespace Universe {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;

        void UploadUniformInt(const std::string& name, int value) const;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        uint32_t m_RendererID;

        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };
}