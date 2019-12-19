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
		Camera(const vec3& position);
		Camera() = default;

		const mat4 getViewMatrix() const;


		void UpdateCameraVectors();

		void Translate(const vec3& vec);

		void CalculateViewMatrix();
	private:
		vec3 m_CameraPosition;
		vec3 m_CameraTarget;
		vec3 m_CameraUp;
		vec3 m_CameraRight;

	private:
		float m_CameraSensitivity, m_CameraSpeed;
		float m_Yaw, m_Pitch;

	private:
		mat4 m_ViewMatrix;
	};
}