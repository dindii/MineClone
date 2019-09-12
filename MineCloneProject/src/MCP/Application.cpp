#include "mcpch.h"
#include "Application.h"
#include "Utils/Logger.h"

namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		s_Instance = this;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			MC_LOG_TRACE("Hello, World!");
			std::cin.get();
		}
	}
}
