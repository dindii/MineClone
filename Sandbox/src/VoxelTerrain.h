#pragma once
#include "MCP/Renderer/Voxel/ChunkManager.h"
#include "MCP/Renderer/Texture2D.h"
#include "MCP/Noise/PerlinNoise.h"

#include <unordered_map>

//Our terrain block types, this could be in a general file for a broader use
enum EBlockType : uint8_t
{
	BLOCK_AIR = 0,
	BLOCK_WATER,
	BLOCK_SAND,
	BLOCK_GRASS,
	BLOCK_DIRT,
	BLOCK_SNOW,
	BLOCK_STONE,
	BLOCK_WOOD,
	BLOCK_BLACK_WOOL,
	BLOCK_BLUE_WOOL,
	BLOCK_BROWN_WOOL,
	BLOCK_CYAN_WOOL,
	BLOCK_GRAY_WOOL,
	BLOCK_GREEN_WOOL,
	BLOCK_LIGHT_BLUE_WOOL,
	BLOCK_LIGHT_GRAY_WOOL,
	BLOCK_LIME_WOOL,
	BLOCK_MAGENTA_WOOL,
	BLOCK_ORANGE_WOOL,
	BLOCK_PINK_WOOL,
	BLOCK_PURPLE_WOOL,
	BLOCK_RED_WOOL,
	BLOCK_WHITE_WOOL,
	BLOCK_YELLOW_WOOL
};

class VoxelTerrain
{
public:
	VoxelTerrain(uint32_t c_width, uint32_t c_height, uint32_t c_depth);
	~VoxelTerrain();

	void GenNoiseChunk(int32_t PositionX, int32_t PositionY, int32_t PositionZ, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset);
	void GenFlatTerrain();

	inline void ResizeTerrain(uint32_t newWidth, uint32_t newHeight, uint32_t newDepth) { m_width = newWidth; m_height = newHeight, m_depth = newDepth; }

	inline MC::ChunkManager* GetTerrainData() { return m_superChunk; }

	void RemoveBlock(uint32_t x, uint32_t y, uint32_t z);
	void PlaceBlock(uint32_t x, uint32_t y, uint32_t z, EBlockType type);

	inline uint32_t GetWidth()  const { return m_width; }
	inline uint32_t GetHeight() const { return m_height; }
	inline uint32_t GetDepth()  const { return m_depth; }

	inline MC::BlockTexture2D* GetTexture(EBlockType block) { return  m_TerrainTextures[block]; }
private:
	uint32_t m_width, m_height, m_depth;

	//Probably this will be turned in some global variable when we get our world divided in regions
	MC::ChunkManager* m_superChunk; 

	//We will link block types with its textures in this terrain approach
	std::unordered_map<EBlockType, MC::BlockTexture2D*> m_TerrainTextures;
};
