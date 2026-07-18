#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Universe
{
    class Shader
    {
    public:
        Shader();
        ~Shader() = default;

        void Bind();
        GLuint GetProgram() { return m_ShaderProgram; }

        void SetMat4Uniform(glm::mat4 matrix, const char* name);
        void SetVec2Uniform(glm::vec2 vector, const char* name);

    private:
        void CheckCompilationStatus(GLuint shader);
        void CheckLinkingStatus();

    private:
        GLuint m_ShaderProgram;
    };
}