#include "../../apollo/source/include/Apollo.h"
#include "include/DefaultWorld.h"
#include <GL/gl.h>

class WindowCloseEvent : public Apollo::Events::IEvent
{
public:
	static constexpr Apollo::Events::IEvent::Type sType = "WindowCloseEvent";

public:
	WindowCloseEvent(const Apollo::Window &closedWindow)
		:
		m_ClosedWindow(closedWindow)
	{
	}

	~WindowCloseEvent()
	{
	}

	const Apollo::Window &GetClosedWindow() const
	{
		return m_ClosedWindow;
	}

	Apollo::Events::IEvent::Type GetType() const override 
	{
		return sType;
	}

private:
	const Apollo::Window &m_ClosedWindow;
};

class DefaultWorld : public Apollo::Application
{
public:
	DefaultWorld(const Apollo::ApplicationSpecification &appSpecification)
		:
		Apollo::Application(appSpecification)
	{
		AP_CLIENT_LOG("Creating Default World!");
		AP_CORE_LOG("Creating Default World! Core");
	}

	~DefaultWorld()
	{
	}

	void OnBegin() override
	{
		p_Window->SetWidth(1000);
		p_Window->SetHeight(900);

		this->Position[0] = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
		this->Position[1] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		this->Position[2] = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);

		// Query Initialization Error
		Apollo::Util::Error initError = Apollo::QueryInitializationError();
		initError.LogToConsole();

		// Input Event
		Apollo::Events::EventDispatcher::AddDispatcher(
			WindowCloseEvent::sType, 
			[](const Apollo::Events::IEvent &event)
			{
				AP_CLIENT_LOG("WindowCloseEvent");
				const WindowCloseEvent &e = static_cast<const WindowCloseEvent &>(event);
				const Apollo::Window &win = e.GetClosedWindow();
				AP_CLIENT_INFO("Shutdowned window address: {}", static_cast<const void *>(&win));
			});
	}

	void OnShutDown() override
	{
		Apollo::Events::EventDispatcher::PostEvent(WindowCloseEvent(*p_Window));
	}

	void OnUpdate(const Apollo::Timestep &deltaTime) override
	{
		Apollo::Pltfrm::TimePoint epochTime = Apollo::Pltfrm::Time::GetEpoch();
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), Apollo::Pltfrm::Time::TimePointToSecondLowP(epochTime) * (glm::pi<float>() / 3), glm::vec3(0.0f, 0.0f, 1.0f));

		for (APsize i = 0; i < 3; i++)
			this->Position[i] = model * this->Position[i];
	}

	void OnRender() override
	{
		glBegin(GL_TRIANGLES);

		for (APsize i = 0; i < 3; i++)
			glVertex2f(this->Position[i].x, this->Position[i].y);

		glEnd();
	}

public:
	glm::vec4 Position[3];
};

void *RunDefaultWorld(const Apollo::ApplicationSpecification &apSpec)
{
	return new DefaultWorld(apSpec);
}