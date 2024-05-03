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

}