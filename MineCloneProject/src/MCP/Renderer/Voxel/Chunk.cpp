#include "mcpch.h"
#include "Chunk.h"
#include "MCP/Renderer/RenderCommand.h"

#include "MCP/Utils/Logger.h"

namespace MC
{

	Chunk::Chunk() : elements(0), changed(true)
	{
		//wrap this
		memset(VisitedFront, 0,  sizeof(bool) * ((CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1)));
		memset(VisitedBack,  0,  sizeof(bool) * ((CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1)));
		memset(VisitedUp,    0,  sizeof(bool) * ((CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1)));
		memset(VisitedDown,  0,  sizeof(bool) * ((CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1)));
		memset(VisitedRight, 0,  sizeof(bool) * ((CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1)));
		memset(VisitedLeft,  0,  sizeof(bool) * ((CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1)));

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

	uint8_t type = 0;

	void Chunk::update()
	{
		changed = false;

		uint32_t vertexBufferIterator = 0;

		for (uint32_t y = 0; y <= CHUNK_SIZE; y++)	
			for (uint32_t z = 0; z <= CHUNK_SIZE; z++)	
				for (uint32_t x = 0; x <= CHUNK_SIZE; x++)
				{
					type = blocks[x][y][z];
					if (!type)
						continue;

					GreedyFrontFace(x, y, z, vertexBufferIterator, this);
					GreedyBackFace (x, y, z, vertexBufferIterator, this);

					GreedyUpFace   (x, y, z, vertexBufferIterator, this);
					GreedyDownFace (x, y, z, vertexBufferIterator, this);
					
					GreedyRightFace(x, y, z, vertexBufferIterator, this);
					GreedyLeftFace (x, y, z, vertexBufferIterator, this);
				}	

		elements = vertexBufferIterator; 

		//wrappar isso
		memset(VisitedFront, 0, sizeof(VisitedFront));
		memset(VisitedBack, 0, sizeof(VisitedBack));
		memset(VisitedUp, 0, sizeof(VisitedUp));
		memset(VisitedDown, 0, sizeof(VisitedDown));
		memset(VisitedRight, 0, sizeof(VisitedRight));
		memset(VisitedLeft, 0, sizeof(VisitedLeft));
	}

	//#TODO: Expandir para outras chunks
	bool Chunk::isFaceVisible(const uint32_t x, const uint32_t y, const uint32_t z, ECubeFace face, Chunk* chunkTarget)
	{
		switch (face)
		{
			case ECubeFace::LEFT:
			{
				if (x == 0 || (x > 0 && !chunkTarget->blocks[x - 1][y][z]))
					return true;
				break;
			}
			case ECubeFace::RIGHT:
			{
				if (x == CHUNK_SIZE || !chunkTarget->blocks[x + 1][y][z])
					return true;
				break;
			}
			case ECubeFace::DOWN:
			{
				if (y == 0 || (y > 0 && !chunkTarget->blocks[x][y - 1][z]))
					return true;
				break;
			}
			case ECubeFace::UP:
			{
				if (y == CHUNK_SIZE || !chunkTarget->blocks[x][y + 1][z])
					return true;
				break;
			}
			case ECubeFace::BACK:
			{
				if (z == 0 || (z > 0 && !chunkTarget->blocks[x][y][z - 1]))
					return true;
				break;
			}
			case ECubeFace::FRONT:
			{
				if (z == CHUNK_SIZE || !chunkTarget->blocks[x][y][z + 1])
					return true;
				break;
			}
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


	void Chunk::GreedyFrontFace(const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget)
	{
		uint32_t length = 0, height = 0;
		uint32_t PreviousLength = 0;

		//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
		for (uint32_t yy = y; yy <= CHUNK_SIZE; yy++)
		{
			for (uint32_t xx = x; xx <= CHUNK_SIZE; xx++)
			{
				//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
				if (chunkTarget->blocks[xx][yy][z] != chunkTarget->blocks[x][yy][z] || !chunkTarget->blocks[xx][yy][z] || VisitedFront[xx][yy][z] || !isFaceVisible(xx, yy, z, ECubeFace::FRONT, chunkTarget))
					break;

				//Salvamos falando que o bloco ja foi visitado
				VisitedFront[xx][yy][z] = true;

				//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
				length++;
			}

			if ((PreviousLength != length || yy == CHUNK_SIZE))
			{
				GenCubeFace(x, yy - height, z, PreviousLength, height, 1, type, vertexBufferIterator, ECubeFace::FRONT);
				height = 0;
			}

			PreviousLength = length;
			length = 0;

			height++;
		}
	}
	
	void Chunk::GreedyBackFace(const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget)
	{
		uint32_t length = 0, height = 0;
		uint32_t PreviousLength = 0;

		//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
		for (uint32_t yy = y; yy <= CHUNK_SIZE; yy++)
		{
			for (uint32_t xx = x; xx <= CHUNK_SIZE; xx++)
			{
				//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
				if (blocks[xx][yy][z] != blocks[x][yy][z] || !blocks[xx][yy][z] || VisitedBack[xx][yy][z] || !isFaceVisible(xx, yy, z, ECubeFace::BACK, this))
					break;

				//Salvamos falando que o bloco ja foi visitado
				VisitedBack[xx][yy][z] = true;

				//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
				length++;
			}

			if (yy > 0 && (PreviousLength != length || yy == CHUNK_SIZE))
			{
				GenCubeFace(x, yy - height, z, PreviousLength, height, 1, type, vertexBufferIterator, ECubeFace::BACK);
				height = 0;
			}

			PreviousLength = length;
			length = 0;

			height++;
		}
	}

	
	void Chunk::GreedyUpFace(const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget)
	{
		uint32_t length = 0, depth = 0;
		uint32_t PreviousLength = 0;

		//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
		for (uint32_t zz = z; zz <= CHUNK_SIZE; zz++)
		{

			for (uint32_t xx = x; xx <= CHUNK_SIZE; xx++)
			{
				//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
				if (blocks[xx][y][zz] != blocks[x][y][zz] || !blocks[xx][y][zz] || VisitedUp[xx][y][zz] || !isFaceVisible(xx, y, zz, ECubeFace::UP, this))
					break;

				//Salvamos falando que o bloco ja foi visitado
				VisitedUp[xx][y][zz] = true;

				//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
				length++;
			}

			if (zz > 0 && (PreviousLength != length || zz == CHUNK_SIZE))
			{
				GenCubeFace(x, y, zz - depth, PreviousLength, 1, depth, type, vertexBufferIterator, ECubeFace::UP);
				depth = 0;
			}

			PreviousLength = length;
			length = 0;

			depth++;
		}
	}
	
	void Chunk::GreedyDownFace(const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget)
	{
		uint32_t length = 0, depth = 0;
		uint32_t PreviousLength = 0;

		//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
		for (uint32_t zz = z; zz <= CHUNK_SIZE; zz++)
		{
			for (uint32_t xx = x; xx <= CHUNK_SIZE; xx++)
			{
				//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
				if (blocks[xx][y][zz] != blocks[x][y][zz] || !blocks[xx][y][zz] || VisitedDown[xx][y][zz] || !isFaceVisible(xx, y, zz, ECubeFace::DOWN, this))
					break;

				//Salvamos falando que o bloco ja foi visitado
				VisitedDown[xx][y][zz] = true;

				//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
				length++;
			}

			if (zz > 0 && (PreviousLength != length || zz == CHUNK_SIZE))
			{
				GenCubeFace(x, y, zz - depth, PreviousLength, 1, depth, type, vertexBufferIterator, ECubeFace::DOWN);
				depth = 0;
			}

			PreviousLength = length;
			length = 0;

			depth++;
		}
	}
	

	void Chunk::GreedyLeftFace(const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget)
	{
		uint32_t depth = 0, height = 0;
		uint32_t PreviousDepth = 0;

		//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
		for (uint32_t yy = y; yy <= CHUNK_SIZE; yy++)
		{
			for (uint32_t zz = z; zz <= CHUNK_SIZE; zz++)
			{
				//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
				if (blocks[x][yy][zz] != blocks[x][yy][z] || !blocks[x][yy][zz] || VisitedLeft[x][yy][zz] || !isFaceVisible(x, yy, zz, ECubeFace::LEFT, this))
					break;

				//Salvamos falando que o bloco ja foi visitado
				VisitedLeft[x][yy][zz] = true;

				//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
				depth++;
			}

			if (yy > 0 && (PreviousDepth != depth || yy == CHUNK_SIZE))
			{
				GenCubeFace(x, yy - height, z, 1, height, PreviousDepth, type, vertexBufferIterator, ECubeFace::LEFT);
				height = 0;
			}

			PreviousDepth = depth;
			depth = 0;

			height++;
		}
	}
	
	void Chunk::GreedyRightFace(const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget)
	{
		uint32_t depth = 0, height = 0;
		uint32_t PreviousDepth = 0;

		//#TODO: Expandir pra outras faces e depois expandir pra outros chunks
		for (uint32_t yy = y; yy <= CHUNK_SIZE; yy++)
		{
			for (uint32_t zz = z; zz <= CHUNK_SIZE; zz++)
			{
				//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
				if (blocks[x][yy][zz] != blocks[x][yy][z] || !blocks[x][yy][zz] || VisitedRight[x][yy][zz] || !isFaceVisible(x, yy, zz, ECubeFace::RIGHT, this))
					break;

				//Salvamos falando que o bloco ja foi visitado
				VisitedRight[x][yy][zz] = true;

				//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
				depth++;
			}

			if (yy > 0 && (PreviousDepth != depth || yy == CHUNK_SIZE))
			{
				GenCubeFace(x, yy - height, z, 1, height, PreviousDepth, type, vertexBufferIterator, ECubeFace::RIGHT);
				height = 0;
			}

			PreviousDepth = depth;
			depth = 0;

			height++;
		}
	}





}