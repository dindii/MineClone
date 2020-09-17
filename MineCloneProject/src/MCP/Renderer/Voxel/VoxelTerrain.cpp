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

	void VoxelTerrain::GenNoiseTerrain(TerrainType type, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset)
	{
		PerlinNoise Noise;

		PNGimageWriter terrainPreview("terrainpreview.png", width, height);

		float xf = (float)width;
		float yf = (float)height;
		float zf = (float)depth;

		float should = 0.0f; //This will be part of the process to select which type of block will be spawned.

		for (uint32_t x = 0; x < width; x++)
			for (uint32_t y = 0; y < height; y++)
			{

				if (type == TerrainType::Terrain2D)
					should = (float)Noise.GenOctave(x / xf, 0.0f, y / yf, octaves, frequency, persistence, xOffset, yOffset);
		
				 terrainPreview.Set(should);

				 for (uint32_t z = 0; z < depth; z++)
				 {
					 if (type == TerrainType::Terrain3D)
						 should = (float)Noise.GenOctave(x / xf, y / yf, z / zf, octaves, frequency, persistence, xOffset, yOffset);

					 //Only one type of block for now
					 (should * yf) > y ? superChunk->Set(x, y, z, 1) : superChunk->Set(x, y, z, 0);
				 }
			}

		terrainPreview.Write();
		m_terrainPreviewTex.SetData(terrainPreview.GetData());
	}

	void VoxelTerrain::GenFlatTerrain() const
	{
		for (uint32_t x = 0; x < width; x++)
			for (uint32_t y = 0; y < height; y++)
				for (uint32_t z = 0; z < depth; z++)
						superChunk->Set(x, y, z, 1);	
	}
}