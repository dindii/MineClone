#include "mcpch.h"
#include "Camera.h"
#include "MCP/Maths/Maths.h"
#include "MCP/Event/ApplicationEvent.h"
#include "MCP/Maths/mat4.h"
#include "MCP/Utils/Logger.h"
#include "MCP/IO/InputHandler.h"

namespace MC
{
	Camera::Camera(const float AR, const vec3& position) : m_Yaw(0.0f), m_Pitch(0.0f), m_CameraTarget({ 0.0f, 0.0f, -1.0f })
	{
		m_Projection =  mat4::Perspective(70.0f /*zoom*/, AR, 0.1f, 100.0f);

		m_CameraPos = position;
		UpdateCameraVectors();
	}


	const mat4 Camera::getViewMatrix() const
	{
		return m_ViewMatrix;
	}

	void Camera::UpdateCameraVectors()
	{
		mat4 m_CameraRotation, m_CameraPosition;

		m_CameraRotation = mat4::Rotate(m_Pitch, vec3(1.0f, 0.0f, 0.0f));
		m_CameraRotation *= mat4::Rotate(m_Yaw, vec3(0.0f, 1.0f, 0.0f));

		m_CameraPosition = mat4::Translate(-m_CameraPos);
	    
		m_ViewMatrix = m_CameraRotation * m_CameraPosition;
	}

	//For Free look fps camera
	void Camera::AddCameraTargetPosition(vec3 pos, DeltaTime& dt)
	{
		//@TODO: Translate no Y ao inves de atualizar o Up junto? 

		pos *= dt;

		MC::vec3 forward(m_ViewMatrix[2 + 0 * 4], m_ViewMatrix[2 + 1 * 4], m_ViewMatrix[2 + 2 * 4]);
		MC::vec3 strafe(m_ViewMatrix[0 + 0 * 4], m_ViewMatrix[0 + 1 * 4], m_ViewMatrix[0 + 2 * 4]);
		MC::vec3 up(m_ViewMatrix[1 + 0 * 4], m_ViewMatrix[1 + 1 * 4], m_ViewMatrix[1 + 2 * 4]);

		MC::vec3 target = m_CameraTarget;

		target += ((forward * pos.z) + (strafe * pos.x)) + (up * pos.y);

		m_CameraTarget = target;

		SetCameraPosition(m_CameraTarget);
	}

	void Camera::SetCameraPosition(vec3& pos)
	{
		if (m_CameraLag)
		{
			m_DesiredPos = pos;
			vec3 lerped = vec3::lerp(m_CameraPos, m_DesiredPos, m_LagVal); 

			UpdateCameraVectors();

			m_CameraPos = lerped;
		}
		else
		{
			m_CameraPos = pos;
			UpdateCameraVectors();
		}		
	}

	void Camera::SetProjection(float AR)
	{
		m_Projection = mat4::Perspective(70.0f /*zoom*/, AR, 0.5f, 100.0f);
	}

	void Camera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent Event) -> bool
		{
			SetProjection((float)(Event.GetWidth() / Event.GetHeight()));
			return false;
		});
	}

}