#include "../include/utils/Assert.h"

namespace Apollo {
namespace Internal {
	static void SoftAssert(bool expression, const std::string &message, bool isDbg)
	{

	}

	static void HardAssert(bool expression, const std::string &message, bool isDbg)
	{

	}

	static void FatalAssert(bool expression, const std::string &message, bool isDbg)
	{

	}
}

namespace Util {

	void APOLLO_API Assert(bool expression, const std::string &message, const AssertType &type)
	{
		switch (type)
		{
			case SOFT_ASSERT:
				Internal::SoftAssert(expression, message, false);
				break;	
			
			case HARD_ASSERT:
				Internal::HardAssert(expression, message, false);
				break;
			
			case FATAL_ASSERT:
				Internal::FatalAssert(expression, message, false);
				break;
			
			case DEBUG_SOFT_ASSERT:
				Internal::SoftAssert(expression, message, true);
				break;
			
			case DEBUG_HARD_ASSERT:
				Internal::HardAssert(expression, message, true);
				break; 
			
			case DEBUG_FATAL_ASSERT:
				Internal::FatalAssert(expression, message, true);
				break;
		}
	}

	// template <Args...>
	// void APOLLO_API Assert<Args>(const std::functional<bool (Args)> &func, const std::string &message, const AssertType &type)
	// {
	// 	switch (type)
	// 	{
	// 		case SOFT_ASSERT:
	// 			Internal::SoftAssert(expression, message, false);
	// 			break;	
			
	// 		case HARD_ASSERT:
	// 			Internal::HardAssert(expression, message, false);
	// 			break;
			
	// 		case FATAL_ASSERT:
	// 			Internal::FatalAssert(expression, message, false);
	// 			break;
			
	// 		case DEBUG_SOFT_ASSERT:
	// 			Internal::SoftAssert(expression, message, true);
	// 			break;
			
	// 		case DEBUG_HARD_ASSERT:
	// 			Internal::HardAssert(expression, message, true);
	// 			break; 
			
	// 		case DEBUG_FATAL_ASSERT:
	// 			Internal::FatalAssert(expression, message, true);
	// 			break;
	// 	}
	// }

}
}