#include "mcpch.h"
#include "Camera.h"
#include "MCP/Maths/Maths.h"

namespace MC
{
	Camera::Camera(const vec3& position) : m_Yaw(0), m_Pitch(0.0f), m_CameraTarget({ 0.0f, 0.0f, -1.0f })
	{
		m_CameraPosition = mat4::Translate(-position);
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

		m_CameraRotation = pitch * yaw;
	    
		m_ViewMatrix = m_CameraRotation * m_CameraPosition;
	}

	void Camera::AddCameraTargetPosition(vec3 pos)
	{
		//@TODO: Translate no Y ao inves de atualizar o Up junto? 

		MC::vec3 forward(m_ViewMatrix[2 + 0 * 4], m_ViewMatrix[2 + 1 * 4], m_ViewMatrix[2 + 2 * 4]);
		MC::vec3 strafe(m_ViewMatrix[0 + 0 * 4], m_ViewMatrix[0 + 1 * 4], m_ViewMatrix[0 + 2 * 4]);
		MC::vec3 up(m_ViewMatrix[1 + 0 * 4], m_ViewMatrix[1 + 1 * 4], m_ViewMatrix[1 + 2 * 4]);

		MC::vec3 target = m_CameraTarget;

		target += ((forward * -pos.z) + (strafe * pos.x)) + (up * pos.y);

		m_CameraTarget = target;

		m_CameraPosition = mat4::Translate(-m_CameraTarget);

		UpdateCameraVectors();
	}

	void Camera::SetCameraPosition(vec3& pos)
	{
		//I don't know if this will work good with fixed cameras (maybe yes) or fixed cameras that gets controlled (maybe not, but in this
		//case, should be better lerp using AddCameraTargetPosition, so the Up, Right and Forward vectors should be updated as well).

		m_CameraPosition = mat4::Translate(-pos);
		UpdateCameraVectors();
	}

}