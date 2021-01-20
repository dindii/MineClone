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
		BLOCK_WATER = 1,
		BLOCK_SAND,
		BLOCK_GRASS,
		BLOCK_DIRT,
		BLOCK_SNOW
	};

	VoxelTerrain::VoxelTerrain(uint32_t c_width, uint32_t c_height, uint32_t c_depth) : width(c_width), height(c_height), depth(c_depth),
		m_terrainPreviewTex(0, width, height, 1)
	{
		superChunk =   new Superchunk;
		AguaTextura =  new Texture2D("res/Textures/azul.png");
		AreiaTextura = new Texture2D("res/Textures/amarelo.png");
		GramaTextura = new Texture2D("res/Textures/verde.png");
		TerraTextura = new Texture2D("res/Textures/marrom.png");
		NeveTextura =  new Texture2D("res/Textures/branco.png");

	
	}

	VoxelTerrain::~VoxelTerrain()
	{
		delete AguaTextura;
		delete AreiaTextura;
		delete GramaTextura;
		delete TerraTextura;
		delete NeveTextura;
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
		
					
							 if ((should * yf) > y)
							 {
								 if      (should > 0.0f  &&  should < 0.4f)  superChunk->Set(x, y, z, BLOCK_WATER, AguaTextura);
								 else if (should > 0.4f  &&  should < 0.45f) superChunk->Set(x, y, z, BLOCK_SAND, AreiaTextura);
								 else if (should > 0.45f &&  should < 0.65f) superChunk->Set(x, y, z, BLOCK_GRASS, GramaTextura);
								 else if (should > 0.65f &&  should < 0.9f)  superChunk->Set(x, y, z, BLOCK_DIRT, TerraTextura);
								 else if (should > 0.9f  &&  should < 1.0f)  superChunk->Set(x, y, z, BLOCK_SNOW, NeveTextura);
							 }
							 else superChunk->Set(x, y, z, 0, nullptr);

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
					superChunk->Set(x, y, z, BLOCK_WATER, AguaTextura);


	}
}