#include "mcpch.h"
#include "Ray.h"
#include "MCP/Application.h"

namespace MC
{

	Trace::Trace(const float x, const float y, const Camera& camera)
	{
		m_Coords = Trace::CastRay(x, y, camera);
	}

	MC::vec3 Trace::CastRay(const float xCoord, const float yCoord, const Camera& camera)
	{
		Application* app = Application::Get();

		//Screen Coords |   0:width, 0:height
		float width =  (float)app->GetWindow().getWidth();
		float height = (float)app->GetWindow().getHeight();

		//Convert to NDC | -1:1, -1:1, -1:1
		float x = (2.0f * xCoord) / width - 1.0f;
		float y = 1.0f - (2.0f * yCoord) / height; //- 1.0f;
		float z = 1.0f;

		vec3 ray_NormalizedDeviceCoords(x, y, z);

		//Convert to Homogeneous Clíp Coordinates | -1:1, -1:1, -1:1
		vec4 ray_ClipCoords(ray_NormalizedDeviceCoords.x, ray_NormalizedDeviceCoords.y, -1.0f, 1.0f);
		//OBS: Test without needing to reverse perspective division. Keep in mind we may need reverse it in some point.

		//Convert to View (camera/eye) Space | -x:x, -y:y, -z:z
		vec4 ray_ViewSpace = mat4::Inverse(camera.GetProjection()) * ray_ClipCoords;

		//Not necessary but in order to be more generic, i will leave this here.
	//	ray_ViewSpace /= ray_ViewSpace.w;

		//We only need the x, y, depth values we will set further
		ray_ViewSpace = vec4(ray_ViewSpace.x, ray_ViewSpace.y, -1.0f, 0.0f);

		//Convert to World Space -x:x, -y:y, -z:z
		vec3 ray_WorldSpace = (mat4::Inverse(camera.getViewMatrix()) * ray_ViewSpace);

		ray_WorldSpace = vec3::Normalize(ray_WorldSpace);

		return ray_WorldSpace;
	}

}