#include "mcpch.h"
#include "Application.h"
#include "Core.h"
#include "IO/InputHandler.h"
#include "MCP/Renderer/VoxelRenderer.h"


namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		if (!s_Instance)
		{
			//We need to initialize the logger first in order to recieve info of the other systems initialization
			logger = new MC::Debug::Logger;

	
			s_Instance = this;

			m_Minimized = false;

			m_Window = new Window(1360, 768, "MCP");


			m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

			VoxelRenderer::Init();

			m_ImGuiLayer = new ImGuiLayer;
			PushOverLay(m_ImGuiLayer);
		}
	}

	Application::~Application()
	{
		VoxelRenderer::ShutDown();

		delete m_Window;
		delete logger;
	}
	void Application::Run()
	{
		while (m_Running)
		{
			deltaTime.tick();


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);
			

			/* Temos um memory leak vindo do imGui */
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->onUpdate();

			//flush log messages
			logger->Flush();
		}
	}

	void Application::OnEvent(Event& event)
	{
		//Exra Cases
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));
		//@TODO: Bubble up event system, de certa que forma que o World Layer pode lidar um esc com um menu e a Application lida com o 
		//fim da aplicação.

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
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Window->setWidth(e.GetWidth());
		m_Window->setHeight(e.GetHeight());

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		else
		{
			m_Minimized = false;
		}

		VoxelRenderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
//#ifdef MC_DEBUG
		if (e.GetKeyCode() == (int)MC_KEYS::MC_KEY_ESC)
		{
			WindowCloseEvent close;
			this->OnEvent(close);

			return true;
		}
		else if (e.GetKeyCode() == (int)MC_KEYS::MC_KEY_F1)
		{
			wireframeMode = !wireframeMode;
			VoxelRenderer::SetWireframeMode(wireframeMode);

			return true;
		}
		else if (e.GetKeyCode() == (int)MC_KEYS::MC_KEY_F2)
		{

			InputHandler::showCursor(lockCursor);

			lockCursor = !lockCursor;

			InputHandler::lockCursorPosition(lockCursor);

			return true;
		}
//#endif

		return false;
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
