#include "mcpch.h"
#include "Camera.h"
#include "MCP/Maths/Maths.h"

namespace MC
{
	Camera::Camera(vec3 position) : m_Yaw(-90.0f), m_Pitch(0.0f), m_CameraUp({ 0.0f, 1.0f, 0.0f }), m_CameraTarget({ 0.0f, 0.0f, -1.0f }), m_CameraPosition(position), m_CameraSensitivity(0.1f),
		m_CameraSpeed(5.0f)
	{
		UpdateCameraVectors();
	}

	MC::mat4 Camera::getViewMatrix()
	{
		return mat4::LookAt(m_CameraPosition, m_CameraPosition + m_CameraTarget, m_CameraUp);
	}

	void Camera::UpdateCameraVectors()
	{

		vec3 Target; 

		Target.x = cos(toRadians(m_Pitch) * cos(toRadians(m_Yaw)));
		Target.y = sin(toRadians(m_Pitch));
		Target.z = cos(toRadians(m_Pitch) * sin(toRadians(m_Yaw)));

		m_CameraTarget = Target.Normalized();

		m_CameraRight = vec3::Normalize(vec3::Cross(m_CameraTarget, m_CameraUp));
		m_CameraUp = vec3::Normalize(vec3::Cross(m_CameraRight, m_CameraTarget));
	}

	//@TODO: SetPosition, Rotation/Pitch/Yaw, Translate, Mouse affecting the Yaw/Pitch
	// Talvez sobrecarregando os operadores * para o translate/rotate

}