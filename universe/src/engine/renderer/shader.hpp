#pragma once
#include <string>
#include <cstdint>

namespace Universe {

	class Shader
	{
	public:
		virtual ~Shader() = default;
        
        virtual void Bind() const = 0;

        static std::unique_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}