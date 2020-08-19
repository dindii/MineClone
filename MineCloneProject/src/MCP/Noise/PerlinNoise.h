#pragma once
#include <stdint.h>

namespace MC
{

	struct PerlinParams
	{
		PerlinParams(uint32_t c_octaves, float c_frequency, float c_persistence, float c_xOffset, float c_yOffset, float c_zOffset) :
			frequency(c_frequency), persistence(c_persistence), xOffset(c_xOffset), yOffset(c_yOffset), zOffset(c_zOffset) {};

		uint32_t octaves = 1;
		float frequency = 0.01f;
		float persistence = 0.1f;
		float xOffset = 0.0f, yOffset = 0.0f, zOffset = 0.0f;
	};

	class PerlinNoise
	{
	public:
		PerlinNoise();

		//For 3D
		double Gen(double x, double y, double z) const;
		double GenOctave(double x, double y, double z, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset) const;
	private:
		double fade(double t) const;
		int inc(int num) const;

		//3D
		double grad(int hash, double x, double y, double z) const;
	private:
		uint32_t permutation[512];
	};


}