#include "mcpch.h"
#include "VoxelTerrain.h"
#include "MCP/Noise/PerlinNoise.h"
#include "MCP/Renderer/Misc/PNGimageWriter.h"
#include "MCP/Utils/Logger.h"

namespace MC
{
	VoxelTerrain::VoxelTerrain(uint32_t c_width, uint32_t c_height, uint32_t c_depth) : width(c_width), height(c_height), depth(c_depth),
		m_terrainPreviewTex(0, width, height, 1)
	{
		superChunk = new Superchunk;
	}

	VoxelTerrain::~VoxelTerrain()
	{
		delete superChunk;
	}

	void VoxelTerrain::GenNoiseTerrain(uint32_t octaves, float frequency, float persistence, TerrainType type)
	{
		PerlinNoise Noise;

		PNGimageWriter terrainPreview("terrainpreview.png", width, height);

		float xf = width;
		float yf = height;
		float zf = depth;

		float should = 0.0f; //This will be part of the process to select which type of block will be spawned.

		for (int y = 0; y < height; y++)
		{		
			for (int x = 0; x < width; x++)
			{
				terrainPreview.Set(should);

				for (int z = 0; z <= depth; z++)
				{	
					if(type == TerrainType::Terrain2D)
						should = Noise.GenOctave(x / xf, y / yf, 0.0f, octaves, frequency, persistence);
					else if (type == TerrainType::Terrain3D)
						should = Noise.GenOctave(x / xf, y / yf, z / zf, octaves, frequency, persistence);

					(should * xf) > y ? superChunk->Set(x, y, z, 1) : superChunk->Set(x, y, z, 0);
				}
			}
		}

		terrainPreview.Write();

		m_terrainPreviewTex.SetData((void*)terrainPreview.GetData());
	}

	void VoxelTerrain::GenFlatTerrain()
	{
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
				for (int z = 0; z < depth; z++)		
						superChunk->Set(x, y, z, 1);	
	}
}