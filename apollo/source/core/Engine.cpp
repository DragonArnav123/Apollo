#include <GLFW/glfw3.h>
#include "../include/core/Engine.h"
#include "../include/core/Window.h"
#include "../include/core/Log.h"
#include "../include/events/Events.h"
#include "../include/renderer/renderer2d/Renderer2D.h"

namespace Apollo {

	Util::Error g_InitializationError = Util::Error::NoError("ApolloCore");

	void Initialize()
	{
		// Initialize Log
		bool loggerInitialized = Logger::Initialize();
		if (!loggerInitialized)
		{
			g_InitializationError = Util::Error("ApolloCore", "Failed to initialize logger (spdlog)!", true);
			return;
		}
		AP_CORE_INFO("Logger Initialized")

		// Initialze Window
		bool windowIntialized = Window::Initialize();
		if (!windowIntialized)
		{
			g_InitializationError = Util::Error("ApolloCore", "Failed to initialize window (glfw)!", true);
			return;
		}
		AP_CORE_INFO("Window Initialized")

		bool eventsInitialized = Events::EventDispatcher::Initialize();
		if (!eventsInitialized)
		{
			g_InitializationError = Util::Error("ApolloCore", "Failed to intialize events!", true);
			return;
		}
		AP_CORE_INFO("Events Initialized")
	}

	void Terminate()
	{
		AP_CORE_INFO("Terminating Apollo Engine")

		// Terminate Events
		Events::EventDispatcher::Terminate();
		AP_CORE_INFO("Events Terminated")

		// Terminate Window
		Window::Terminate();
		AP_CORE_INFO("Window Terminated")

		// Terminate Log
		Logger::Terminate();
		AP_CORE_INFO("Logger Terminated")
	}

	void ForceExit(APi32 exitCode)
	{
		// Log
		Terminate();
		exit(-1);
	}

	std::string GetAssertDir()
	{
		// we can get apollo library working directory with some manipulation from __FILE__ and this file
		return "";
	}

	Util::Error APOLLO_API QueryInitializationError()
	{
		return g_InitializationError;
	}

}