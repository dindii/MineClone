#pragma once
#include "Chunk.h"
#include "MCP/Renderer/Texture2D.h"
#include "MCP/Maths/uivec3.h"
constexpr int SUPER_CHUNK_SIZE = 20;

namespace MC
{
	struct ChunkManager
	{
		ChunkManager();
		~ChunkManager();
		uint8_t Get(int x, int y, int z);
		void Set(int x, int y, int z, uint8_t type, const BlockTexture2D* FaceTextures);
		void Set(int x, int y, int z, uint8_t type);
		
		Chunk* c[SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE];
	};
}