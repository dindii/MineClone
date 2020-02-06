#pragma once
#include "Window.h"
#include "LayerStack.h"
#include "MCP/Platform/DeltaTime.h"

namespace MC
{

	/*
	* Aqui � a central do programa, basicamente poderia se chamar "Engine", a Application � um singleton (como s� temos uma Application) que ter�
	  suas janelas, seus sistemas de renderer e ir� tamb�m distribuir os eventos que � recebido por meio de nossa janela.
	  Aqui tamb�m atualizaremos todos os sistemas e com isso daremos oportunidade ao App.cpp funcionar perfeitamente.
	*/

	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& e);

		inline void setRunning(bool isRunning) { m_Running = isRunning; }

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

	private:
		static Application* s_Instance;
	
	private:
		bool m_Running;
		Window* m_Window;
		LayerStack m_LayerStack;

		DeltaTime deltaTime;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();

}