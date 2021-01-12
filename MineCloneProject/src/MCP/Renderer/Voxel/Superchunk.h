#pragma once
#include "Chunk.h"
#include "MCP/Renderer/Texture2D.h"

constexpr int SUPER_CHUNK_SIZE = 15;

namespace MC
{
	struct Superchunk
	{
		Superchunk();
		~Superchunk();
		uint8_t Get(int x, int y, int z);
		void Set(int x, int y, int z, uint8_t type, const Texture2D* texture);

		Chunk* c[SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE];
	};
}