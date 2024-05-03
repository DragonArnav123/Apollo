#include "../include/core/Engine.h"
#include "../include/core/Window.h"
#include "../include/core/Log.h"
#include "../include/renderer/renderer2d/Renderer2D.h"

namespace Apollo {

	void Initialize()
	{
		// Initialze Window
		Window::Initialize();
	}

	void Terminate()
	{
		// Terminate Window
		Window::Terminate();
	}

	void ForceExit(APi32 exitCode)
	{
		// Log
		Terminate();
		exit(-1);
	}

	std::string GetApolloAssertDirectory()
	{
		// we can get apollo library working directory with some manipulation from __FILE__ and this file
	}

}