#include "../include/core/Window.h"
#include "../include/_glfw.h"

static void WindowHints()
{
	// todo
}

namespace Apollo {

	Window::Window(APsize width, APsize height)
		: 
		m_Width(width),
		m_Height(height),
		m_Title("Apollo Window")
	{
		::WindowHints();		
		m_Win = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		glfwSetWindowUserPointer(m_Win, this);
		m_SetCallbacks();
	}

	Window::Window(APsize size)
		:
		m_Width(size),
		m_Height(size),
		m_Title("Apollo Window")
	{
		::WindowHints();
		m_Win = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		glfwSetWindowUserPointer(m_Win, this);
		m_SetCallbacks();
	}

	Window::Window(APsize width, APsize height, const std::string &name)
		:
		m_Width(width),
		m_Height(height),
		m_Title(name)
	{
		::WindowHints();
		m_Win = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		glfwSetWindowUserPointer(m_Win, this);
		m_SetCallbacks();
	}

	Window::Window(APsize size, const std::string &name)
		:
		m_Width(size),
		m_Height(size),
		m_Title(name)
	{
		::WindowHints();
		m_Win = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		glfwSetWindowUserPointer(m_Win, this);
		m_SetCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Win);
	}

	void Window::Initialize()
	{
		static bool initialized = false;

		if (initialized) return;

		if (!glfwInit())
		{
			// logging , hard assert
			std::cout << " Could not initailize glfw \n";
		}

		initialized = true;
	}

	void Window::Terminate()
	{
		// log
		glfwTerminate();
	}

	void Window::SetWidth(APsize width)
	{
		m_Width = width;
		glfwSetWindowSize(m_Win, m_Width, m_Height);
	}

	void Window::SetHeight(APsize height)
	{
		m_Height = height;
		glfwSetWindowSize(m_Win, m_Width, m_Height);
	}

	void Window::SetTitle(const std::string &title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Win, m_Title.c_str());
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
		win.SetWidth(m_Width);
		win.SetHeight(m_Height);
		win.SetTitle(m_Title);
	}

	bool Window::IsKeyPressed()
	{
		return false;
	}

	bool Window::IsMouseButtonPressed()
	{
		return false;
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

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::m_SetCallbacks()
	{

	}

}