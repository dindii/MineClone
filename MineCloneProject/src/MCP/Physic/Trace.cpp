#include "mcpch.h"
#include "Trace.h"
#include "MCP/IO/InputHandler.h"
#include "MCP/Application.h"

namespace MC
{
	vec3 Trace::Cast(const Camera& camera)
	{
		mat4 projectionMatrix = camera.GetProjection();
		mat4 viewMatrix = camera.getViewMatrix();

		//SCREEN CORDS
		vec2 mousePos = InputHandler::GetMouseCoords();

		Application* app = Application::Get();

		float screenWidth = app->GetWindow().getWidth();
		float screenHeight = app->GetWindow().getHeight();

		//NDC
		float xNormalizedDeviceCoords = (2.0f * mousePos.x) / screenWidth - 1;
		float yNormalizedDeviceCoords = (2.0f * mousePos.y) / screenHeight - 1; //-Y if needed

		//CLIP COORDS
		vec4 clipCoords(xNormalizedDeviceCoords, yNormalizedDeviceCoords, -1.0f, 1.0f);

		//VIEW SPACE
		mat4 invertedProjection = projectionMatrix.Invert();
		vec4 viewCoords = invertedProjection * clipCoords;

		viewCoords = vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);

		//WORLD SPACE
		mat4 inversedView = viewMatrix.Invert();
		vec4 worldCoords = inversedView * viewCoords;

		vec3 ray(worldCoords.x, worldCoords.y, worldCoords.z);
		ray = ray.Normalized();

		return ray;

	}

}