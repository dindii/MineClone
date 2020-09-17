#include "mcpch.h"
#include "Chunk.h"
#include "MCP/Renderer/RenderCommand.h"

#include "MCP/Utils/Logger.h"

namespace MC
{
	Chunk::Chunk() : elements(0), changed(true)
	{
		memset(blocks, 0, sizeof(blocks));
		memset(vertex, 0, sizeof(vertex));
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

		uint32_t i = 0;

		for (uint32_t x = 0; x < CHUNK_SIZE; x++)
			for (uint32_t y = 0; y < CHUNK_SIZE; y++)
				for (uint32_t z = 0; z < CHUNK_SIZE; z++) {
					uint8_t type = blocks[x][y][z];

					if (!type)
						continue;

					if (x == 0 && nc.left_Chunk && nc.left_Chunk->blocks[CHUNK_SIZE-1][y][z])
					{
					}
					else if (x == 0 || (x > 0 && !blocks[x - 1][y][z]))
						GenCubeFace(x, y, z, type, i, ECubeFace::LEFT);

					if (x == CHUNK_SIZE-1 && nc.right_Chunk && nc.right_Chunk->blocks[0][y][z])
					{
					}
					else if (x == CHUNK_SIZE - 1 || (!blocks[x + 1][y][z]))
						GenCubeFace(x, y, z, type, i, ECubeFace::RIGHT);

					if (y == 0 && nc.below_Chunk && nc.below_Chunk->blocks[x][CHUNK_SIZE-1][z])
					{
					}
					else if (y == 0 || (y > 0 && !blocks[x][y - 1][z]))
						GenCubeFace(x, y, z, type, i, ECubeFace::DOWN);


					if (y == CHUNK_SIZE-1 && nc.upper_Chunk&& nc.upper_Chunk->blocks[x][0][z])
					{
					}
					else if (y == CHUNK_SIZE - 1 || !blocks[x][y + 1][z])
						GenCubeFace(x, y, z, type, i, ECubeFace::UP);
					

					if (z == 0 && nc.back_Chunk && nc.back_Chunk->blocks[x][y][CHUNK_SIZE-1])
					{
					}
					else if (z == 0 || (z > 0 && !blocks[x][y][z - 1]))
						GenCubeFace(x, y, z, type, i, ECubeFace::BACK);


					if (z == CHUNK_SIZE-1 && nc.front_Chunk && nc.front_Chunk->blocks[x][y][0])
					{
					}
					else if (z == CHUNK_SIZE - 1 || !blocks[x][y][z + 1])
						GenCubeFace(x, y, z, type, i, ECubeFace::FRONT);				
				}

		elements = i; 
	}

	void Chunk::GenCubeFace(const int x, const int y, const int z, const uint8_t type, uint32_t& vertexIterator, ECubeFace face)
	{
		switch (face)
		{
			case ECubeFace::BACK:
			{
				vertex[vertexIterator++] = bvec4(x, y, z, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z, type);
				
				break;
			}
			case ECubeFace::FRONT:
			{
				vertex[vertexIterator++] = bvec4(x, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z + 1, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z + 1, type);

				break;
			}
			case ECubeFace::LEFT:
			{
				vertex[vertexIterator++] = bvec4(x, y, z, type);
				vertex[vertexIterator++] = bvec4(x, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z + 1, type);

				break;
			}
			case ECubeFace::RIGHT:
			{
				vertex[vertexIterator++] = bvec4(x + 1, y, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z + 1, type);

				break;
			}
			case ECubeFace::UP:
			{
				vertex[vertexIterator++] = bvec4(x, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z, type);
				vertex[vertexIterator++] = bvec4(x, y + 1, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + 1, z + 1, type);

				break;
			}
			case ECubeFace::DOWN:
			{
				vertex[vertexIterator++] = bvec4(x, y, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z, type);
				vertex[vertexIterator++] = bvec4(x, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z, type);
				vertex[vertexIterator++] = bvec4(x + 1, y, z + 1, type);
				vertex[vertexIterator++] = bvec4(x, y, z + 1, type);

				break;
			}
		}
	}
}