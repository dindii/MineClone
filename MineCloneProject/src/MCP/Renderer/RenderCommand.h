#pragma once

#include "MCP/Maths/vec4.h"

namespace MC
{
	class RenderCommand
	{
	public:
		static void Clear(const bool& ColorBuffer = true, const bool& DepthBuffer = true);
		static void SetClearColor(const vec4& color);
	};

}