#include "mcpch.h"
#include "VoxelTerrain.h"
#include "MCP/Noise/PerlinNoise.h"
#include "MCP/Renderer/Misc/PNGimageWriter.h"
#include "MCP/Utils/Logger.h"

#include "MCP/Renderer/Texture2D.h"

namespace MC
{
	enum EBlockColor : uint8_t
	{
		BLOCK_AIR = 0,
		BLOCK_WATER,
		BLOCK_SAND,
		BLOCK_GRASS,
		BLOCK_DIRT,
		BLOCK_SNOW,
		BLOCK_STONE,
		BLOCK_WOOD
	};

	VoxelTerrain::VoxelTerrain(uint32_t c_width, uint32_t c_height, uint32_t c_depth) : width(c_width), height(c_height), depth(c_depth),
		m_terrainPreviewTex(0, width, height, 1)
	{
		superChunk   = new Superchunk;

		WaterTexture = new Texture2D("res/Textures/azul.png");
		SandTexture  = new Texture2D("res/Textures/sand.png");
		SnowTexture  = new Texture2D("res/Textures/branco.png");
		StoneTexture = new Texture2D("res/Textures/stone.png");
		DirtTexture  = new Texture2D("res/Textures/dirt/dirt.png");
		WoodTexture  = new Texture2D("res/Textures/wood/oak_wood.png");

		GrassTexture = new BlockTexture2D
		   ("res/Textures/grass/grass_side.png"  ,
			"res/Textures/grass/grass_side.png"  ,
			"res/Textures/grass/grass_top.png"   ,
			"res/Textures/grass/grass_bottom.png",
			"res/Textures/grass/grass_side.png"  ,
			"res/Textures/grass/grass_side.png");

	}

	VoxelTerrain::~VoxelTerrain()
	{
		delete WaterTexture;
		delete SandTexture;
		delete SnowTexture;
		delete DirtTexture;
		delete WoodTexture;
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
				{
					for (uint32_t y = 0; y < height; y++)
					{

						if (type == TerrainType::Terrain2D)
							should = (float)Noise.GenOctave(x / xf, 0.0f, y / yf, octaves, frequency, persistence, xOffset, yOffset);

						terrainPreview.Set(y, x, should);

						for (uint32_t z = 0; z < depth; z++)
						{
							if (type == TerrainType::Terrain3D)
								should = (float)Noise.GenOctave(x / xf, y / yf, z / zf, octaves, frequency, persistence, xOffset, yOffset);


							if ((should * yf) > y)
							{
								if (should > 0.0f  &&  should < 0.4f)  superChunk->Set(x, y, z, BLOCK_WATER, WaterTexture);
								else if (should > 0.4f  &&  should < 0.45f) superChunk->Set(x, y, z, BLOCK_SAND, SandTexture);
								else if (should > 0.45f &&  should < 0.60f) superChunk->Set(x, y, z, BLOCK_GRASS, GrassTexture);
								else if (should > 0.60f &&  should < 0.8f)  superChunk->Set(x, y, z, BLOCK_STONE, StoneTexture);
								else if (should > 0.8f  &&  should < 1.0f)  superChunk->Set(x, y, z, BLOCK_SNOW, SnowTexture);
							}

							//#TODO: Unset
							else superChunk->Set(x, y, z, BLOCK_AIR, WaterTexture);
						}
					}
				}
		
		terrainPreview.Write();
		m_terrainPreviewTex.SetData(terrainPreview.GetData());
	}

	void VoxelTerrain::GenFlatTerrain() const
	{
			for (uint32_t y = 0; y < height; y++)
				for (uint32_t z = 0; z < depth; z++)
					for(uint32_t x = 0; x<width; x++)
					superChunk->Set(x, y, z, BLOCK_WATER, WaterTexture);
	}

	
	bool VoxelTerrain::ValidateBlock(const uint8_t x, const uint8_t y, const uint8_t z)
	{
		if ((x < 0 || y < 0 || z < 0) || (x > width || y > height || z > depth))
			return false;

		return true;
	}

	void VoxelTerrain::RemoveBlock(uint8_t x, uint8_t y, uint8_t z)
	{
		if (!ValidateBlock(x, y, z))
			return;

		superChunk->Set(x, y, z, BLOCK_AIR, WaterTexture);
	}

	//#TODO: a block selector, maybe a map
	void VoxelTerrain::PlaceBlock(uint8_t x, uint8_t y, uint8_t z)
	{
		if (!ValidateBlock(x, y, z))
			return;

		superChunk->Set(x, y, z, BLOCK_WOOD, WoodTexture);
	}

}