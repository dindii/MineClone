#pragma once

#include "MCP/Maths/vec4.h"
#include "MCP/Maths/mat4.h"
#include "Camera/Camera.h"

#include "MCP/Renderer/Voxel/Chunk.h"
#include "MCP/Renderer/Voxel/Superchunk.h"
#include "MCP/Renderer/Voxel/VoxelTerrain.h"
#include "MCP/Renderer/Texture2D.h"

namespace MC
{
	class VoxelRenderer
	{
	public:
		static void Draw(Chunk* chunk);
		static void Draw(Superchunk* superchunk);

		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetWireframeMode(bool cond);

		static int8_t AddTexture(const Texture2D* texture);
		static int8_t GetTexture(const Texture2D* texture);

		static void Init(); 
		static void ShutDown();

		//INFOS
		static uint32_t DrawnChunks;
		
	public:
	//private:
		struct VoxelRenderingResources
		{
			static const uint32_t MaxTextureSlots = 32;
			Shader voxelShader;
			uint32_t TextureSlotsIndex = 0;

			 const Texture2D* textures[MaxTextureSlots];

			 mat4* SceneActiveCamera;
			 mat4* SceneActiveProjection;
		
		};

		static VoxelRenderingResources* v_Data;
	};
}
