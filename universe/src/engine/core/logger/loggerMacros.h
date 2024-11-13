#pragma once

#ifdef UE_ENABLE_LOGGING
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