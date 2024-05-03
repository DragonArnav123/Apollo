#pragma once

#include "../APpch.h"
#include "Core.h"

#if defined(APOLLO_CORE)
	#define AP_CORE_LOG(format, ...) 			Apollo::Logger::LogCore(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::LOG, std::string(format), __VA_ARGS__);
	#define AP_CORE_TRACE(format, ...) 			Apollo::Logger::LogCore(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::TRACE, std::string(format), __VA_ARGS__);
	#define AP_CORE_INFO(format, ...) 			Apollo::Logger::LogCore(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::INFO, std::string(format), __VA_ARGS__);
	#define AP_CORE_WARN(format, ...) 			Apollo::Logger::LogCore(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::WARN, std::string(format), __VA_ARGS__);
	#define AP_CORE_FATAL(format, ...) 			Apollo::Logger::LogCore(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::FATAL, std::string(format), __VA_ARGS__);
#else
	#define AP_CORE_LOG(format, ...)
	#define AP_CORE_TRACE(format, ...) 	
	#define AP_CORE_INFO(format, ...) 
	#define AP_CORE_WARN(format, ...) 
	#define AP_CORE_FATAL(format, ...) 	
#endif

#define AP_CLIENT_LOG(format, ...) 				Apollo::Logger::LogClient(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::LOG, std::string(format), __VA_ARGS__);
#define AP_CLIENT_TRACE(format, ...) 			Apollo::Logger::LogClient(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::TRACE, std::string(format), __VA_ARGS__);
#define AP_CLIENT_INFO(format, ...) 			Apollo::Logger::LogClient(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::INFO, std::string(format), __VA_ARGS__);
#define AP_CLIENT_WARN(format, ...) 			Apollo::Logger::LogClient(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::WARN, std::string(format), __VA_ARGS__);
#define AP_CLIENT_FATAL(format, ...) 			Apollo::Logger::LogClient(__FILE__, __FUNCTION__, __LINE__, Apollo::LogType::FATAL, std::string(format), __VA_ARGS__);

namespace Apollo {

	enum class LogType
	{
		LOG    			 = 0x000,
		TRACE 					,
		INFO 					,
		WARN 					,
		FATAL 					,
		ASSERT_OK 				,
	};

	class APOLLO_API Logger
	{
	public:
		Logger();
		virtual ~Logger();

		static void Initialize();
		static void Terminate();

		static void LogCore(APccstr file, APccstr func, APi32 line, LogType type, const std::string &format, ...);
		static void LogClient(APccstr file, APccstr func, APi32 line, LogType type, const std::string &format, ...);
	};

}