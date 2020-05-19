#pragma once
#include "mcpch.h"

#define ED_PI 3.14159265359

namespace MC
{
	inline float normalizeInRange(float val, float max, float min)
	{
		return (val - min) / (max - min);
	}

	inline float toDegrees(const float& radians) 
	{
		return (float)(radians * (180.0f / ED_PI));
	}

	inline float toRadians(const float& degrees)
	{
		return (float)(degrees * (ED_PI / 180.0f));
	}

	inline float tan(const float& angle)
	{
		return ::tan(angle);
	}

	inline float cos(const float& angle)
	{
		return ::cos(angle);
	}

	inline float sin(const float& angle)
	{
		return ::sin(angle);
	}

}