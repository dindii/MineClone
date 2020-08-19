#pragma once

#include "MCP/Maths/vec4.h"
#include "MCP/Maths/mat4.h"
#include "Camera/Camera.h"

#include "MCP/Renderer/Voxel/Chunk.h"
#include "MCP/Renderer/Voxel/Superchunk.h"
#include "MCP/Renderer/Voxel/VoxelTerrain.h"

namespace MC
{
	class VoxelRenderer
	{
	public:
		static void Draw(Chunk* chunk);
		static void Draw(Superchunk* superchunk);

		static void BeginScene(const Camera& camera);

		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetWireframeMode(bool cond);

		static void Init(); 
		static void ShutDown();
	};
}
