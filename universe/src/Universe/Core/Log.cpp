#include "UEpch.h"
#include "Universe/Core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Universe {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		s_CoreLogger = spdlog::stdout_color_mt("UNIVERSE");

		s_ClientLogger = spdlog::stdout_color_mt("APP");
	}
}