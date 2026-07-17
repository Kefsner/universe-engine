#pragma once

#include <spdlog/spdlog.h>

namespace Universe
{
    class Logger
    {
    public:
        Logger();
        ~Logger() = default;

        static void Init();

    private:
        static spdlog::logger s_CoreLogger;
        static spdlog::logger s_Logger;
    };
}


#define UE_CORE_LOGGER(x) { spdlog::info(x); }
#define UE_LOGGER(x) { spdlog::info(x); }
