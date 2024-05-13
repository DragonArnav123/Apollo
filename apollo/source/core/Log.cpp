#include "../include/APpch.h"
#include "../include/core/Log.h"
#include "../../../library/spdlog/include/spdlog/sinks/stdout_color_sinks.h"

namespace Apollo {
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
	std::string Logger::m_Format = "[%n](%@)(%T)[%l]: %v";

	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
	}

	bool Logger::Initialize()
	{
		spdlog::set_pattern(m_Format);

		s_CoreLogger = spdlog::stdout_color_mt("APOLLO");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

		return true; /* handle if this ever fails */
	}

	void Logger::Terminate()
	{
		s_CoreLogger->warn("@TODO: Logger::Terminate");
	}

	std::shared_ptr<spdlog::logger> &Logger::GetCoreLogger()
	{
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger> &Logger::GetClientLogger()
	{
		return s_ClientLogger;
	}

}