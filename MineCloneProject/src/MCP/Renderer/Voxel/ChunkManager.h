#pragma once
#include "Chunk.h"
#include "MCP/Renderer/Texture2D.h"
#include "MCP/Maths/uivec3.h"

constexpr int SUPER_CHUNK_SIZE = 40;

namespace MC
{
	struct ChunkManager
	{
		ChunkManager();
		~ChunkManager();
		uint8_t GetVoxel(int x, int y, int z);
		Chunk* GetChunk(int x, int y, int z);
		void Set(int x, int y, int z, uint8_t type, const BlockTexture2D* FaceTextures);
		void Set(int x, int y, int z, uint8_t type);
		Chunk* CreateChunk(uint32_t x, uint32_t y, uint32_t z);
		Chunk* c[SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE];
	};
}