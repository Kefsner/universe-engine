#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "universe/renderer/shader.hpp"


namespace Universe {

    class OpenGLShader : public Shader
    {
    public:
        // Constructor and Destructor
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        // virtual functions
        void Bind() const override;
        const std::string& GetName() const override { return m_Name; }
        void SetInt(const std::string& name, int value) override;
        void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        void SetFloat(const std::string& name, float value) override;
        void SetFloat2(const std::string& name, const glm::vec2& values) override;
        void SetFloat3(const std::string& name, const glm::vec3& values) override;
        void SetFloat4(const std::string& name, const glm::vec4& values) override;
        void SetMat4(const std::string& name, const glm::mat4& value) override;

    private:
        uint32_t m_RendererID;
        std::string m_Name;

        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };
}