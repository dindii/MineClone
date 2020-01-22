#pragma once

#include "MCP/Maths/vec4.h"
#include "MCP/Renderer/Voxel/Chunk.h"



namespace MC
{
	class RenderCommand
	{
	public:
		static void Draw(Chunk* chunk, Shader* shader);
		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);

		static unsigned int GenMesh(unsigned int nMeshes);
		static void DelMesh(unsigned int nMeshes, unsigned int& Mesh);

		static void Init();
	};

}