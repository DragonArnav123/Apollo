#pragma once

#include "Events.h"
#include "../core/Core.h"
#include "../utils/Input.h"

namespace Apollo {
	class Window;

namespace Events {

	class APOLLO_API WindowResize : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "WindowResize";

	public:
		explicit WindowResize(const Window &resizedWindow, APsize newWidth, APsize newHeight);
		~WindowResize();

		IEvent::Type GetType() const override;

		const Window &GetWindow() const;
		APsize GetWidth() const;
		APsize GetHeight() const;

		static APsize GetOldWidth();
		static APsize GetOldHeight();

	private:
		const Window &m_Window;
		APsize m_NewWidth, m_NewHeight;
		static APsize s_OldWidth, s_OldHeight;
	};

	class APOLLO_API WindowClose : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "WindowClose";

	public:
		explicit WindowClose(const Window &closedWindow, APi32 exitCode);
		~WindowClose();

		IEvent::Type GetType() const override;

		const Window &GetWindow() const;

		APi32 GetExitCode() const;

	private:
		const Window &m_Window;
		APi32 m_ExitCode;
	};

	class APOLLO_API WindowRefresh : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "WindowRefresh";

	public:
		explicit WindowRefresh(const Window &refreshedWindow);
		~WindowRefresh();

		IEvent::Type GetType() const override;

		const Window &GetWindow() const;

	private:
		const Window &m_Window;
	};

	class APOLLO_API WindowMove : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "WindowMove";

	public:
		explicit WindowMove(const Window &movedWindow, APi32 newXCoord, APi32 newYCoord);
		~WindowMove();

		IEvent::Type GetType() const override;

		const Window &GetWindow() const;

		APi32 GetNewXCoord() const;
		APi32 GetNewYCoord() const;

		static APi32 GetOldXCoord();
		static APi32 GetOldYCoord();

	private:
		const Window &m_Window;
		APi32 m_NewXCoord, m_NewYCoord;
		static APi32 s_OldXCoord, s_OldYCoord;
	};

	class APOLLO_API FramebufferResize : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "FramebufferResize";

	public:
		explicit FramebufferResize(const Window &resizedWindow, APsize newWidth, APsize newHeight);
		~FramebufferResize();

		IEvent::Type GetType() const override;

		const Window &GetWindow() const;
		APsize GetWidth() const;
		APsize GetHeight() const;

		static APsize GetOldWidth();
		static APsize GetOldHeight();

	private:
		const Window &m_Window;
		APsize m_NewWidth, m_NewHeight;
		static APsize s_OldWidth, s_OldHeight;
	};


	class APOLLO_API KeyPress : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "KeyPress";

	public:
		explicit KeyPress(const Window &window, Input::KeyCode keyCode);
		~KeyPress();

		IEvent::Type GetType() const override;

		const Window &GetWindow() const;
		Input::KeyCode GetKeyCode() const;

	private:
		const Window &m_Window;
		Input::KeyCode m_KeyCode;
	};

	class APOLLO_API TextInput : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "";

	public:


		IEvent::Type GetType() const override;

	private:
	};

	class APOLLO_API MousePress : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "";

	public:


		IEvent::Type GetType() const override;

	private:
	};

	class APOLLO_API MouseMove : public IEvent	{
	public:
		static constexpr IEvent::Type sType = "";

	public:

		IEvent::Type GetType() const override;

	};	

	class APOLLO_API MouseScroll : public IEvent
	{
	public:
		static constexpr IEvent::Type sType = "";

	public:


		IEvent::Type GetType() const override;

	private:
	};

}
}