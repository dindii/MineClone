#include "mcpch.h"
#include "VoxelRenderer.h"
#include "RenderCommand.h"

#include "MCP/Utils/Logger.h"
#include "MCP/Maths/Maths.h"

namespace MC
{	
	VoxelRenderer::VoxelRenderingResources* VoxelRenderer::v_Data;

	void VoxelRenderer::Init()
	{
		v_Data = new VoxelRenderingResources();
		v_Data->voxelShader.Init("res/Shaders/chunkVertex.shader", "res/Shaders/chunkFragment.shader");
		v_Data->voxelShader.Bind();

		int32_t samplers[v_Data->MaxTextureSlots];
	
		for (uint32_t x = 0; x < v_Data->MaxTextureSlots; x++)
			samplers[x] = x;
	
		v_Data->voxelShader.UploadIntArray("u_Textures", samplers, v_Data->MaxTextureSlots);
	
		for (uint32_t x = 0; x < v_Data->MaxTextureSlots; x++)
			v_Data->textures[x] = nullptr;

		RenderCommand::Init();
	}

	int8_t VoxelRenderer::AddTexture(const Texture2D* texture)
	{
		if (v_Data->TextureSlotsIndex >= v_Data->MaxTextureSlots)
		{
			MC_LOG_ERROR("Not enough texture slots remaining!");
			return 0;
		}
		
		v_Data->textures[v_Data->TextureSlotsIndex] = texture; 
		return v_Data->TextureSlotsIndex++;

	}

	int8_t VoxelRenderer::GetTexture(const Texture2D* texture)
	{
		int8_t textureIndex = -1;
		
		for (uint32_t x = 0; x <= v_Data->TextureSlotsIndex; x++)
		{
			if (v_Data->textures[x] && *v_Data->textures[x] == *texture)
			{
				textureIndex = x;
				return textureIndex;
			}
		}
		
		return textureIndex;

		
	}

	
	void VoxelRenderer::ShutDown()
	{
		delete v_Data;
	}

	void VoxelRenderer::Draw(Chunk* chunk)
	{
		RenderCommand::Draw(chunk);
	}

	void VoxelRenderer::Draw(Superchunk* superchunk)
	{
 		for (int x = 0; x < SUPER_CHUNK_SIZE; x++)
 			for (int y = 0; y < SUPER_CHUNK_SIZE; y++)
 				for (int z = 0; z < SUPER_CHUNK_SIZE; z++)
 				{
 					if (superchunk->c[x][y][z])
 					{
 						mat4 model;
 						model *= model.Translate(vec3(float(x * CHUNK_SIZE), float(y  * CHUNK_SIZE), float(z  * CHUNK_SIZE)));
 						v_Data->voxelShader.Bind();
 						v_Data->voxelShader.UploadUniformMat4("u_Transform", model);
 						Draw(superchunk->c[x][y][z]);
 					}
 				}
	}

	void VoxelRenderer::BeginScene(const Camera& camera)
	{
		for (int x = 0; x < v_Data->TextureSlotsIndex; x++)
		{
			v_Data->textures[x]->Bind(x);
		}

		v_Data->voxelShader.UploadUniformMat4("u_ViewProjection", (camera.GetProjection() * camera.getViewMatrix()));
	}

	void VoxelRenderer::EndScene()
	{
// 		for (int x = 0; x < v_Data->TextureSlotsIndex; x++)
// 		{
// 			v_Data->textures[x]->Bind(x);
// 		}

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

	void VoxelRenderer::SetWireframeMode(bool cond)
	{
		RenderCommand::WireframeMode(cond);
	}

}

//length height
//height depth
//length depth