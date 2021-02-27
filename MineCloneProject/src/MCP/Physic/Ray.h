#pragma once
#include "MCP/Renderer/Camera/Camera.h"
#include "MCP/Maths/vec3.h"
namespace MC
{
	class Trace
	{
	public:
		Trace(const float x, const float y, const Camera& camera);
		~Trace() = default;

		vec3 getDirection() const { return m_Coords; }


		static vec3 CastRay(const float x, const float y, const Camera& camera);


	private:
		vec3 m_Coords;
	};


}