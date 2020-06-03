#pragma once
#include "MCP/Maths/mat4.h"
#include "MCP/Event/Event.h"
#include "MCP/Platform/DeltaTime.h"
namespace MC
{
	//@TODO: Switch mode para alternar entre a criação de uma câmera perspectiva ou ortográfica.
	//@TODO: Mudar para quarternions
	//@TODO: Um modo para LookAt!
	//@TODO: Camera Controller
	
	///@TODO: Derivar uma classe FPSCamera ou TPSCamera etc, assim a camera não fica tão presa apenas ao freelook. 

	/*    Very Primitive Camera */

	class Camera
	{
	public:
		Camera(const float AR, const vec3& position);
		Camera() : m_Yaw(0.0f), m_Pitch(0.0f) {};

		const mat4 getViewMatrix() const;


		void UpdateCameraVectors();

		void AddCameraTargetPosition(vec3 pos, DeltaTime& dt);

		inline void SetCameraTarget(vec3& target) { m_CameraTarget = target; } 
		void SetCameraPosition(vec3& position);
		inline void SetCameraYaw(float Yaw) { UpdateCameraVectors(); m_Yaw = Yaw; }
		inline void SetCameraPitch(float Pitch) { UpdateCameraVectors(); m_Pitch = Pitch; }
	
		inline vec3 GetCameraTarget() const { return m_CameraTarget; }
		inline vec3 GetCameraUp() const { return m_CameraUp; }
		inline vec3 GetCameraRight() const { return m_CameraRight; }
		inline vec3 GetCameraPos() const { return m_CameraPos; }
			 
		inline float GetCameraYaw() const { return m_Yaw; }
		inline float GetCameraPitch() const { return m_Pitch; }

		inline mat4 GetProjection() const { return m_Projection; }
		inline void SetProjection(float AR);

		inline void SetViewMatrix(mat4& view) { m_ViewMatrix = view; }

		inline void SetLagVal(float& val) { m_CameraLag = val; }


		void OnEvent(Event& e);

	private:
		vec3  m_DesiredPos;
		bool  m_CameraLag = true;
		float m_LagVal;

	private:
		vec3 m_CameraTarget;
		vec3 m_CameraUp;
		vec3 m_CameraRight;
		vec3 m_CameraPos;

	private:
		float m_Yaw, m_Pitch;

	private:
		mat4 m_ViewMatrix, m_Projection;
	};
}