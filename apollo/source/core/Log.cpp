#include "../include/APpch.h"
#include "../include/core/Log.h"

namespace Apollo {

	namespace Internal {
		static void Log(APccstr file, APccstr func, APi32 line, LogType type, bool isCore, const std::string &format, ...)
		{

		}
	}


	Logger::Logger()
	{

	}

	Logger::~Logger()
	{

	}

	void Logger::Initialize()
	{

	}

	void Logger::Terminate()
	{

	}

	void Logger::LogCore(APccstr file, APccstr func, APi32 line, LogType type, const std::string &format, ...)
	{
		Internal::Log(file, func, line, type, true, format, ...);
	}

	void Logger::LogClient(APccstr file, APccstr func, APi32 line, LogType type, const std::string &format, ...)
	{
		Internal::Log(file, func, line, type, false, format, ...);
	}

}