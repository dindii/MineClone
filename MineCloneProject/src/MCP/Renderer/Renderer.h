#pragma once

#include "MCP/Maths/vec4.h"
#include "MCP/Maths/mat4.h"
#include "Camera/Camera.h"

#include "MCP/Renderer/Voxel/Chunk.h"

namespace MC
{
	class Renderer
	{
	public:
		//static void Draw(Chunk); 
		static void Draw(Chunk* chunk, Shader* shader);
		static void BeginScene(const Camera& camera, const mat4& projection);

		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);

		static void Init(); // Load default values

	private:
		struct SceneData
		{
			mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}