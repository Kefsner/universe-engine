#pragma once

#include "spdlog/spdlog.h"

namespace Universe {

	class Logger
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define UE_CORE_TRACE(...)		::Universe::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define UE_CORE_INFO(...)		::Universe::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define UE_CORE_WARN(...)		::Universe::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define UE_CORE_ERROR(...)		::Universe::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define UE_CORE_CRITICAL(...)	::Universe::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define UE_TRACE(...)			::Universe::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define UE_INFO(...)			::Universe::Logger::GetClientLogger()->info(__VA_ARGS__)
#define UE_WARN(...)			::Universe::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define UE_ERROR(...)			::Universe::Logger::GetClientLogger()->error(__VA_ARGS__)
#define UE_CRITICAL(...)		::Universe::Logger::GetClientLogger()->critical(__VA_ARGS__)

// Assert Macro
#define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }