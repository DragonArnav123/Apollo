#include "../include/APpch.h"
#include "../include/events/ApolloEvents.h"
#include "../include/core/Window.h"

namespace Apollo {
namespace Events {

	APsize WindowResize::s_OldWidth;
	APsize WindowResize::s_OldHeight;

	WindowResize::WindowResize(
		const Window &rw,
		APsize nW,
		APsize nH)
		:
		m_Window(rw),
		m_NewWidth(nW),
		m_NewHeight(nH)
	{
		AP_LOCAL_PERSIST bool firstTime = true;

		if (firstTime)
		{
			s_OldWidth = m_NewWidth;
			s_OldHeight = m_NewHeight;
			firstTime = false;
		}
	}

	WindowResize::~WindowResize()
	{
		s_OldWidth = m_NewWidth;
		s_OldHeight = m_NewHeight;
	}

	IEvent::Type WindowResize::GetType() const
	{
		return sType;
	}

	const Window &WindowResize::GetWindow() const
	{
		return m_Window;
	}

	APsize WindowResize::GetWidth() const 
	{
		return m_NewWidth;
	}

	APsize WindowResize::GetHeight() const
	{
		return m_NewHeight;
	}

	APsize WindowResize::GetOldWidth()
	{
		return s_OldWidth;
	}

	APsize WindowResize::GetOldHeight()
	{
		return s_OldHeight;
	}

	WindowClose::WindowClose(const Window &cw, APi32 ec)
		:
		m_Window(cw),
		m_ExitCode(ec)
	{
	}

	WindowClose::~WindowClose()
	{
	}

	IEvent::Type WindowClose::GetType() const
	{
		return sType;
	}

	const Window &WindowClose::GetWindow() const
	{
		return m_Window;
	}

	APi32 WindowClose::GetExitCode() const
	{
		return m_ExitCode;
	}

	WindowRefresh::WindowRefresh(const Window &rw)
		:
		m_Window(rw)
	{
	}

	WindowRefresh::~WindowRefresh()
	{
	}

	IEvent::Type WindowRefresh::GetType() const
	{
		return sType;
	}

	const Window &WindowRefresh::GetWindow() const
	{
		return m_Window;
	}

	APi32 WindowMove::s_OldXCoord;
	APi32 WindowMove::s_OldYCoord;

	WindowMove::WindowMove(
		const Window &mw,
		APi32 nX,
		APi32 nY)
		:
		m_Window(mw),
		m_NewXCoord(nX),
		m_NewYCoord(nY)
	{
		AP_LOCAL_PERSIST bool firstTime = true;

		if (firstTime)
		{
			s_OldXCoord = m_NewXCoord;
			s_OldYCoord = m_NewYCoord;
			firstTime = false;
		}
	}

	WindowMove::~WindowMove()
	{
		s_OldXCoord = m_NewXCoord;
		s_OldYCoord = m_NewYCoord;
	}

	IEvent::Type WindowMove::GetType() const
	{
		return sType;
	}

	const Window &WindowMove::GetWindow() const
	{
		return m_Window;
	}

	APi32 WindowMove::GetNewXCoord() const
	{
		return m_NewXCoord;
	}

	APi32 WindowMove::GetNewYCoord() const
	{
		return m_NewYCoord;
	}

	APi32 WindowMove::GetOldXCoord()
	{
		return s_OldXCoord;
	}

	APi32 WindowMove::GetOldYCoord()
	{
		return s_OldYCoord;
	}

	APsize FramebufferResize::s_OldWidth;
	APsize FramebufferResize::s_OldHeight;

	FramebufferResize::FramebufferResize(
		const Window &rw,
		APsize nW,
		APsize nH)
		:
		m_Window(rw),
		m_NewWidth(nW),
		m_NewHeight(nH)
	{
		AP_LOCAL_PERSIST bool firstTime = true;

		if (firstTime)
		{
			s_OldWidth = m_NewWidth;
			s_OldHeight = m_NewHeight;
			firstTime = false;
		}
	}

	FramebufferResize::~FramebufferResize()
	{
		s_OldWidth = m_NewWidth;
		s_OldHeight = m_NewHeight;
	}

	IEvent::Type FramebufferResize::GetType() const
	{
		return sType;
	}

	const Window &FramebufferResize::GetWindow() const
	{
		return m_Window;
	}

	APsize FramebufferResize::GetWidth() const 
	{
		return m_NewWidth;
	}

	APsize FramebufferResize::GetHeight() const
	{
		return m_NewHeight;
	}

	APsize FramebufferResize::GetOldWidth()
	{
		return s_OldWidth;
	}

	APsize FramebufferResize::GetOldHeight()
	{
		return s_OldHeight;
	}

	KeyPress::KeyPress(
		const Window &w,
		Input::KeyCode kc)
		:
		m_Window(w),
		m_KeyCode(kc)
	{
	}

	KeyPress::~KeyPress()
	{
	}

	IEvent::Type KeyPress::GetType() const
	{
		return sType;
	}

	const Window &KeyPress::GetWindow() const
	{
		return m_Window;
	}

	Input::KeyCode KeyPress::GetKeyCode() const
	{
		return m_KeyCode;
	}

}
}