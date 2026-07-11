#pragma once

#include <glad/glad.h>

namespace Universe
{
    class Shader
    {
    public:
        Shader();
        ~Shader() = default;

    private:
        void CheckCompilationStatus(GLuint shader);
        void CheckLinkingStatus();

    private:
        GLuint m_ShaderProgram;
    };
}