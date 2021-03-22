#include "mcpch.h"
#include "RenderCommand.h"
#include <glad/glad.h>


namespace MC
{

	void RenderCommand::Draw(Chunk* chunk)
	{
		if (!chunk->VBO)
			chunk->VBO = GenMesh(1);

		if (chunk->changed)
		{
			chunk->update();

			glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
			glBufferData(GL_ARRAY_BUFFER, chunk->elements * sizeof(uint32_t), chunk->vertex, GL_STATIC_DRAW);
		}

		if (!chunk->elements)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
		glEnableVertexAttribArray(0);
		glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(uint32_t), 0);

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

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	unsigned int RenderCommand::GenMesh(unsigned int nMeshes)
	{
		unsigned int VBO = 0;
		glGenBuffers(nMeshes, &VBO);

		return VBO;
	}

	void RenderCommand::WireframeMode(bool cond)
	{
		if (cond)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void RenderCommand::DelMesh(unsigned int nMeshes, unsigned int& Mesh)
	{
		if (Mesh > 0)
		{
			glDeleteBuffers(nMeshes, &Mesh);
			Mesh = -1;
		}
		}

	float RenderCommand::GetPixelDepth(const uint32_t width, const uint32_t height, const uint32_t x, const uint32_t y)
	{
		float depth = 0;
		glReadPixels(width, height, x, y, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		return depth;
	}

	void RenderCommand::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

}