#include "mcpch.h"
#include "Application.h"
#include "Utils/Logger.h"
#include "Core.h"
#include "IO/InputHandler.h"


//test
#include "Object/Mesh/MeshLoader.h"
#include <glad/glad.h>
#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Renderer/Camera/Camera.h"

namespace MC
{

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Running(true)
	{
		s_Instance = this;

		m_Window = new Window(1360, 720, "MClone!");

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
		//Since i don't have the renderer yet, i will be using this area to test my rendering fundamentals
		 mesh = MC::MeshLoader::loadOBJFile("D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\Object\\Mesh\\cube.obj");
		 shader = new MC::Shader("D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testVertexShader.shader", "D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testFragmentShader.shader");

		 float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 

		-0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 

		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 

		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 

		-0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f, -0.5f, 

		-0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		 };

		 glGenVertexArrays(1, &CubeVAO);
		 glGenBuffers(1, &CubeVBO);

		 glBindVertexArray(CubeVAO);

		 glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
		 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		 // position attribute
		 glEnableVertexAttribArray(0);
		 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
	}

	Application::~Application()
	{
		delete m_Window;

		/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
		//@TODO: Remove
		delete shader;
		/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->onUpdate();	

			/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			mat4 proj = mat4::Perspective(45.0f, 1.8, 0.1f, 100.0f);
	
			mat4 transform;

			static float offsetest = 0.0f;
			offsetest += 0.01;
			
			transform *= mat4::Translate({ 0.0f, 0.0f, 0.0f });
			transform *= mat4::Rotate(offsetest *offsetest * offsetest, vec3(1.0f, 0.0f, 0.0f));

			Camera test({ 0.0f, 0.0f, 10.0f });

		
			mat4 viewproj = proj * test.getViewMatrix();


			shader->Bind();
			shader->UploadUniformMat4("u_ViewProjection", viewproj);
			shader->UploadUniformMat4("u_Transform", transform);


			glBindVertexArray(CubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, (void*)0);
			/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/


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
