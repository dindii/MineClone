#include "mcpch.h"
#include "PerlinNoise1D.h"
#include <stdint.h>
#include <random>

namespace MC
{
	PerlinNoise1D::PerlinNoise1D(float Width)
	{
		nOutputSize = Width;
		fNoiseSeed1D = new float[nOutputSize];
		fPerlinNoise1D = new float[nOutputSize];

		for (uint32_t x = 0; x < nOutputSize; x++)
			fNoiseSeed1D[x] = (float)rand() / (float)RAND_MAX;

	}

	void PerlinNoise1D::GenPerlinNoise1D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput)
	{
		for (uint32_t x = 0; x < nWidth; x++)
			for (uint32_t y = 0; y < nHeight; y++)
		{
			float fNoise = 0.0f;
			float fScale = 1.0f;
			float fScaleAcc = 0.0f;
			float fScalingBias = 2.0f;


			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nWidth >> o;

				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
				int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScaleAcc += fScale;
				fScale = fScale / fBias;

			}

			fOutput[y * nWidth + x] = fNoise / fScaleAcc;
		}
	}

}