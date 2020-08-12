#include "mcpch.h"
#include "VoxelTerrain.h"
#include "MCP/Noise/PerlinNoise.h"
#include "MCP/Renderer/Misc/PNGimageWriter.h"
#include "MCP/Utils/Logger.h"

namespace MC
{
	VoxelTerrain::VoxelTerrain()
	{
		superChunk = new Superchunk;
	}

	VoxelTerrain::~VoxelTerrain()
	{
		delete superChunk;
	}

	void VoxelTerrain::Gen3DNoiseTerrain(uint32_t xt, uint32_t yt, uint32_t zt, uint32_t octaves, float frequency, float persistence)
	{
	}
	void VoxelTerrain::Gen2DNoiseTerrain(uint32_t xt, uint32_t yt, uint32_t zt, uint32_t octaves, float frequency, float persistence)
	{
		PerlinNoise Noise;

		PNGimageWriter terrainPreview("terrainpreview.png", xt, yt);

		float xf = xt;
		float yf = yt;
		float should = 0.0f; //This will be part of the process to select which type of block will be spawned.
		//#TODO criar um enum e alternar os modos, melhor do que copiar codigo.
		for (int y = 0; y < yt; y++)
		{		
			for (int x = 0; x < xt; x++)
			{
				terrainPreview.Set(should);
				for (int z = 0; z <= zt; z++)
				{
					should = Noise.GenOctave(x / xf, y / yf, 0.0f, octaves, frequency, persistence);
					(should * yf) > y ? superChunk->Set(x, y, z, 1) : superChunk->Set(x, y, z, 0);
				}
			}
		}

		terrainPreview.Write();

		m_terrainPreviewTex = Texture2D(terrainPreview.GetData(), terrainPreview.getWidth(), terrainPreview.getHeight(), 1);
	}

	void VoxelTerrain::GenFlatTerrain(uint32_t xt, uint32_t yt, uint32_t zt)
	{
		for (int x = 0; x < xt; x++)
			for (int y = 0; y < yt; y++)
				for (int z = 0; z < zt; z++)		
						superChunk->Set(x, y, z, 1);	
	}
}