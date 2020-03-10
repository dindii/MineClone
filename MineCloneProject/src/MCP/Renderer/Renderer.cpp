#include "mcpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace MC
{
	//@TODO: Maybe delete?
	Renderer::SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::Draw(Chunk* chunk, Shader* shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		RenderCommand::Draw(chunk, shader);
	}

	void Renderer::Draw(Superchunk* superchunk, Shader* shader)
	{

		for (int x = 0; x < SUPER_CHUNK_SIZE; x++)
			for (int y = 0; y < SUPER_CHUNK_SIZE; y++)
				for (int z = 0; z < SUPER_CHUNK_SIZE; z++)
					if (superchunk->c[x][y][z])
					{
						shader->Bind();
						mat4 model;
						model *= model.Translate(vec3(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE));
						shader->UploadUniformMat4("u_Transform", model);
						Draw(superchunk->c[x][y][z], shader);
					}
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetProjection() * camera.getViewMatrix();
	}

	void Renderer::Clear(const bool& ColorBuffer /*= true*/, const bool& DepthBuffer /*= true*/)
	{
		RenderCommand::Clear(ColorBuffer, DepthBuffer);
	}

	void Renderer::SetClearColor(const vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(x, y, width, height);
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

}