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

	void Application::OnEvent(Event& event)
	{

		//No futuro a maioria disso aqui vai ser mandado para os Layers e somente.

		MC_LOG_TRACE(event);

		EventDispatcher Dispatcher(event);

		Dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent Event) -> bool
		{
			this->setRunning(false);
			
			return true;
		});

		//TEST
		Dispatcher.Dispatch<KeyPressedEvent>([&](KeyPressedEvent Event) -> bool
		{
			if (Event.GetKeyCode() == MC_KEYS::MC_KEY_ESC)
			{
				WindowCloseEvent e;
				this->OnEvent(e);

				return true;
			}

			return true;
		});

	}

}
