#pragma once
#include "Window.h"
#include "LayerStack.h"

//DEBUG
#include "Object/Mesh/MeshLoader.h"
#include "MCP/Renderer/Shader/Shader.h"
#include <memory>

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
	private:
		static Application* s_Instance;
	
	private:
		bool m_Running;
		Window* m_Window;
		LayerStack m_LayerStack;

		//DEBUG
	private:
		MC::Mesh mesh;
		MC::Shader* shader;
		unsigned int CubeVBO, CubeVAO, CubeEBO;
		unsigned int meshSize;
		//DEBUG
	};

	Application* CreateApplication();

}