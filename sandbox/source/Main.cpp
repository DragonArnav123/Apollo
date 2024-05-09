#include "../../apollo/source/include/Apollo.h"
#include <GL/gl.h>

class Sandbox : public Apollo::Application
{
public:
	Sandbox(const Apollo::ApplicationSpecification &appSpecification)
		:
		Apollo::Application(appSpecification)
	{
	}

	~Sandbox()
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
	}

	void OnShutDown() override
	{
	}

	void OnUpdate(APf32 deltaTime) override
	{
		static APf32 coeff = 0.0f;

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), coeff * (glm::pi<float>() / 3), glm::vec3(0.0f, 0.0f, 1.0f));

		for (APsize i = 0; i < 3; i++)
			this->Position[i] = model * this->Position[i];

		coeff += 0.000001f;
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

Apollo::Application *Apollo::CreateApplication(APi32 argc, APccstr argv[])
{
	Sandbox *sandbox = new Sandbox( { "Test Apollo::Window", "", { argc, argv } } );

	return sandbox;
}