#pragma once
#include "Chunk.h"

constexpr int SUPER_CHUNK_SIZE = 8;

namespace MC
{
	struct Superchunk
	{
		Superchunk();
		~Superchunk();
		uint8_t Get(int x, int y, int z);
		void Set(int x, int y, int z, uint8_t type);

		Chunk* c[SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE][SUPER_CHUNK_SIZE];
	};
}