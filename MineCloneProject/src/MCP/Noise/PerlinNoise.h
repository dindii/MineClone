#pragma once
#include <stdint.h>

namespace MC
{
	class PerlinNoise
	{
	public:
		PerlinNoise();

		//For 3D
		float Gen(const float x, const float y, const float z) const;
		float GenOctave(const float x, const float y, const float z, const uint32_t octaves, float frequency, const float persistence, const float xOffset, const float yOffset) const;
	private:
		float fade(const float t) const;
		int inc(int num) const;

		//3D
		float grad(int hash, const float x, const float y, const float z) const;
	private:
		uint32_t permutation[512];
	};


}