#pragma once

#include "Core.h"
#include "../../../../library/spdlog/include/spdlog/spdlog.h"

#if defined(APOLLO_CORE)
	// #define AP_CORE_LOG(...) 			::Apollo::Logger::GetCoreLogger()->log(__VA_ARGS__);
	#define AP_CORE_LOG(...)
	#define AP_CORE_TRACE(...) 			::Apollo::Logger::GetCoreLogger()->trace(__VA_ARGS__);
	#define AP_CORE_INFO(...) 			::Apollo::Logger::GetCoreLogger()->info(__VA_ARGS__);
	#define AP_CORE_ERROR(...) 			::Apollo::Logger::GetCoreLogger()->error(__VA_ARGS__);
	#define AP_CORE_WARN(...) 			::Apollo::Logger::GetCoreLogger()->warn(__VA_ARGS__);
	#define AP_CORE_CRITICAL(...) 		::Apollo::Logger::GetCoreLogger()->critical(__VA_ARGS__);
#else
	#define AP_CORE_LOG(...)
	#define AP_CORE_TRACE(...) 	
	#define AP_CORE_INFO(...) 
	#define AP_CORE_ERROR(...) 
	#define AP_CORE_WARN(...) 
	#define AP_CORE_CRITICAL(...) 	
#endif

// #define AP_CLIENT_LOG(...) 				::Apollo::Logger::GetClientLogger()->log(__VA_ARGS__);
#define AP_CLIENT_LOG(...) 				
#define AP_CLIENT_TRACE(...) 			::Apollo::Logger::GetClientLogger()->trace(__VA_ARGS__);
#define AP_CLIENT_INFO(...) 			::Apollo::Logger::GetClientLogger()->info(__VA_ARGS__);
#define AP_CLIENT_ERROR(...) 			::Apollo::Logger::GetClientLogger()->error(__VA_ARGS__);
#define AP_CLIENT_WARN(...) 			::Apollo::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define AP_CLIENT_CRITICAL(...) 		::Apollo::Logger::GetClientLogger()->critical(__VA_ARGS__);

namespace Apollo {

	class APOLLO_API Logger
	{
	public:
		Logger();
		virtual ~Logger();

		static bool Initialize();
		static void Terminate();

		static std::shared_ptr<spdlog::logger> &GetCoreLogger();
		static std::shared_ptr<spdlog::logger> &GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger, s_ClientLogger;
		static std::string m_Format;
	};

}