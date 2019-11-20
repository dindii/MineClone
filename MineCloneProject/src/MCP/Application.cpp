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
		 //shader = MC::Shader("D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testVertexShader.shader", "D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testFragmentShader.shader");

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
		

// 		//VAO Test
// 		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 		glGenVertexArrays(1, &CubeVAO);
// 		glBindVertexArray(CubeVAO);
// 
// 		//VBO Test
// 		glGenBuffers(1, &CubeVBO);
// 		glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
// 
// 
// 		glBufferSubData(GL_ARRAY_BUFFER, 0, meshSize * sizeof(vec3), &mesh.Data[0].Vertex);
// 		glBufferSubData(GL_ARRAY_BUFFER, meshSize * sizeof(vec3), meshSize * sizeof(vec3), &mesh.Data[0].Normal);
// 		glBufferSubData(GL_ARRAY_BUFFER, 2 * meshSize * sizeof(vec3), meshSize * sizeof(vec2), &mesh.Data[0].TextureCoods);
// 
// 		//VBO Attribs
// 		glEnableVertexAttribArray(0);
// 		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vec3), (void*)0);
// 		glEnableVertexAttribArray(1);
// 		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vec3), (void*)(meshSize * sizeof(vec3)));
// 		glEnableVertexAttribArray(2);
// 		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vec3), (void*)(meshSize * sizeof(vec3) + meshSize * sizeof(vec2)));
// 
// 		//Element Buffer test
// 		glGenBuffers(1, &CubeEBO);
// 		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeEBO);
// 		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), &mesh.indices, GL_STATIC_DRAW);
// 		// 		

		

		//glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, (void*)0);




		/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
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

				/*************** TEST ***************/	/*************** TEST ***************/	/*************** TEST ***************/
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			MC::Shader shader("D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testVertexShader.shader", "D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testFragmentShader.shader");

			mat4 proj = mat4::Perspective(45.0f, 1.8, 0.1f, 100.0f);
	
			mat4 transform;

			static float offsetest = 0.0f;
			offsetest += 0.01;
			
			//@TODO: Descobrir o porquê UpdateCameraVectors está distorcendo a cena.
			transform *= mat4::Translate({ 0.0f, 0.0f, 0.0f });
			transform *= mat4::Rotate(offsetest *offsetest * offsetest, vec3(1.0f, 0.0f, 0.0f));

			Camera test({ 0.0f, 0.0f, 3.0f });

		
			mat4 viewproj = proj * test.getViewMatrix();


			shader.Bind();
			shader.UploadUniformMat4("u_ViewProjection", viewproj);
			shader.UploadUniformMat4("u_Transform", transform);


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
