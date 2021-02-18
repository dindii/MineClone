#pragma once
#include "MCP/Renderer/Camera/Camera.h"

namespace MC
{
	struct Trace
	{
		static vec3 UnprojectCenterPixel(const Camera& camera);
	};

}