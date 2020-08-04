#pragma once
#include <stdint.h>

namespace MC
{

	class PerlinNoise
	{
	public:
		PerlinNoise();

		//For 3D
		double Gen(double x, double y, double z);
		double GenOctave(double x, double y, double z, int octaves, double frequency, double persistence);
	private:
		double fade(double t);
		int inc(int num);

		//3D
		double grad(int hash, double x, double y, double z);
	private:
		uint32_t permutation[512];
	};


}