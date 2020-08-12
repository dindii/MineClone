#pragma once
#include "MCP/Renderer/Voxel/Superchunk.h"
#include "MCP/Renderer/Texture2D.h"

namespace MC
{
	class VoxelTerrain
	{
	public:
		VoxelTerrain();
		~VoxelTerrain();

		void Gen2DNoiseTerrain(uint32_t x, uint32_t y, uint32_t z, uint32_t octaves, float frequency, float persistence);
		void Gen3DNoiseTerrain(uint32_t x, uint32_t y, uint32_t z, uint32_t octaves, float frequency, float persistence);
		void GenFlatTerrain(uint32_t xt, uint32_t yt, uint32_t zt);

		Superchunk* GetTerrainData() { return superChunk; }
		Texture2D GetTerrainPreview() { return m_terrainPreviewTex; }

	private:
		Superchunk* superChunk; //@TODO: extent to multiple superchunks
		Texture2D m_terrainPreviewTex;
	};
}