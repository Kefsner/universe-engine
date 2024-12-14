#pragma once

#include <spdlog/spdlog.h>

namespace Universe
{
    class Logger
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#if defined(UE_DEBUG)
    #define UE_CORE_TRACE(...) ::Universe::Logger::GetCoreLogger()->trace(__VA_ARGS__)
    #define UE_CORE_INFO(...) ::Universe::Logger::GetCoreLogger()->info(__VA_ARGS__)
    #define UE_CORE_WARN(...) ::Universe::Logger::GetCoreLogger()->warn(__VA_ARGS__)
    #define UE_CORE_ERROR(...) ::Universe::Logger::GetCoreLogger()->error(__VA_ARGS__)
#else
    #define UE_CORE_TRACE(...)
    #define UE_CORE_INFO(...)
    #define UE_CORE_WARN(...)
    #define UE_CORE_ERROR(...)
#endif

#define UE_TRACE(...) ::Universe::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define UE_INFO(...) ::Universe::Logger::GetClientLogger()->info(__VA_ARGS__)
#define UE_WARN(...) ::Universe::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define UE_ERROR(...) ::Universe::Logger::GetClientLogger()->error(__VA_ARGS__)