#include "mcpch.h"
#include "Utils.h"
#include "MCP/IO/InputHandler.h"
#include "MCP/Application.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/VoxelRenderer.h"

namespace MC
{
	MC::vec3 Utils::UnprojectCenterPixel(const Camera& camera)
	{
		mat4 projectionMatrix = camera.GetProjection();
		mat4 viewMatrix       = camera.getViewMatrix();

		MC::Application* app  = MC::Application::Get();

		//Screen actual width and height
		float width = app->GetWindow().getWidth();
		float height = app->GetWindow().getHeight();

		//middle screen fragment depth (0-1)
		float depth = MC::RenderCommand::GetPixelDepth(width / 2, height / 2, 1, 1);

		mat4 Inverse = mat4::Inverse(projectionMatrix * viewMatrix);

 		vec4 tmp = vec4(width, height, depth, 1.0f);

 		tmp.x    = (width  / 2) / width;
		tmp.y    = (height / 2) / height;
 		tmp      = (tmp * (2.0f)) - (1.0f);

		vec4 obj = Inverse * tmp;
		obj /= obj.w;

		return vec3(obj.x, obj.y, obj.z);
	}

}