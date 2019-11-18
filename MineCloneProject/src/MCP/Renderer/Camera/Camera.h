#pragma once
#include "MCP/Maths/mat4.h"

namespace MC
{
	//@TODO: Switch mode para alternar entre a criação de uma câmera perspectiva ou ortográfica.
	//@TODO: Mudar para quarternions
	
	/*    Very Primitive Camera */
	class Camera
	{
	public:
		Camera(vec3 position = vec3(0.0f, 0.0f, -0.1f));

		mat4 getViewMatrix();
		void UpdateCameraVectors();

	private:
		vec3 m_CameraPosition;
		vec3 m_CameraTarget;
		vec3 m_CameraUp;
		vec3 m_CameraRight;

	private:
		float m_CameraSensitivity, m_CameraSpeed;
		float m_Yaw, m_Pitch;
	};
}