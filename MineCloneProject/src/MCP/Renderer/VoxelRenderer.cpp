#include "mcpch.h"
#include "VoxelRenderer.h"
#include "RenderCommand.h"

#include "MCP/Utils/Logger.h"
#include "MCP/Maths/Maths.h"

namespace MC
{	
	VoxelRenderer::VoxelRenderingResources* VoxelRenderer::v_Data;

	//#TODO: wrap in render stats
	uint32_t VoxelRenderer::DrawnChunks = 0;

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

		RenderCommand::SetClearColor({0.6f, 0.8f, 1.0f, 1.0f});

		v_Data->SceneActiveCamera     = new mat4();
		v_Data->SceneActiveProjection = new mat4();
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
		delete v_Data->SceneActiveCamera;
		delete v_Data->SceneActiveProjection;
		delete v_Data;
	}

	void VoxelRenderer::Draw(Chunk* chunk)
	{

		RenderCommand::Draw(chunk);

		DrawnChunks++;
	}

	void VoxelRenderer::Draw(ChunkManager* superchunk)
	{
 		for (int x = 0; x < SUPER_CHUNK_SIZE; x++)
 			for (int y = 0; y < SUPER_CHUNK_SIZE; y++)
 				for (int z = 0; z < SUPER_CHUNK_SIZE; z++)
 				{
 					if (superchunk->c[x][y][z])
 					{
 						mat4 model;
 						model = model.Translate(vec3(float((x)* CHUNK_SIZE), float((y)* CHUNK_SIZE), float((z)* CHUNK_SIZE)));
					

						//MVP matrix
						mat4 mvp = (*v_Data->SceneActiveProjection) * (*v_Data->SceneActiveCamera) * model;
			

						//generic chunk center in the world
						vec4 center = mvp * vec4((CHUNK_SIZE / 2), (CHUNK_SIZE / 2), (CHUNK_SIZE / 2), 1.0f);

						float distance = vec3::Length({ center.x, center.y, center.z });

						//center of the particular chunk in NDC
						center.x /= center.w;
						center.y /= center.w;
 
						//if the chunk is behind the camera, don't render it
						if (center.z < (-CHUNK_SIZE / 1.5f))
							continue;

						//if the chunk is out of the camera bounds + margin, don't render it
						if (fabsf(center.x) > 1 + fabsf(CHUNK_SIZE * 2 / center.w) || fabsf(center.y) > 1 + fabsf(CHUNK_SIZE * 2 / center.w))
							continue;
 
						//render distance 
						if (distance > 200.0f)
							continue;

 						v_Data->voxelShader.Bind();
 						v_Data->voxelShader.UploadUniformMat4("u_Transform", model);
 
 						Draw(superchunk->c[x][y][z]);
 					}
 				}
	}

	void VoxelRenderer::BeginScene(const Camera& camera)
	{
		for (uint8_t x = 0; x < v_Data->TextureSlotsIndex; x++)
			v_Data->textures[x]->Bind(x);
		

		v_Data->voxelShader.UploadUniformMat4("u_ViewProjection", (camera.GetProjection() * camera.getViewMatrix()));

		//Culling
		*(v_Data->SceneActiveCamera) = camera.getViewMatrix();
		*(v_Data->SceneActiveProjection) = camera.GetProjection();
	}

	void VoxelRenderer::EndScene()
	{
// 		for (int x = 0; x < v_Data->TextureSlotsIndex; x++)
// 		{
// 			v_Data->textures[x]->Bind(x);
// 		}
		DrawnChunks = 0;
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