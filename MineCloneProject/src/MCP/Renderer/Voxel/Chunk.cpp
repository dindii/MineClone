#include "mcpch.h"
#include "Chunk.h"
#include "MCP/Renderer/RenderCommand.h"

#include "MCP/Utils/Logger.h"

namespace MC
{

	Chunk::Chunk() : elements(0), changed(true)
	{
		//wrap this
		memset(VisitedFront, 0, sizeof(bool) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
		memset(VisitedBack, 0, sizeof(bool) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
		memset(VisitedUp, 0, sizeof(bool) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
		memset(VisitedDown, 0, sizeof(bool) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
		memset(VisitedRight, 0, sizeof(bool) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
		memset(VisitedLeft, 0, sizeof(bool) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));

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

		int first = 0;

		for (uint32_t y = 0; y < CHUNK_SIZE; y++)
		{
			bool visibleFront = false, visibleBack = false;

			for (uint32_t z = 0; z < CHUNK_SIZE; z++)
			{
				bool visibleRight = false, visibleLeft = false;
				bool visibleDown = false, visibleUp = false;

				for (uint32_t x = 0; x < CHUNK_SIZE; x++)
				{
					uint8_t type = blocks[x][y][z];
					if (!type)
						continue;

					 //How much i did we dig into the blocks
					uint32_t length = 0, height = 0, depth = 0;
					uint32_t PreviousLength = 0, previousDepth = 0, previousHeight = 0;



					//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
					for (uint32_t yy = y; yy < CHUNK_SIZE; yy++)
					{
						for (uint32_t zz = z; zz < CHUNK_SIZE; zz++)
						{
							//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
							if (blocks[x][yy][zz] != blocks[x][yy][z] || !blocks[x][yy][zz] || VisitedLeft[x][yy][zz] || !isFaceVisibleLeft(x, yy, zz))
								break;

							//Salvamos falando que o bloco ja foi visitado
							VisitedLeft[x][yy][zz] = true;

							//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
							depth++;
						}

						if (yy > 0 && (previousDepth != depth || yy == CHUNK_SIZE - 1))
						{
							GenCubeFace(x, yy - height, z, 1, height, previousDepth, type, i, ECubeFace::LEFT);
							height = 0;
						}

						previousDepth = depth;
						depth = 0;

						height++;
					}

					height = 0;
					previousDepth = 0;

















					//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
					for (uint32_t yy = y; yy < CHUNK_SIZE; yy++)
					{
						for (uint32_t zz = z; zz < CHUNK_SIZE; zz++)
						{
							//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
							if (blocks[x][yy][zz] != blocks[x][yy][z] || !blocks[x][yy][zz] || VisitedRight[x][yy][zz] || !isFaceVisibleRight(x, yy, zz))
								break;

							//Salvamos falando que o bloco ja foi visitado
							VisitedRight[x][yy][zz] = true;

							//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
							depth++;
						}

						if (yy > 0 && (previousDepth != depth|| yy == CHUNK_SIZE - 1))
						{
							GenCubeFace(x, yy - height, z, 1, height, previousDepth, type, i, ECubeFace::RIGHT);
							height = 0;
						}

						previousDepth = depth;
						depth = 0;

						height++;
					}

					height = 0;
					previousDepth = 0;



				













					//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
					for (uint32_t zz = z; zz < CHUNK_SIZE; zz++)
					{
						for (uint32_t xx = x; xx < CHUNK_SIZE; xx++)
						{
							//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
							if (blocks[xx][y][zz] != blocks[x][y][zz] || !blocks[xx][y][zz] || VisitedDown[xx][y][zz] || !isFaceVisibleDown(xx, y, zz))
								break;

							//Salvamos falando que o bloco ja foi visitado
							VisitedDown[xx][y][zz] = true;

							//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
							length++;
						}

						if (zz > 0 && (PreviousLength != length || zz == CHUNK_SIZE - 1))
						{
							GenCubeFace(x, y, zz - depth, PreviousLength, 1, depth, type, i, ECubeFace::DOWN);
							depth = 0;
						}

						PreviousLength = length;
						length = 0;

						depth++;
					}

					depth = 0;
					length = 0;
					PreviousLength = 0;










					//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
					for (uint32_t zz = z; zz < CHUNK_SIZE; zz++)
					{
						for (uint32_t xx = x; xx < CHUNK_SIZE; xx++)
						{
							//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
							if (blocks[xx][y][zz] != blocks[x][y][zz] || !blocks[xx][y][zz] || VisitedUp[xx][y][zz] || !isFaceVisibleUp(xx, y, zz))
								break;

							//Salvamos falando que o bloco ja foi visitado
							VisitedUp[xx][y][zz] = true;

							//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
							length++;
						}

						if (zz > 0 && (PreviousLength != length || zz == CHUNK_SIZE - 1))
						{
							GenCubeFace(x, y, zz - depth, PreviousLength, 1, depth, type, i, ECubeFace::UP);
							depth = 0;
						}

						PreviousLength = length;
						length = 0;

						depth++;
					}

					depth = 0;
					length = 0;
					PreviousLength = 0;
















					//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
					for (uint32_t yy = y; yy < CHUNK_SIZE; yy++)
					{
						for (uint32_t xx = x; xx < CHUNK_SIZE; xx++)
						{
							//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
							if (blocks[xx][yy][z] != blocks[x][yy][z] || !blocks[xx][yy][z] || VisitedBack[xx][yy][z] || !isFaceVisibleBack(xx, yy, z))
								break;

							//Salvamos falando que o bloco ja foi visitado
							VisitedBack[xx][yy][z] = true;

							//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
							length++;
						}

						if (yy > 0 && (PreviousLength != length || yy == CHUNK_SIZE - 1))
						{
							GenCubeFace(x, yy - height, z, PreviousLength, height, 1, type, i, ECubeFace::BACK);
							height = 0;
						}

						PreviousLength = length;
						length = 0;

						height++;
					}

					height = 0;
					length = 0;
					PreviousLength = 0;






					//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
					for (uint32_t yy = y; yy < CHUNK_SIZE; yy++)
					{
						for (uint32_t xx = x; xx < CHUNK_SIZE; xx++)
						{
							//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
							if (blocks[xx][yy][z] != blocks[x][yy][z] || !blocks[xx][yy][z] || VisitedFront[xx][yy][z] || !IsFaceVisibleFront(xx, yy, z))
								break;

							//Salvamos falando que o bloco ja foi visitado
							VisitedFront[xx][yy][z] = true;

							//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
							length++;
						}

						if (yy > 0 && (PreviousLength != length || yy == CHUNK_SIZE-1))
						{
							GenCubeFace(x, yy-height, z, PreviousLength, height, 1, type, i, ECubeFace::FRONT);
							height = 0;
						}

						PreviousLength = length;
						length = 0;

						height++;
					}

 					height = 0;
 					length = 0;
					PreviousLength = 0;
				}
			
			}
		}

		elements = i; 

		//wrappar isso
		memset(VisitedFront, 0, sizeof(VisitedFront));
		memset(VisitedBack, 0, sizeof(VisitedBack));
		memset(VisitedUp, 0, sizeof(VisitedUp));
		memset(VisitedDown, 0, sizeof(VisitedDown));
		memset(VisitedRight, 0, sizeof(VisitedRight));
		memset(VisitedLeft, 0, sizeof(VisitedLeft));
	}

	bool Chunk::IsFaceVisibleFront(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		if (z == CHUNK_SIZE - 1 && nc.front_Chunk && nc.front_Chunk->blocks[x][y][0])
		{
			return false;
		}
		else if (z == CHUNK_SIZE - 1 || !blocks[x][y][z + 1])
		{
			return true;
		}

		return false;
	}

	bool Chunk::isFaceVisibleBack(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		if (z == 0 && nc.back_Chunk && nc.back_Chunk->blocks[x][y][CHUNK_SIZE - 1])
		{
			return false;
		}
		else if (z == 0 || (z > 0 && !blocks[x][y][z - 1]))
		{
			return true;
		}

		return false;
	}

	bool Chunk::isFaceVisibleUp(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		if (y == CHUNK_SIZE - 1 && nc.upper_Chunk&& nc.upper_Chunk->blocks[x][0][z])
		{
			return false;
		}
		else if (y == CHUNK_SIZE - 1 || !blocks[x][y + 1][z])
		{
			return true;
		}

		return false;
	}

	bool Chunk::isFaceVisibleDown(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		if (y == 0 && nc.below_Chunk && nc.below_Chunk->blocks[x][CHUNK_SIZE - 1][z])
		{
			return false;
		}
		else if (y == 0 || (y > 0 && !blocks[x][y - 1][z]))
		{
			return true;
		}

		return false;
	}

	bool Chunk::isFaceVisibleRight(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		//#TODO: Experimentar fazer a checagem só do true e o resto todo retorna false.
		if (x == CHUNK_SIZE - 1 && nc.right_Chunk && nc.right_Chunk->blocks[0][y][z])
		{
			return false;
		}
		else if (x == CHUNK_SIZE - 1 || (!blocks[x + 1][y][z]))
		{
			return true;
		}

		return false;
	}

	bool Chunk::isFaceVisibleLeft(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		//a block is NOT visible
		if (x == 0 && nc.left_Chunk && nc.left_Chunk->blocks[CHUNK_SIZE - 1][y][z])
		{
			return false;
		}
		// a block is visible
		else if (x == 0 || (x > 0 && !blocks[x - 1][y][z]))
		{
			return true;
		}

		return false;
	}



	void Chunk::GenCubeFace(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t length, const uint32_t height, const uint32_t depth, const uint8_t type, uint32_t& vertexIterator, ECubeFace face)
	{
		switch (face)
		{
			case ECubeFace::BACK:
			{
				vertex[vertexIterator++] = bvec4(x,			 y,		      z, type);
				vertex[vertexIterator++] = bvec4(x,			 y + height,  z, type);
				vertex[vertexIterator++] = bvec4(x + length, y, z,			 type);
				vertex[vertexIterator++] = bvec4(x,			 y + height,  z, type);
				vertex[vertexIterator++] = bvec4(x + length, y + height,  z, type);
				vertex[vertexIterator++] = bvec4(x + length, y,		      z, type);
				
				break;
			}
			case ECubeFace::FRONT:
			{															 
 				vertex[vertexIterator++] = bvec4(x,          y,			 z + 1, type);
 				vertex[vertexIterator++] = bvec4(x + length, y,			 z + 1, type);
				vertex[vertexIterator++] = bvec4(x,			 y + height, z + 1, type);
				vertex[vertexIterator++] = bvec4(x,			 y + height, z + 1, type);
				vertex[vertexIterator++] = bvec4(x + length, y,			 z + 1, type);
				vertex[vertexIterator++] = bvec4(x + length, y + height, z + 1, type);

				break;
			}
			case ECubeFace::LEFT:
			{
				vertex[vertexIterator++] = bvec4(x, y,          z, type);
				vertex[vertexIterator++] = bvec4(x, y,		    z + depth, type);
				vertex[vertexIterator++] = bvec4(x, y + height, z, type);
				vertex[vertexIterator++] = bvec4(x, y + height, z, type);
				vertex[vertexIterator++] = bvec4(x, y,          z + depth, type);
				vertex[vertexIterator++] = bvec4(x, y + height, z + depth, type);

				break;
			}
			case ECubeFace::RIGHT:
			{
				vertex[vertexIterator++] = bvec4(x + 1, y,			z,         type);
				vertex[vertexIterator++] = bvec4(x + 1, y + height, z,		   type);
				vertex[vertexIterator++] = bvec4(x + 1, y,			z + depth, type);
				vertex[vertexIterator++] = bvec4(x + 1, y + height, z,         type);
				vertex[vertexIterator++] = bvec4(x + 1, y + height, z + depth, type);
				vertex[vertexIterator++] = bvec4(x + 1, y,			z + depth, type);

				break;
			}
			case ECubeFace::UP:
			{
				vertex[vertexIterator++] = bvec4(x,		   	 y + 1, z,         type);
				vertex[vertexIterator++] = bvec4(x,		  	 y + 1, z + depth, type);
				vertex[vertexIterator++] = bvec4(x + length, y + 1, z,		   type);
				vertex[vertexIterator++] = bvec4(x + length, y + 1, z,	       type);
				vertex[vertexIterator++] = bvec4(x,          y + 1, z + depth, type);
				vertex[vertexIterator++] = bvec4(x + length, y + 1, z + depth, type);

				break;
			}
			case ECubeFace::DOWN:
			{
				vertex[vertexIterator++] = bvec4(x,          y, z,         type);
				vertex[vertexIterator++] = bvec4(x + length, y, z,         type);
				vertex[vertexIterator++] = bvec4(x,          y, z + depth, type);
				vertex[vertexIterator++] = bvec4(x + length, y, z,         type);
				vertex[vertexIterator++] = bvec4(x + length, y, z + depth, type);
				vertex[vertexIterator++] = bvec4(x,          y, z + depth, type);

				break;
			}
		}
	}
}