#include "mcpch.h"
#include "VoxelTerrain.h"
#include "MCP/Noise/PerlinNoise.h"
#include "MCP/Renderer/Misc/PNGimageWriter.h"
#include "MCP/Utils/Logger.h"

#include "MCP/Renderer/Texture2D.h"
#include "MCP/Utils/RandomNumberGenerator.h"

VoxelTerrain::VoxelTerrain(uint32_t c_width, uint32_t c_height, uint32_t c_depth) : width(c_width), height(c_height), depth(c_depth),
	m_terrainPreviewTex(0, width, height, 1)
{
	superChunk   = new MC::ChunkManager;

	m_TerrainTextures[EBlockType::BLOCK_WATER] = new MC::BlockTexture2D("res/Textures/azul.png");
	m_TerrainTextures[EBlockType::BLOCK_SAND]  = new MC::BlockTexture2D("res/Textures/sand.png");
	m_TerrainTextures[EBlockType::BLOCK_SNOW]  = new MC::BlockTexture2D("res/Textures/branco.png");
	m_TerrainTextures[EBlockType::BLOCK_STONE] = new MC::BlockTexture2D("res/Textures/stone.png");
	m_TerrainTextures[EBlockType::BLOCK_DIRT]  = new MC::BlockTexture2D("res/Textures/dirt/dirt.png");
	m_TerrainTextures[EBlockType::BLOCK_WOOD]  = new MC::BlockTexture2D("res/Textures/wood/oak_wood.png");

	m_TerrainTextures[EBlockType::BLOCK_GRASS] = new MC::BlockTexture2D
													                   ("res/Textures/grass/grass_side.png",
													                   "res/Textures/grass/grass_side.png",
													                   "res/Textures/grass/grass_top.png",
													                   "res/Textures/grass/grass_bottom.png",
													                   "res/Textures/grass/grass_side.png",
													                   "res/Textures/grass/grass_side.png");

	m_TerrainTextures[EBlockType::BLOCK_BLACK_WOOL     ] = new MC::BlockTexture2D("res/Textures/wool/black_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_BLUE_WOOL      ] = new MC::BlockTexture2D("res/Textures/wool/blue_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_BROWN_WOOL     ] = new MC::BlockTexture2D("res/Textures/wool/brown_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_CYAN_WOOL      ] = new MC::BlockTexture2D("res/Textures/wool/cyan_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_GRAY_WOOL      ] = new MC::BlockTexture2D("res/Textures/wool/gray_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_GREEN_WOOL     ] = new MC::BlockTexture2D("res/Textures/wool/green_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_LIGHT_BLUE_WOOL] = new MC::BlockTexture2D("res/Textures/wool/light_blue_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_LIGHT_GRAY_WOOL] = new MC::BlockTexture2D("res/Textures/wool/light_gray_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_LIME_WOOL      ] = new MC::BlockTexture2D("res/Textures/wool/lime_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_MAGENTA_WOOL   ] = new MC::BlockTexture2D("res/Textures/wool/magenta_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_ORANGE_WOOL    ] = new MC::BlockTexture2D("res/Textures/wool/orange_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_PINK_WOOL      ] = new MC::BlockTexture2D("res/Textures/wool/pink_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_PURPLE_WOOL    ] = new MC::BlockTexture2D("res/Textures/wool/purple_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_RED_WOOL       ] = new MC::BlockTexture2D("res/Textures/wool/red_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_WHITE_WOOL     ] = new MC::BlockTexture2D("res/Textures/wool/white_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_YELLOW_WOOL    ] = new MC::BlockTexture2D("res/Textures/wool/yellow_wool.png");
}

VoxelTerrain::~VoxelTerrain()
{
	for (uint16_t x = 0; x < m_TerrainTextures.size(); x++)
		delete m_TerrainTextures[(EBlockType)x];
}

void VoxelTerrain::GenNoiseTerrain(TerrainType type, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset)
{
	MC::PerlinNoise Noise;
	
	MC::PNGimageWriter terrainPreview("terrainpreview.png", width, height);
	
	float xf = (float)width;
	float yf = (float)height;
	float zf = (float)depth;
	
	float should = 0.0f; //This will be part of the process to select which type of block will be spawned.
	
	for (uint32_t x = 0; x < width; x++)
	{
		for (uint32_t y = 0; y < height; y++)
		{

			if (type == TerrainType::Terrain2D)
				should = (float)Noise.GenOctave(x / xf, 0.0f, y / yf, octaves, frequency, persistence, xOffset, yOffset, 0.0f);

			terrainPreview.Set(y, x, should);

			for (uint32_t z = 0; z < depth; z++)
			{
				if (type == TerrainType::Terrain3D)
					should = (float)Noise.GenOctave(x / xf, y / yf, z / zf, octaves, frequency, persistence, xOffset, yOffset, 0.0f);

				if ((should * yf) > y)
				{
					if (should > 0.0f  &&  should < 0.4f)       superChunk->Set(x, y, z, BLOCK_WATER, m_TerrainTextures[BLOCK_WATER]);
					else if (should > 0.4f  &&  should < 0.45f) superChunk->Set(x, y, z, BLOCK_SAND,  m_TerrainTextures[BLOCK_SAND]);
					else if (should > 0.45f &&  should < 0.60f) superChunk->Set(x, y, z, BLOCK_GRASS, m_TerrainTextures[BLOCK_GRASS]);
					else if (should > 0.60f &&  should < 0.8f)  superChunk->Set(x, y, z, BLOCK_STONE, m_TerrainTextures[BLOCK_STONE]);
					else if (should > 0.8f  &&  should < 1.0f)  superChunk->Set(x, y, z, BLOCK_SNOW,  m_TerrainTextures[BLOCK_SNOW]);
				}

				else superChunk->Set(x, y, z, BLOCK_AIR);
			}
		}
	}
	
	terrainPreview.Write();
	m_terrainPreviewTex.SetData(terrainPreview.GetData());
}

void VoxelTerrain::GenNoiseChunk(uint32_t xChunk, uint32_t yChunk, uint32_t zChunk, TerrainType type, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset)
{
	MC::Chunk* ActualChunk = superChunk->GetChunk(xChunk, yChunk, zChunk);

	if (ActualChunk)
		return;

	int CHUNK_SIZE = 15; //debug

	ActualChunk = superChunk->CreateChunk(xChunk / CHUNK_SIZE, yChunk / CHUNK_SIZE, zChunk / CHUNK_SIZE);

	MC::PerlinNoise Noise;
	float should = 0.0f;

	float xf = (float)CHUNK_SIZE;
	float yf = (float)CHUNK_SIZE;
	float zf = (float)CHUNK_SIZE;

	for (uint32_t x = 0; x < CHUNK_SIZE; x++)
	{
		for (uint32_t y = 0; y < CHUNK_SIZE; y++)
		{
			for (uint32_t z = 0; z < CHUNK_SIZE; z++)
			{
				should = (float)Noise.GenOctave(x / xf, y / yf, z / zf, octaves, frequency, persistence, (xChunk / CHUNK_SIZE), yOffset, (zChunk / CHUNK_SIZE));


				if ((should * yf) > y)
				{
					if (should > 0.0f  &&  should < 0.4f)       ActualChunk->set(x, y, z, BLOCK_WATER, m_TerrainTextures[BLOCK_WATER]);
					else if (should > 0.4f  &&  should < 0.45f) ActualChunk->set(x, y, z, BLOCK_SAND, m_TerrainTextures[BLOCK_SAND]);
					else if (should > 0.45f &&  should < 0.60f) ActualChunk->set(x, y, z, BLOCK_GRASS, m_TerrainTextures[BLOCK_GRASS]);
					else if (should > 0.60f &&  should < 0.8f)  ActualChunk->set(x, y, z, BLOCK_STONE, m_TerrainTextures[BLOCK_STONE]);
					else if (should > 0.8f  &&  should < 1.0f)  ActualChunk->set(x, y, z, BLOCK_SNOW, m_TerrainTextures[BLOCK_SNOW]);
				}

				else ActualChunk->set(x, y, z, BLOCK_AIR, m_TerrainTextures[BLOCK_WATER]);

			}
		}
	}
}


void VoxelTerrain::GenNoiseChunk(MC::vec3 ChunkPos, TerrainType type, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset)
{
	if (ChunkPos.x < 0 || ChunkPos.y < 0 || ChunkPos.z < 0)
		return;

	uint32_t xChunk = (uint32_t)ChunkPos.x;
	uint32_t yChunk = (uint32_t)ChunkPos.y;
	uint32_t zChunk = (uint32_t)ChunkPos.z;

	GenNoiseChunk(xChunk, yChunk, zChunk, type, octaves, frequency, persistence, xOffset, yOffset);
}

void VoxelTerrain::GenFlatTerrain()
{
	for (uint32_t y = 0; y < height; y++)
		for (uint32_t z = 0; z < depth; z++)
			for (uint32_t x = 0; x < width; x++)
				superChunk->Set(x, y, z, BLOCK_WATER, m_TerrainTextures[BLOCK_WATER]);
}

void VoxelTerrain::RemoveBlock(uint32_t x, uint32_t y, uint32_t z)
{
	superChunk->Set(x, y, z, BLOCK_AIR);
}

void VoxelTerrain::PlaceBlock(uint32_t x, uint32_t y, uint32_t z, EBlockType type)
{
	superChunk->Set(x, y, z, type, m_TerrainTextures[type]);
}

