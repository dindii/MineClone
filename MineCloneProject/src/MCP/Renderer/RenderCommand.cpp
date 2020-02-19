#include "mcpch.h"
#include "RenderCommand.h"
#include <glad/glad.h>


namespace MC
{

	void RenderCommand::Draw(Chunk* chunk, Shader* shader)
	{
		if (chunk->changed)
		{
			chunk->update();

			glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
			glBufferData(GL_ARRAY_BUFFER, chunk->elements * sizeof(chunk->vertex[0]), chunk->vertex, GL_STATIC_DRAW);
		}
		
		if (!chunk->elements)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, sizeof(uint8_t) * 4, (void*)0);

		shader->Bind();
		glDrawArrays(GL_TRIANGLES, 0, chunk->elements);
	}

	void RenderCommand::Clear(const bool& ColorBuffer /*= true*/, const bool& DepthBuffer /*= true*/)
	{
		if (ColorBuffer)
			glClear(GL_COLOR_BUFFER_BIT);

		if (DepthBuffer)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::SetClearColor(const vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	unsigned int RenderCommand::GenMesh(unsigned int nMeshes)
	{
		unsigned int VBO = 0;
		glGenBuffers(nMeshes, &VBO);

		return VBO;
	}

	void RenderCommand::DelMesh(unsigned int nMeshes, unsigned int& Mesh)
	{
		glDeleteBuffers(nMeshes, &Mesh);
	}

	void RenderCommand::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
	}

}