#pragma once

namespace MC
{
	class PerlinNoise1D
	{
	public:
		PerlinNoise1D(float Width);

		static void GenPerlinNoise1D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);

	private:
		float* fNoiseSeed1D = nullptr;
		float* fPerlinNoise1D = nullptr;
		int nOutputSize = 256;
	};
}