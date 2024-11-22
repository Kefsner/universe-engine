#pragma once
#include <string>
#include <cstdint>
#include "engine/core.hpp"

namespace Universe {

	class Shader
	{
	public:
		virtual ~Shader() = default;
        
        virtual void Bind() const = 0;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}