#pragma once

#include "spdlog/spdlog.h"

namespace Universe {

	class Log
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

#ifdef UE_ENABLE_LOGGING
	// Core log macros
	#define UE_CORE_TRACE(...)		::Universe::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define UE_CORE_INFO(...)		::Universe::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define UE_CORE_WARN(...)		::Universe::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define UE_CORE_ERROR(...)		::Universe::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define UE_CORE_CRITICAL(...)	::Universe::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define UE_TRACE(...)			::Universe::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define UE_INFO(...)			::Universe::Log::GetClientLogger()->info(__VA_ARGS__)
	#define UE_WARN(...)			::Universe::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define UE_ERROR(...)			::Universe::Log::GetClientLogger()->error(__VA_ARGS__)
	#define UE_CRITICAL(...)		::Universe::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	// Core log macros
	#define UE_CORE_TRACE(...)
	#define UE_CORE_INFO(...)
	#define UE_CORE_WARN(...)
	#define UE_CORE_ERROR(...)
	#define UE_CORE_CRITICAL(...)

	// Client log macros
	#define UE_TRACE(...)
	#define UE_INFO(...)
	#define UE_WARN(...)
	#define UE_ERROR(...)
	#define UE_CRITICAL(...)
#endif