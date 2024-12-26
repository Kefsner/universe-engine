#pragma once

#include <glm/glm.hpp>

#include "universe/base/base.hpp"
#include "universe/base/assert.hpp"

namespace Universe
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Bool
    };

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetUniformInt(const char* name, int value) = 0;
        virtual void SetUniformFloat4(const char* name, const glm::vec4& vector) = 0;
        virtual void SetUniformMat4(const char* name, const glm::mat4& matrix) = 0;

        static Ref<Shader> Create(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}