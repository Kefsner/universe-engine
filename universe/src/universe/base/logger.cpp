#include "pch.hpp"

#include "universe/base/logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Universe
{
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
    
    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("UNIVERSE");
        s_CoreLogger->set_level(spdlog::level::trace);
    
        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);

        UE_CORE_INFO("Welcome to Universe");
    };
}