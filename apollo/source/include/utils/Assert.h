#pragma once

#include "../APpch.h"
#include "../core/Core.h"

#define APOLLO_SOFT_ASSERT(expression, message) 						Apollo::Util::Assert(expression, message, Apollo::Util::AssertType::SOFT_ASSERT);
#define APOLLO_HARD_ASSERT(expression, message) 						Apollo::Util::Assert(expression, message, Apollo::Util::AssertType::HARD_ASSERT);
#define APOLLO_FATTAL_ASSERT(expression, message) 						Apollo::Util::Assert(expression, message, Apollo::Util::AssertType::FATAL_ASSERT);

#if defined(APOLLO_CONFIG_DEBUG)
	#define APOLLO_DBG_SOFT_ASSERT(expression, message) 				Apollo::Util::Assert(expression, message, Apollo::Util::AssertType::DEBUG_SOFT_ASSERT);
	#define APOLLO_DBG_HARD_ASSERT(expression, message) 				Apollo::Util::Assert(expression, message, Apollo::Util::AssertType::DEBUG_HARD_ASSERT);
	#define APOLLO_DBG_FATTAL_ASSERT(expression, message) 				Apollo::Util::Assert(expression, message, Apollo::Util::AssertType::DEBUG_FATAL_ASSERT);
#else
	#define APOLLO_DBG_SOFT_ASSERT(expression, message) 		
	#define APOLLO_DBG_HARD_ASSERT(expression, message) 			
	#define APOLLO_DBG_FATTAL_ASSERT(expression, message) 			
#endif

#define APOLLO_SOFT_FUNC_ASSERT(lambda_func, message, ...) 				Apollo::Util::Assert<__VA_ARGS__>(lambda_func, message, Apollo::Util::AssertType::SOFT_ASSERT);
#define APOLLO_HARD_FUNC_ASSERT(lambda_func, message, ...) 				Apollo::Util::Assert<__VA_ARGS__>(lambda_func, message, Apollo::Util::AssertType::HARD_ASSERT);
#define APOLLO_FATTAL_FUNC_ASSERT(lambda_func, message, ...) 			Apollo::Util::Assert<__VA_ARGS__>(lambda_func, message, Apollo::Util::AssertType::FATAL_ASSERT);

#if defined(APOLLO_CONFIG_DEBUG)
	#define APOLLO_DBG_SOFT_FUNC_ASSERT(lambda_func, message, ...) 		Apollo::Util::Assert<__VA_ARGS__>(lambda_func, message, Apollo::Util::AssertType::DEBUG_SOFT_ASSERT);
	#define APOLLO_DBG_HARD_FUNC_ASSERT(lambda_func, message, ...) 		Apollo::Util::Assert<__VA_ARGS__>(lambda_func, message, Apollo::Util::AssertType::DEBUG_HARD_ASSERT);
	#define APOLLO_DBG_FATTAL_FUNC_ASSERT(lambda_func, message, ...) 	Apollo::Util::Assert<__VA_ARGS__>(lambda_func, message, Apollo::Util::AssertType::DEBUG_FATAL_ASSERT);
#else
	#define APOLLO_DBG_SOFT_FUNC_ASSERT(lambda_func, message, ...) 		
`	#define APOLLO_DBG_HARD_FUNC_ASSERT(lambda_func, message, ...) 			
	#define APOLLO_DBG_FATTAL_FUNC_ASSERT(lambda_func, message, ...) 			
#endif

namespace Apollo {
namespace Util {

	enum class AssertType
	{
		SOFT_ASSERT 		 = 0x000,
		HARD_ASSERT 				,
		FATAL_ASSERT				,
		DEBUG_SOFT_ASSERT 			,
		DEBUG_HARD_ASSERT 			,		
		DEBUG_FATAL_ASSERT			,
	};

	void APOLLO_API Assert(bool expression, const std::string &message, const AssertType &type);

	// template <Args...>
	// void APOLLO_API Assert(const std::functional<bool (Args)> &func, const std::string &message, const AssertType &type);

}
}