#pragma once

#include "../APpch.h"
#include "Core.h"

namespace Apollo {

	void APOLLO_API Initialize();

	void APOLLO_API Terminate();

	void APOLLO_API ForceExit(/* some kinda of error class */ APi32 exitCode);

	std::string APOLLO_API GetApolloAssertDirectory();
	
}