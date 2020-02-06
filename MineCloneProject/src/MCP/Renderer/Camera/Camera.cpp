#include "mcpch.h"
#include "Camera.h"
#include "MCP/Maths/Maths.h"

namespace MC
{
	Camera::Camera(const vec3& position) : m_Yaw(0), m_Pitch(0.0f), m_CameraTarget({ 0.0f, 0.0f, -1.0f }), m_CameraPosition(position), m_CameraSensitivity(0.1f),
		m_CameraSpeed(5.0f)
	{
		UpdateCameraVectors();
	}

	const mat4 Camera::getViewMatrix() const
	{
		return m_ViewMatrix;
	}

	void Camera::UpdateCameraVectors()
	{
		mat4 yaw;
		mat4 pitch;

		pitch = mat4::Rotate(m_Pitch, vec3(1.0f, 0.0f, 0.0f));
		yaw = mat4::Rotate(m_Yaw, vec3(0.0f, 1.0f, 0.0f));

		rotation = pitch * yaw;

		position = mat4::Translate(-m_CameraTarget);
	    
		m_ViewMatrix = rotation * position;
	}
}