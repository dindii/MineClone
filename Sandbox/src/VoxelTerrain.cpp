#include "mcpch.h"
#include "VoxelTerrain.h"
#include "MCP/Noise/PerlinNoise.h"
#include "MCP/Renderer/Texture2D.h"

VoxelTerrain::VoxelTerrain(uint32_t c_width, uint32_t c_height, uint32_t c_depth) : m_width(c_width), m_height(c_height), m_depth(c_depth)
{
	m_superChunk = new MC::ChunkManager;

	//As we don't have an asset manager yet, is the user responsability to acquire and release resource.
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

	m_TerrainTextures[EBlockType::BLOCK_BLACK_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/black_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_BLUE_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/blue_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_BROWN_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/brown_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_CYAN_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/cyan_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_GRAY_WOOL]       = new MC::BlockTexture2D("res/Textures/wool/gray_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_GREEN_WOOL]      = new MC::BlockTexture2D("res/Textures/wool/green_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_LIGHT_BLUE_WOOL] = new MC::BlockTexture2D("res/Textures/wool/light_blue_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_LIGHT_GRAY_WOOL] = new MC::BlockTexture2D("res/Textures/wool/light_gray_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_LIME_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/lime_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_MAGENTA_WOOL]	 = new MC::BlockTexture2D("res/Textures/wool/magenta_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_ORANGE_WOOL]	 = new MC::BlockTexture2D("res/Textures/wool/orange_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_PINK_WOOL]	     = new MC::BlockTexture2D("res/Textures/wool/pink_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_PURPLE_WOOL]	 = new MC::BlockTexture2D("res/Textures/wool/purple_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_RED_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/red_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_WHITE_WOOL]		 = new MC::BlockTexture2D("res/Textures/wool/white_wool.png");
	m_TerrainTextures[EBlockType::BLOCK_YELLOW_WOOL]	 = new MC::BlockTexture2D("res/Textures/wool/yellow_wool.png");
}

VoxelTerrain::~VoxelTerrain()
{
	for (uint16_t x = 0; x < m_TerrainTextures.size(); x++)
		delete m_TerrainTextures[(EBlockType)x];
}

void VoxelTerrain::GenNoiseChunk(int32_t PositionX, int32_t PositionY, int32_t PositionZ, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset)
{
	//We don't have negative chunk positions in our array but we do have negative world positions, so we must bea able to recieve negative numbers and then
	//deny them. Otherwise we would get a large number (by the unsigned conversion) that would be harder to filter since it would not be negative.
	if (PositionX <= 0 || PositionY <= 0 || PositionZ <= 0)
		return;

	MC::Chunk* ActualChunk = m_superChunk->GetChunk(PositionX, PositionY, PositionZ);

	//If we already have a generated or loaded chunk, skip.
	if (ActualChunk)
		return;

	
	MC::PerlinNoise Noise;
	
	//We will store the noise value here and use it to decide if a block will be place in the position or not
	float ShouldPlaceBlock = 0.0f;

	//This conversion is necessary because ChunkManager::Set(x, y, z) uses modulus operator and then divides by the chunk size
	//So we must make some conversions first for a more accurate value
	uint32_t  ChunkX = PositionX / MC::CHUNK_SIZE;
	uint32_t  ChunkY = PositionY / MC::CHUNK_SIZE;
	uint32_t  ChunkZ = PositionZ / MC::CHUNK_SIZE;

	uint32_t ChunkXLoc = ChunkX * MC::CHUNK_SIZE;
	uint32_t ChunkYLoc = ChunkY * MC::CHUNK_SIZE;
	uint32_t ChunkZLoc = ChunkZ * MC::CHUNK_SIZE;

	//We need float values for our noise to work correctly
	float fWidth  =  (float)m_width;
	float fHeight =  (float)m_height;
	float fDepth  =  (float)m_depth;

	for (uint32_t x = 0; x < fWidth; x++)
	{
		for (uint32_t y = 0; y < fHeight; y++)
		{
			for (uint32_t z = 0; z < fDepth; z++)
			{
				//We use the PositionX and PositionZ in the world so we can offset our noise and make the world procedural.
				ShouldPlaceBlock = (float)Noise.GenOctave(x / fWidth, y / fHeight, z / fDepth, octaves, frequency, persistence, (PositionX / MC::CHUNK_SIZE), yOffset, (PositionZ / MC::CHUNK_SIZE));

				//Values defined by ourselves, you can make a lot of stuff with creativity.
				if ((ShouldPlaceBlock * fHeight) > y)
				{
					if (ShouldPlaceBlock > 0.0f  &&  ShouldPlaceBlock < 0.4f)       m_superChunk->Set(x + ChunkXLoc, y + ChunkYLoc, z + ChunkZLoc, BLOCK_WATER, m_TerrainTextures[BLOCK_WATER]);
					else if (ShouldPlaceBlock > 0.4f  &&  ShouldPlaceBlock < 0.45f) m_superChunk->Set(x + ChunkXLoc, y + ChunkYLoc, z + ChunkZLoc, BLOCK_SAND, m_TerrainTextures[BLOCK_SAND]);
					else if (ShouldPlaceBlock > 0.45f &&  ShouldPlaceBlock < 0.60f) m_superChunk->Set(x + ChunkXLoc, y + ChunkYLoc, z + ChunkZLoc, BLOCK_GRASS, m_TerrainTextures[BLOCK_GRASS]);
					else if (ShouldPlaceBlock > 0.60f &&  ShouldPlaceBlock < 0.8f)  m_superChunk->Set(x + ChunkXLoc, y + ChunkYLoc, z + ChunkZLoc, BLOCK_STONE, m_TerrainTextures[BLOCK_STONE]);
					else if (ShouldPlaceBlock > 0.8f  &&  ShouldPlaceBlock < 1.0f)  m_superChunk->Set(x + ChunkXLoc, y + ChunkYLoc, z + ChunkZLoc, BLOCK_SNOW, m_TerrainTextures[BLOCK_SNOW]);
				}

				//If it shoudn't be a block, set it as an air block
				else m_superChunk->Set(x + ChunkXLoc, y, z + ChunkZLoc, BLOCK_AIR, m_TerrainTextures[BLOCK_WATER]);
			}
		}
	}
}

//Gen a cube terrain for debug or test purposes
void VoxelTerrain::GenFlatTerrain()
{
	for (uint32_t y = 0; y < m_height; y++)
		for (uint32_t z = 0; z < m_depth; z++)
			for (uint32_t x = 0; x < m_width; x++)
				m_superChunk->Set(x, y, z, BLOCK_WATER, m_TerrainTextures[BLOCK_WATER]);
}

//Turns the block into an air block
void VoxelTerrain::RemoveBlock(uint32_t x, uint32_t y, uint32_t z)
{
	m_superChunk->Set(x, y, z, BLOCK_AIR);
}

//Place a block with an type and it will be placed with its correspondent texture
void VoxelTerrain::PlaceBlock(uint32_t x, uint32_t y, uint32_t z, EBlockType type)
{
	m_superChunk->Set(x, y, z, type, m_TerrainTextures[type]);
}
