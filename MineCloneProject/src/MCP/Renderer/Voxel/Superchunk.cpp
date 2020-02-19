#include "mcpch.h"
#include "Superchunk.h"

namespace MC
{

	Superchunk::Superchunk()
	{
		memset(c, 0, sizeof(c));
	}

	Superchunk::~Superchunk()
	{
		for (int x = 0; x < SUPER_CHUNK_SIZE; x++)
			for (int y = 0; y < SUPER_CHUNK_SIZE; y++)
				for (int z = 0; z < SUPER_CHUNK_SIZE; z++)
					delete c[x][y][z];
	}

	uint8_t Superchunk::Get(int x, int y, int z)
	{
		int cx = x / CHUNK_SIZE;
		int cy = y / CHUNK_SIZE;
		int cz = z / CHUNK_SIZE;

		x %= CHUNK_SIZE;
		y %= CHUNK_SIZE;
		z %= CHUNK_SIZE;

		if (!c[cx][cy][cz])
			return 0;
		else
			return c[cx][cy][cz]->get(x, y, z);
	}

	void Superchunk::Set(int x, int y, int z, uint8_t type)
	{
		int cx = x / CHUNK_SIZE;
		int cy = y / CHUNK_SIZE;
		int cz = z / CHUNK_SIZE;

		x %= CHUNK_SIZE;
		y %= CHUNK_SIZE;
		z %= CHUNK_SIZE;

		if (!c[cx][cy][cz])
			c[cx][cy][cz] = new Chunk();

		c[cx][cy][cz]->set(x, y, z, type);
	}

}