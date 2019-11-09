#include "mcpch.h"
#include "Application.h"
#include "Utils/Logger.h"
#include "Core.h"
#include "IO/InputHandler.h"


//test
#include "Object/Mesh/MeshLoader.h"
#include <glad/glad.h>

namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		s_Instance = this;

		m_Window = new Window(1360, 720, "MClone!");

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		/*************** TEST ***************/
		//Since i don't have the renderer yet, i will be using this area to test my rendering fundamentals
		MC::Mesh mesh = MC::MeshLoader::loadOBJFile("D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\Object\\Mesh\\cube.obj");

		unsigned int meshSize = mesh.Data.size();
		unsigned int CubeVBO, CubeVAO, CubeEBO;

		//VAO Test
		glGenVertexArrays(1, &CubeVAO);
		glBindVertexArray(CubeVAO);
		
		//VBO Test
		glGenBuffers(1, &CubeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);


		glBufferSubData(GL_ARRAY_BUFFER, 0, meshSize * sizeof(vec3), &mesh.Data[0].Vertex);
		glBufferSubData(GL_ARRAY_BUFFER, meshSize * sizeof(vec3), meshSize * sizeof(vec3), &mesh.Data[0].Normal);
		glBufferSubData(GL_ARRAY_BUFFER, 2 * meshSize * sizeof(vec3), meshSize * sizeof(vec2), &mesh.Data[0].TextureCoods);

		//VBO Attribs
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vec3), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vec3), (void*)(meshSize * sizeof(vec3)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vec3), (void*)(meshSize * sizeof(vec3) + meshSize * sizeof(vec2)));

		//Element Buffer test
		glGenBuffers(1, &CubeEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), &mesh.indices, GL_STATIC_DRAW);
		
		//bind shader
		//create camera
		//bind uniforms
		//draw

		/*************** TEST ***************/
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
