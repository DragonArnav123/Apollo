#pragma once

#include "Core.h"
#include "../utils/Input.h"

struct GLFWwindow;

namespace Apollo {

	class APOLLO_API Window
{
	public:
		Window(APsize width, APsize height);
		Window(APsize size);
		Window(APsize width, APsize height, const std::string &name);
		Window(APsize size, const std::string &name);
		Window(const Window &) = delete;
		virtual ~Window();

		static bool Initialize();
		static void Terminate();

		// getters
		inline const GLFWwindow *GetGLFWWindow() const { return m_Win; }
		inline GLFWwindow *GetGLFWWindowDebug() const 
		{
#if defined(APOLLO_CONFIG_DEBUG)
			return m_Win;
#else
			return nullptr;
#endif
		}
		inline APsize GetWidth() const { return m_Width; }
		inline APsize GetHeight() const { return m_Height; }
		inline const std::string &GetTitle() const { return m_Title; }

		// setters
		void SetWidth(APsize width);
		void SetHeight(APsize height);
		void SetTitle(const std::string &title);

		void SetCurrentContext();
		void SwapBuffers();
		void CopyTo(Window &win);
		bool IsKeyPressed();
		bool IsMouseButtonPressed();
		void Close();
		void Open();
		void Destroy();
		bool IsOpen();

		static void PollEvents();

	private:
		void m_SetCallbacks();

	private:
		APsize m_Width, m_Height;
		std::string m_Title;
		GLFWwindow *m_Win;
		bool m_IsOpen = false ;
		// icon stuff
	};

}