#include "mcpch.h"
#include "Application.h"
#include "Utils/Logger.h"
#include "Core.h"
#include "IO/InputHandler.h"


//test
#include "Object/Mesh/MeshLoader.h"

namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		s_Instance = this;

		m_Window = new Window(1360, 720, "MClone!");

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		//TEST
		MC::Mesh mesh = MC::MeshLoader::loadOBJFile("bla.txt");

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

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			//@TODO: Call imgui layer.

		}
	}

	void Application::OnEvent(Event& event)
	{
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
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
