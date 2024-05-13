#include "../include/APpch.h"
#include "../include/core/Application.h"
#include "../include/core/Timestep.h"
#include "../include/platform/Time.h"

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

	void Application::OnUpdate(const Timestep &ts)
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
		Pltfrm::TimePoint lastTime = Pltfrm::TimePoint(0, 0, 0, 0);

		while (p_Running)
		{
			// Clear
			// Renderer::ClearScreen();

			// Calculate timestep
			// Get the current time
			Pltfrm::TimePoint currentTime = Pltfrm::Time::GetCurrentTime();

			// Calculate the delta time
			Pltfrm::TimePoint deltaTime = currentTime - lastTime;

			// Calculate the timestep by converting everything into seconds
			Timestep timeStep = Pltfrm::Time::TimePointToSecondLowP(deltaTime);
			lastTime = currentTime;

			// Update
			this->OnUpdate(timeStep);

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