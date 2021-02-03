#include "mcpch.h"
#include "AABB.h"

namespace MC
{
	MC::IntersectionInfo AABB::CheckIntersection(const AABB& other) const
	{
		vec3 distances1 = other.GetMinExtents() - m_maxExtents;
		vec3 distances2 =  m_minExtents - other.GetMaxExtents();

		vec3 distances = distances1.Max(distances2);

		float maxDistance = distances.Max();

		return IntersectionInfo(maxDistance < 0, maxDistance);
	}

}