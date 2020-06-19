#pragma once
#include <stdint.h>

namespace MC
{

	class PerlinNoise
	{
	public:
		PerlinNoise();
		double Gen(double x, double y, double z);
		double GenOctave(double x, double y, double z, int octaves, double frequency, double persistence);
	private:
		double fade(double t);
		int inc(int num);
		double grad(int hash, double x, double y, double z);
	private:
		uint32_t permutation[512];
		bool repeat;
	};


}