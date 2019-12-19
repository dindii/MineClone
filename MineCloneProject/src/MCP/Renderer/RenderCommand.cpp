#include "mcpch.h"
#include <glad/glad.h>
#include "RenderCommand.h"

namespace MC
{

	void RenderCommand::Clear(const bool& ColorBuffer /*= true*/, const bool& DepthBuffer /*= true*/)
	{
		if (ColorBuffer)
			glClear(GL_COLOR_BUFFER_BIT);

		if (DepthBuffer)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::SetClearColor(const vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

}