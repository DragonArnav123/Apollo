#pragma once

#include "Core.h"
#include "../utils/Input.h"

struct GLFWwindow;

namespace Apollo {

	struct APOLLO_API WindowProperties
	{
		APsize Width;
		APsize Height;
		std::string Title;
		// icon
		bool Resizable;

		struct GLViewport
		{
			APi32 X, Y, W, H;
		} Viewport;

		struct WindowPos
		{
			APi32 X, Y;
		} Position;
	};

	class APOLLO_API Window
	{
	public:
		Window(const WindowProperties &wP);
		Window(const Window &) = delete;
		virtual ~Window();

		static bool Initialize();
		static void Terminate();

		// Getters
		inline const GLFWwindow *GetGLFWWindow() const { return m_Win; }
		inline GLFWwindow *GetGLFWWindowDebug() const 
		{
#if defined(APOLLO_CONFIG_DEBUG)
			return m_Win;
#else
			return nullptr;
#endif
		}
		APsize GetWidth() const;
		APsize GetHeight() const;
		const std::string &GetTitle() const;
		bool IsResizable() const;
		const WindowProperties &Properties() const;

		// Setters
		void SetWidth(APsize width);
		void SetHeight(APsize height);
		void SetTitle(const std::string &title);
		void SetViewportSize(const WindowProperties::GLViewport &vp);
		void SetWindowPos(const WindowProperties::WindowPos &pos);
		void CenterWindowOnScreen();

		void SetCurrentContext();
		void SwapBuffers();
		void CopyTo(Window &win);
		void Close();
		void Open();
		void Destroy();
		bool IsOpen();
		bool IsKeyPressed();
		bool IsKeyPressed(Input::KeyCode keyCode);
		bool IsKeyReleased();
		bool IsKeyReleased(Input::KeyCode keyCode);

		static void PollEvents();

	private:
		void m_SetCallbacks();

	private:
		WindowProperties m_Properties;
		GLFWwindow *m_Win;
		bool m_IsOpen = false ;
		// icon stuff
	};

}