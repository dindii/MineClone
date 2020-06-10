#pragma once
#include "Window.h"
#include "LayerStack.h"
#include "MCP/Platform/DeltaTime.h"

namespace MC
{

	/*
	* Aqui é a central do programa, basicamente poderia se chamar "Engine", a Application é um singleton (como só temos uma Application) que terá
	  suas janelas, seus sistemas de renderer e irá também distribuir os eventos que é recebido por meio de nossa janela.
	  Aqui também atualizaremos todos os sistemas e com isso daremos oportunidade ao App.cpp funcionar perfeitamente.
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
	protected:
		Window* m_Window;
	private:
		bool m_Running;
		LayerStack m_LayerStack;
		bool m_Minimized;
		DeltaTime deltaTime;
		bool wireframeMode = false;
		bool lockCursor = true;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
	};

	Application* CreateApplication();

}