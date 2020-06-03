#pragma once

#include "MCP/Maths/vec4.h"
#include "MCP/Renderer/Voxel/Chunk.h"
#include "MCP/Renderer/Voxel/Superchunk.h"


namespace MC
{
	class RenderCommand
	{
	public:
		//@TODO: Draw based on VBO 
		static void Draw(Chunk* chunk);
		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static unsigned int GenMesh(unsigned int nMeshes);
		static void DelMesh(unsigned int nMeshes, unsigned int& Mesh);

		static void Init();
	};

}