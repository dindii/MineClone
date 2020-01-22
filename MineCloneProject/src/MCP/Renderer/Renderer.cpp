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

	void Renderer::BeginScene(const Camera& camera, const mat4& projection)
	{
		m_SceneData->ViewProjectionMatrix = projection * camera.getViewMatrix();
	}

	void Renderer::Clear(const bool& ColorBuffer /*= true*/, const bool& DepthBuffer /*= true*/)
	{
		RenderCommand::Clear(ColorBuffer, DepthBuffer);
	}

	void Renderer::SetClearColor(const vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

}