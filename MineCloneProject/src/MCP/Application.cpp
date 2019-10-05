#include "mcpch.h"
#include "Application.h"
#include "Utils/Logger.h"
#include "Core.h"

namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		s_Instance = this;

		m_Window = new Window(1360, 720, "MClone!");

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->onUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		std::cout << e.ToString() << std::endl;
	}

}
