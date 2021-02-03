#pragma once
#include "MCP/Maths/vec3.h"

namespace MC
{
	class IntersectionInfo
	{
	public:
		IntersectionInfo(const bool isIntersecting, const float howMuchIsIntersecting) :
			m_IsIntersecting(isIntersecting), m_HowMuchIsIntersecting(howMuchIsIntersecting) {};

		inline bool GetIsIntersecting() const { return m_IsIntersecting; }
		inline float GetHowMuchIsIntersecting() const { return m_HowMuchIsIntersecting; }


	private:
		const bool m_IsIntersecting;
		const float m_HowMuchIsIntersecting;
	};


	class AABB
	{
	public:

		AABB(const vec3& minExtents, const vec3& maxExtents) : m_minExtents(minExtents), m_maxExtents(maxExtents) {};

		IntersectionInfo CheckIntersection(const AABB& other) const;

		inline const vec3 GetMinExtents() const { return m_minExtents; }
		inline const vec3 GetMaxExtents() const { return m_maxExtents; }

	private:
		const vec3 m_minExtents, m_maxExtents;
	};

}