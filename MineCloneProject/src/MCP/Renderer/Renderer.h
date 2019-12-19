#pragma once

#include "MCP/Maths/vec4.h"
#include "mcp/Maths/mat4.h"
#include "Camera/Camera.h"

namespace MC
{
	class Renderer
	{
	public:
		//static void Draw(); Blocks/Chunks
		static void BeginScene(const Camera& camera, const mat4& projection);
		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);

	private:
		struct SceneData
		{
			mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}