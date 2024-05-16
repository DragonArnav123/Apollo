#include "../include/APpch.h"
#include "../include/core/Window.h"
#include "../include/core/Log.h"
#include "../include/events/ApolloEvents.h"
#include "../include/_glfw.h"

namespace Apollo {
namespace Internal {

	AP_INTERNAL_FUNC void WindowHints()
	{
		// OpenGL Profile
		// OpenGL Major Version
		// OpenGL Minor Version
	}

}
}

namespace Apollo {

	Window::Window(const WindowProperties &wp)
		: 
		m_Properties(wp)
	{
		Internal::WindowHints();		

		if (!m_Properties.Resizable)
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_POSITION_X, m_Properties.Position.X);
		glfwWindowHint(GLFW_POSITION_Y, m_Properties.Position.Y);

		m_Win = 
			glfwCreateWindow(
				m_Properties.Width, 
				m_Properties.Height, 
				m_Properties.Title.c_str(), 
				NULL, NULL);
		glfwSetWindowUserPointer(m_Win, this);
		m_SetCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Win);
	}

	bool Window::Initialize()
	{
		static bool initialized = false;

		if (initialized) return true;

		if (!glfwInit())
		{
			return false;
		}

		initialized = true;
		return true;
	}

	void Window::Terminate()
	{
		// log
		glfwTerminate();
	}

	APsize Window::GetWidth() const
	{
		return m_Properties.Width;
	}

	APsize Window::GetHeight() const
	{
		return m_Properties.Height;
	}

	const std::string &Window::GetTitle() const
	{
		return m_Properties.Title;
	}

	bool Window::IsResizable() const
	{
		return m_Properties.Resizable;
	}

	const WindowProperties &Window::Properties() const
	{
		return m_Properties;
	}

	void Window::SetWidth(APsize width)
	{
		m_Properties.Width = width;
		glfwSetWindowSize(m_Win, m_Properties.Width, m_Properties.Height);
	}

	void Window::SetHeight(APsize height)
	{
		m_Properties.Height = height;
		glfwSetWindowSize(m_Win, m_Properties.Width, m_Properties.Height);
	}

	void Window::SetTitle(const std::string &title)
	{
		m_Properties.Title = title;
		glfwSetWindowTitle(m_Win, m_Properties.Title.c_str());
	}

	void Window::SetViewportSize(const WindowProperties::GLViewport &vp)
	{
		m_Properties.Viewport = vp;
		glViewport(vp.X, vp.Y, vp.W, vp.H);
	}

	void Window::SetWindowPos(const WindowProperties::WindowPos &p)
	{
		m_Properties.Position = p;
		glfwSetWindowPos(m_Win, p.X, p.Y);
	}

	void Window::SetCurrentContext()
	{
		m_IsOpen = true;
		glfwMakeContextCurrent(m_Win);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Win);
	}

	void Window::CopyTo(Window &win)
	{
		win.SetWidth(m_Properties.Width);
		win.SetHeight(m_Properties.Height);
		win.SetTitle(m_Properties.Title);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Win, GLFW_TRUE);
		m_IsOpen = false;
	}
	
	void Window::Open()
	{
		glfwSetWindowShouldClose(m_Win, GLFW_FALSE);
		m_IsOpen = true;
	}
	
	void Window::Destroy()
	{
		glfwDestroyWindow(m_Win);
		m_IsOpen = false;
	}

	bool Window::IsOpen()
	{
		m_IsOpen = !(glfwWindowShouldClose(m_Win));
		return m_IsOpen;
	}

	bool Window::IsKeyPressed()
	{
		return false;
	}

	bool Window::IsKeyPressed(Input::KeyCode keyCode)
	{
		return (bool) (glfwGetKey(m_Win, (APi32) keyCode) == GLFW_PRESS);
	}	

	bool Window::IsKeyReleased()
	{
		return false;
	}

	bool Window::IsKeyReleased(Input::KeyCode keyCode)
	{
		return (bool) (glfwGetKey(m_Win, (APi32) keyCode) == GLFW_RELEASE);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::m_SetCallbacks()
	{
#define GLFW_WIN \
		Window *_w = \
			static_cast<Window *>(\
				glfwGetWindowUserPointer(w));

		// Window Resize Callback
		auto winRes = [](GLFWwindow *w, APi32 width, APi32 height) {
			GLFW_WIN
			_w->m_Properties.Width = width;
			_w->m_Properties.Height = height;

			Events::EventDispatcher::PostEvent(Events::WindowResize(*_w, width, height));
		};
		glfwSetWindowSizeCallback(m_Win, winRes);

		// Window Close Callback
		auto winCls = [](GLFWwindow *w) {
			GLFW_WIN

			Events::EventDispatcher::PostEvent(Events::WindowClose(*_w, 0));
		};
		glfwSetWindowCloseCallback(m_Win, winCls);

		// Window Refresh Callback
		auto winRef = [](GLFWwindow *w) {
			GLFW_WIN

			// glfwSwapBuffers(w);
			Events::EventDispatcher::PostEvent(Events::WindowRefresh(*_w));
		};
		glfwSetWindowRefreshCallback(m_Win, winRef);

		// Window Move Callback
		auto winMov = [](GLFWwindow *w, APi32 x, APi32 y) {
			GLFW_WIN
			_w->m_Properties.Position.X = x;
			_w->m_Properties.Position.Y = y;

			Events::EventDispatcher::PostEvent(Events::WindowMove(*_w, x, y));
		};
		glfwSetWindowPosCallback(m_Win, winMov);

		// FrameBuffer Resize Callback
		auto fbfRes = [](GLFWwindow *w, APi32 width, APi32 height) {
			GLFW_WIN

			_w->SetViewportSize( { 0, 0, width, height } );

			Events::EventDispatcher::PostEvent(Events::FramebufferResize(*_w, width, height));
		};
		glfwSetFramebufferSizeCallback(m_Win, fbfRes);

		// Key Press Callback
		auto keyPrs = [](
			GLFWwindow* w, 
			APi32 key,
			APi32 scancode,
			APi32 action,
			APi32 mods) {
			GLFW_WIN

			if (action == GLFW_PRESS)
				Events::EventDispatcher::PostEvent(
					Events::KeyPress(
						*_w, 
						static_cast<Input::KeyCode>(key)));
			else
				AP_CORE_WARN("Yet to complete this");
		};
		glfwSetKeyCallback(m_Win, keyPrs);

		// Text Input Callback
		auto txtInp = []() {

		};

		// Mouse Press Callback
		auto msePrs = []() {

		};

		// Mouse Move Callback
		auto mseMov = []() {

		};

		// Mouse Scroll Callback
		auto mseScr = []() {

		};

		// Window Maximized
		// Some content scaling thingy
		// Window Focus thingy
	}

	// Window attention thingy
	// Window visibility thingy


}