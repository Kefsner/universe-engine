#pragma once
#include <string>
#include "engine/core.hpp"

namespace Universe {

	class Shader
	{
	public:
		virtual ~Shader() = default;
        
        virtual void Bind() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}