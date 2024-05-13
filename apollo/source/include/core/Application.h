#pragma once

#include "../APpch.h"
#include "Core.h"
#include "Window.h"

namespace Apollo {

	class Timestep;

	struct APOLLO_API ApplicationCommandLineArgs
	{
		APi32 Count = 0;
		APccstr *Args = nullptr;

		inline const char *operator[](APi32 index)
		{
			// soft assert and clamp
			return Args[index];
		};
	};

	struct APOLLO_API ApplicationSpecification
	{
		std::string Name = "Apollo Engine";
		std::string WorkingDir;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class APOLLO_API Application
	{
	public:
		Application(const ApplicationSpecification &specification);
		virtual ~Application();

		inline Window &GetWindow() { return *p_Window; }
		inline Window *GetWindowPtr() { return p_Window; }
		inline bool IsRunning() const { return p_Running; }
		inline Application &GetApp() { return *s_Instance; }
		inline Application *GetAppPtr() { return s_Instance; }
		inline ApplicationSpecification &GetAppSpecification() { return p_Specification; }

		virtual void OnBegin();
		virtual void OnUpdate(const Timestep &ts);
		virtual void OnRender();
		virtual void OnShutDown();

		void CloseApp();

		void Run();

	protected:
		ApplicationSpecification p_Specification;
		bool p_Running = true;
		Window *p_Window = nullptr;

	private:
		static Application *s_Instance;
	};

	Application *CreateApplication(APi32 argc, APccstr argv[]);

}