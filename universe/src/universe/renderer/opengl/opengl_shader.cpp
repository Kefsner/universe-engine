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
        CheckShaderCompilation(vertexShader, "VERTEX");

        const char* fragmentSrcCStr = fragmentSrc.c_str();
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrcCStr, nullptr);
        glCompileShader(fragmentShader);
        CheckShaderCompilation(fragmentShader, "FRAGMENT");

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShader);
        glAttachShader(m_ShaderID, fragmentShader);
        glLinkProgram(m_ShaderID);
        CheckProgramLinking(m_ShaderID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        UE_CORE_TRACE("Deleting shader: {0}", m_Name);
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

    void OpenGLShader::CheckShaderCompilation(GLuint shader, const std::string& type)
    {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            UE_CORE_ERROR("Shader compilation error: {0} shader\n{1}", type, infoLog);
        }
        UE_CORE_TRACE("Shader compilation successful: {0} shader", type);
    }

    void OpenGLShader::CheckProgramLinking(GLuint program)
    {
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            UE_CORE_ERROR("Program linking error: {0}", infoLog);
        }
        UE_CORE_TRACE("Program linking successful");
    }
}