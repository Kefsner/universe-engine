#pragma once
#include "engine/renderer/shader.hpp"
#include <glm/glm.hpp>
#include <glad/glad.h>


namespace Universe {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;

        const std::string& GetName() const override { return m_Name; }

        void UploadUniformInt(const std::string& name, int value) const;
        void UploadUniformFloat(const std::string& name, float value) const;
        void UploadUniformFloat2(const std::string& name, const glm::vec2& values) const;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& values) const;
        void UploadUniformFloat4(const std::string& name, const glm::vec4& values) const;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        uint32_t m_RendererID;
        std::string m_Name;

        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };
}