#pragma once

#include "MCP/Maths/vec4.h"
#include "MCP/Maths/mat4.h"
#include "Camera/Camera.h"

#include "MCP/Renderer/Voxel/Chunk.h"
#include "MCP/Renderer/Voxel/Superchunk.h"

namespace MC
{
	class VoxelRenderer
	{
	public:
		static void Draw(Chunk* chunk);
		
		//Debug // Testar enviar um uniform por draw call pra usar o perlin e depois começar a instanciar todo o array de perlin.
		//Colocar esse array sendo 4*4*4 e fazer as operações dentro dele mesmo.
		static void Draw(Superchunk* superchunk, float arr[4][4][4]);

		static void BeginScene(const Camera& camera);

		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetWireframeMode(bool cond);

		static void Init(); 
		static void ShutDown();
	};
}
