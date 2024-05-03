#include "../include/APpch.h"
#include "../include/core/Application.h"

namespace Apollo {

	Application::Application(const ApplicationSpecification &specification)
		: 
		p_Specification(specification)
	{
		// assert
		if (s_Instance)
			return;

		s_Instance = this;
		p_Window = new Window(1000, 1000, specification.Name);
	}

	Application::~Application()
	{
	}

	void Application::OnBegin()
	{
		// log
	}

	void Application::OnUpdate(/* change to Timestep */ APf32 dt)
	{
	}

	void Application::OnRender()
	{
	}

	void Application::OnShutDown()
	{
	}

	void Application::CloseApp()
	{
		p_Running = false;
	}

	void Application::Run()
	{
		p_Window->SetCurrentContext();
		/* Timestep */ APf32 lastTime = 0.0f /* Platform::GetTime<APf32>() */;

		while (p_Running)
		{
			// Clear
			// Renderer::ClearScreen();

			// Calculate timestep
			APf32 currentTime = 0.0f /* Platform::GetTime<APf32>() */;
			/* Timestep */ APf32 deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// Update
			this->OnUpdate(deltaTime);

			// Render
			this->OnRender();

			// Poll events
			Window::PollEvents();

			// Swap Buffers
			p_Window->SwapBuffers();

			p_Running = p_Window->IsOpen();
		}
	}

	Application *Application::s_Instance = nullptr;
}	