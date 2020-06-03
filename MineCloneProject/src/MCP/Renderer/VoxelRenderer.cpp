#include "mcpch.h"
#include "VoxelRenderer.h"
#include "RenderCommand.h"

namespace MC
{
	struct VoxelRenderingResources
	{
		Shader voxelShader;
	};

	static VoxelRenderingResources* v_Data;

	void VoxelRenderer::Init()
	{
		v_Data = new VoxelRenderingResources();
		v_Data->voxelShader.Init("res/Shaders/chunkVertex.shader", "res/Shaders/chunkFragment.shader");

		RenderCommand::Init();
	}

	void VoxelRenderer::ShutDown()
	{
		delete v_Data;
	}

	void VoxelRenderer::Draw(Chunk* chunk)
	{
		v_Data->voxelShader.Bind();
		RenderCommand::Draw(chunk);
	}

	void VoxelRenderer::Draw(Superchunk* superchunk, float arr[4][4][4])
	{
		uint32_t aux = 0; 

		for (int x = 0; x < SUPER_CHUNK_SIZE; x++)
			for (int y = 0; y < SUPER_CHUNK_SIZE; y++)
				for (int z = 0; z < SUPER_CHUNK_SIZE; z++)
					if (superchunk->c[x][y][z])
					{
						mat4 model;
						model *= model.Translate(vec3(0, 0, 0));
						v_Data->voxelShader.UploadUniformMat4("u_Transform", model);

						Draw(superchunk->c[0][0][0]);

						aux++;
					}
	}

	void VoxelRenderer::BeginScene(const Camera& camera)
	{
		v_Data->voxelShader.UploadUniformMat4("u_ViewProjection", (camera.GetProjection() * camera.getViewMatrix()));
	}

	void VoxelRenderer::Clear(const bool& ColorBuffer /*= true*/, const bool& DepthBuffer /*= true*/)
	{
		RenderCommand::Clear(ColorBuffer, DepthBuffer);
	}

	void VoxelRenderer::SetClearColor(const vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void VoxelRenderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(x, y, width, height);
	}

}