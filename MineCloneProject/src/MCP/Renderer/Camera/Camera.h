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

		inline void SetCameraTarget(vec3& target) { m_CameraTarget = target; } 
		inline void SetCameraPosition(vec3& position) { m_CameraPosition = position; }
		inline void SetCameraYaw(float Yaw) { m_Yaw = Yaw; }
		inline void SetCameraPitch(float Pitch) { m_Pitch = Pitch; }
	
		inline vec3 GetCameraTarget() const { return m_CameraTarget; }
		inline vec3 GetCameraPosition() const { return m_CameraPosition; }
		inline vec3 GetCameraUp() const { return m_CameraUp; }
		inline vec3 GetCameraRight() const { return m_CameraRight; }
			 
		inline float GetCameraYaw() const { return m_Yaw; }
		inline float GetCameraPitch() const { return m_Pitch; }

		inline void SetViewMatrix(mat4& view) { m_ViewMatrix = view; }

	private:
		vec3 m_CameraPosition;
		vec3 m_CameraTarget;
		vec3 m_CameraUp;
		vec3 m_CameraRight;

	private:
		float m_CameraSensitivity, m_CameraSpeed;
		float m_Yaw, m_Pitch;

	private:
		mat4 position, rotation, scale;
		mat4 m_ViewMatrix;
	};
}