#pragma once
#include "MCP/Renderer/Voxel/ChunkManager.h"
#include "MCP/Renderer/Texture2D.h"
#include "MCP/Noise/PerlinNoise.h"

#include <unordered_map>

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

	enum class TerrainType : uint8_t
	{
		Terrain2D   = 2,
		Terrain3D   = 3
	};

	void GenNoiseTerrain(TerrainType type, uint32_t octaves, float frequency, float persistence, float xOffset, float yOffset);
	void GenFlatTerrain();

	inline void ResizeTerrain(uint32_t newWidth, uint32_t newHeight, uint32_t newDepth) { width = newWidth; height = newHeight, depth = newDepth; }

	inline MC::ChunkManager* GetTerrainData() { return superChunk; }
	inline MC::Texture2D& GetTerrainPreview() { return m_terrainPreviewTex; }

	void RemoveBlock(uint8_t x, uint8_t y, uint8_t z);
	void PlaceBlock(uint8_t x, uint8_t y, uint8_t z, EBlockType type);

	inline uint32_t GetWidth()  const { return width; }
	inline uint32_t GetHeight() const { return height; }
	inline uint32_t GetDepth()  const { return depth; }

	inline MC::BlockTexture2D* GetTexture(EBlockType block) { return  m_TerrainTextures[block]; }
private:
	uint32_t width, height, depth;

	MC::ChunkManager* superChunk; 
	MC::Texture2D m_terrainPreviewTex;

	std::unordered_map<EBlockType, MC::BlockTexture2D*> m_TerrainTextures;
};
