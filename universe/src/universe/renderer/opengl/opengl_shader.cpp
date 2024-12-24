#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_shader.hpp"

namespace Universe
{
    OpenGLShader::OpenGLShader(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        const char* vertexSrcCStr = vertexSrc.c_str();
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrcCStr, nullptr);
        glCompileShader(vertexShader);

        const char* fragmentSrcCStr = fragmentSrc.c_str();
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrcCStr, nullptr);
        glCompileShader(fragmentShader);

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShader);
        glAttachShader(m_ShaderID, fragmentShader);
        glLinkProgram(m_ShaderID);

        // We can add a code snippet here to check if the shaders compiled and linked successfully

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(m_ShaderID);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
}