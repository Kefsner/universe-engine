#pragma once

#include <glad/glad.h>

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

        static void CheckShaderCompilation(GLuint shader, const std::string& type);
        static void CheckProgramLinking(GLuint program);

    private:
        uint32_t m_ShaderID;
        const char* m_Name;
    };
}