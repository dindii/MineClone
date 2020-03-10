#include "mcpch.h"
#include "Application.h"
#include "Utils/Logger.h"
#include "Core.h"
#include "IO/InputHandler.h"
#include "MCP/Renderer/Renderer.h"


namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		s_Instance = this;
		m_Minimized = false;

		m_Window = new Window(1360, 768, "MClone!");


		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			deltaTime.tick();

			m_Window->onUpdate();	

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);
			
			//@TODO: Call imgui layer.
		}
	}

	void Application::OnEvent(Event& event)
	{
		//Exra Cases
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		//@TODO: Bubble up event system, de certa que forma que o World Layer pode lidar um esc com um menu e a Application lida com o 
		//fim da aplicação.

#ifdef MC_DEBUG
	 //temporary {
		KeyPressedEvent* evento = (KeyPressedEvent*)&event;
		if (evento->GetKeyCode() == MC_KEY_ESC)
		{
			evento->Handled = true;
			WindowCloseEvent close;
			this->OnEvent(close);
		}
		//temporary }
#endif

		if(!m_Minimized)
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			if (event.Handled)
				break;

			(*--it)->OnEvent(event);
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		e.Handled = true;
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		else
		{
			m_Minimized = false;
		}

		Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLay(layer);
	}

}
