#include "mcpch.h"
#include "Chunk.h"

#include "MCP/Renderer/RenderCommand.h"

namespace MC
{
	Chunk::Chunk()
	{
		memset(blocks, 1, sizeof(blocks));
		memset(vertex, 0, sizeof(vertex));
		elements = 0;
		changed = true;
		VBO = RenderCommand::GenMesh(1);
	}

	Chunk::~Chunk()
	{
		RenderCommand::DelMesh(1, VBO);
	}

	uint8_t Chunk::get(int x, int y, int z)
	{
		return blocks[x][y][z];
	}

	void Chunk::set(int x, int y, int z, uint8_t type)
	{
		blocks[x][y][z] = type;
		changed = true;
	}

	void Chunk::update()
	{
		changed = false;

		int i = 0;

		for (unsigned int x = 0; x < CHUNK_SIZE; x++)
			for (unsigned int y = 0; y < CHUNK_SIZE; y++)
				for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
					uint8_t type = blocks[x][y][z];

					if (!type)
						continue;


					// View from negative x //
					vertex[i++] = bvec4(x, y, z, type);
					vertex[i++] = bvec4(x, y, z + 1, type);
					vertex[i++] = bvec4(x, y + 1, z, type);
					vertex[i++] = bvec4(x, y + 1, z, type);
					vertex[i++] = bvec4(x, y, z + 1, type);
					vertex[i++] = bvec4(x, y + 1, z + 1, type);

					// View from positive x //
					vertex[i++] = bvec4(x + 1, y, z, type);
					vertex[i++] = bvec4(x + 1, y + 1, z, type);
					vertex[i++] = bvec4(x + 1, y, z + 1, type);
					vertex[i++] = bvec4(x + 1, y + 1, z, type);
					vertex[i++] = bvec4(x + 1, y + 1, z + 1, type);
					vertex[i++] = bvec4(x + 1, y, z + 1, type);


					// View from negative y //
					vertex[i++] = bvec4(x, y, z, type);
					vertex[i++] = bvec4(x+1, y, z+1, type);

					vertex[i++] = bvec4(x, y, z, type);
					vertex[i++] = bvec4(x+1, y, z+1, type);
					vertex[i++] = bvec4(x, y, z+1, type);


					// View from positive y //
					vertex[i++] = bvec4(x + 1, y + 1, z, type);
					vertex[i++] = bvec4(x, y + 1, z, type);
					vertex[i++] = bvec4(x+1, y + 1, z + 1, type);

					vertex[i++] = bvec4(x, y + 1, z, type);
					vertex[i++] = bvec4(x, y + 1, z + 1, type);
					vertex[i++] = bvec4(x + 1, y + 1, z+1, type);

					// View from negative z //
					vertex[i++] = bvec4(x, y, z, type);
					vertex[i++] = bvec4(x+1, y, z, type);
					vertex[i++] = bvec4(x+1, y+1, z, type);

					vertex[i++] = bvec4(x, y, z, type);
					vertex[i++] = bvec4(x+1, y+1, z, type);
					vertex[i++] = bvec4(x, y+1, z, type);


					// View from positive z
					vertex[i++] = bvec4(x+1, y, z+1, type);
					vertex[i++] = bvec4(x, y, z+1, type);
					vertex[i++] = bvec4(x+1, y+1, z+1, type);

					vertex[i++] = bvec4(x+1, y, z+1, type);
					vertex[i++] = bvec4(x, y, z+1, type);
					vertex[i++] = bvec4(x, y+1, z+1, type);

		}


		elements = i; 
	}


}