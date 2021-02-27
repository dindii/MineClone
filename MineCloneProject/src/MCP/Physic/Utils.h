#pragma once
#include "MCP/Renderer/Camera/Camera.h"

namespace MC
{
	struct Utils
	{
		static vec3 UnprojectCenterPixel(const Camera& camera);
	};

}