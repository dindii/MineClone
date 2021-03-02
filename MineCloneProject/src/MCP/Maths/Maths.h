#pragma once
#include "mcpch.h"
#include <stdint.h>
#define MC_PI 3.14159265359

namespace MC
{
	inline int clamp(const int min, const int max,  const int val)
	{
		int aux = 0;

		if (val < min)
		{
			aux = min;
			return aux;
		}
		else if (val > max)
		{
			aux = max;
			return aux;
		}

		return val;
	}

	inline uint8_t floatToByte(const float f)
	{
		return (f >= 1.0f ? 255 : (f <= 0.0f ? 0 : (int)floor(f * 256.0f)));
	}

	inline float normalizeInRange(float val, float max, float min)
	{
		return (val - min) / (max - min);
	}

	inline float toDegrees(const float radians) 
	{
		return (float)(radians * (180.0f / MC_PI));
	}

	inline float toRadians(const float degrees)
	{
		return (float)(degrees * (MC_PI / 180.0f));
	}

	inline float tan(const float angle)
	{
		return ::tan(angle);
	}

	inline float cos(const float angle)
	{
		return ::cos(angle);
	}

	inline float sin(const float angle)
	{
		return ::sin(angle);
	}

	inline float lerp(const float start, const float end, float alpha)
	{
		 return ((start * (1.0f - alpha)) + (end * alpha));	
	}

	inline float floorf(const float val)
	{
		return ::floorf(val);
	}

	inline float fabsf(const float val)
	{
		return ::fabsf(val);
	}

	inline float roundf(const float val)
	{
		return ::roundf(val);
	}

	//distance from an integer
	inline float dti(float val)
	{
		return fabsf(val - roundf(val));
	}
	//Module for doubles
	template<typename T, typename U>
	constexpr double dmod(T x, U mod)
	{
		return !mod ? x : x - mod * static_cast<long long>(x / mod);
	}



}