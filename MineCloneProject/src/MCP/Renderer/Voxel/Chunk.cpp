#include "mcpch.h"
#include "Chunk.h"
#include "MCP/Renderer/RenderCommand.h"

#include "MCP/Utils/Logger.h"
#include "MCP/Renderer/VoxelRenderer.h"

#include "MCP/Maths/Maths.h"
namespace MC
{
	constexpr uint32_t CHUNK_SQUARED = (CHUNK_SIZE) * (CHUNK_SIZE);
	constexpr uint32_t CHUNK_SIZE_CUBED = CHUNK_SQUARED * (CHUNK_SIZE);

#define CALC_INDEX(x, y, z, a) (x + z * (CHUNK_SIZE) + y * CHUNK_SQUARED) + (CHUNK_SIZE_CUBED * a)
#define CALC_INDEX_SIMPLE(x, y, z) (x + z * (CHUNK_SIZE) + y * CHUNK_SQUARED)


	Chunk::Chunk() : elements(0), changed(true)
	{
		memset(blocks,        0, sizeof(blocks));
		memset(vertex,        0, sizeof(vertex));
		memset(VisitedBlocks, 0, sizeof(VisitedBlocks));
		memset(m_TexturesID,  0, sizeof(m_TexturesID));

		VBO = RenderCommand::GenMesh(1);
	}

	Chunk::~Chunk()
	{
		RenderCommand::DelMesh(1, VBO);
	}

	uint8_t Chunk::get(int x, int y, int z)
	{
		return blocks[CALC_INDEX_SIMPLE(x, y, z)];
	}

	void Chunk::set(int x, int y, int z, uint8_t type, const BlockTexture2D* FaceTextures)
	{
	
		if (!type || !FaceTextures)
		{
			for (uint8_t face = 0; face < CUBE_FACES; face++)
				this->set(x, y, z, type, (ECubeFace)face, nullptr);
		
			return;
		}
		
		for (uint8_t face = 0; face < CUBE_FACES; face++)
			this->set(x, y, z, type, (ECubeFace)face, FaceTextures->Textures[face]);
			
	}
	void Chunk::set(int x, int y, int z, uint8_t type, ECubeFace face, const Texture2D* UniformTexture)
	{
		blocks[CALC_INDEX_SIMPLE(x, y, z)] = type;
		changed = true;

		if (!type || !UniformTexture)
			return;	
		
		int8_t TextureID = VoxelRenderer::GetTexture(UniformTexture);

		if (TextureID < 0)
			TextureID = VoxelRenderer::AddTexture(UniformTexture);
		
		
		//Almost all of my voxel mesh generation works with faces, so i have to make my texture array also work with faces
		//This can leads us in the future to a setup where we can choose a texture for each of the six cube faces. 
			m_TexturesID[CALC_INDEX(x, y, z, face)] = TextureID;
		
	}

	void Chunk::update()
	{
	    uint8_t type = 0;
		changed = false;

		uint32_t vertexBufferIterator = 0;

		for (uint32_t y = 0; y < CHUNK_SIZE; y++)	
			for (uint8_t z = 0; z < CHUNK_SIZE; z++)	
				for (uint8_t x = 0; x < CHUNK_SIZE; x++)
				{
					type = blocks[CALC_INDEX_SIMPLE(x, y, z)];
					if (!type)
						continue;

					CalcFrontAndBackFace(x, y, z, type, vertexBufferIterator);
					CalcUpAndDownFace   (x, y, z, type, vertexBufferIterator);
					CalcRightAndLeftFace(x, y, z, type, vertexBufferIterator);
				}	

		elements = vertexBufferIterator; 

		memset(VisitedBlocks, 0, sizeof(VisitedBlocks));
	}

	bool Chunk::isFaceVisible(const uint8_t x, const uint32_t y, const uint8_t z, ECubeFace face)
	{
		switch (face)
		{
			case ECubeFace::LEFT:
			{
				if (x == 0 && nc.left_Chunk && nc.left_Chunk->blocks[CALC_INDEX_SIMPLE((CHUNK_SIZE - 1), y, z)])
					return false;
			
				else if (x == 0 || (x > 0 && !blocks[CALC_INDEX_SIMPLE((x - 1), y, z)]))
					return true;

				
				break;
			}
			case ECubeFace::RIGHT:
			{
				if (x == CHUNK_SIZE - 1 && nc.right_Chunk && nc.right_Chunk->blocks[CALC_INDEX_SIMPLE(0, y, z)])
					return false;
				
				else if (x == CHUNK_SIZE -1 || !blocks[CALC_INDEX_SIMPLE((x+1), y, z)])
					return true;
				

				break;
			}
			case ECubeFace::DOWN:
			{
				if (y == 0 && nc.below_Chunk && nc.below_Chunk->blocks[CALC_INDEX_SIMPLE(x, (CHUNK_SIZE-1), z)])
					return false;
				
				else if (y == 0 || (y > 0 && !blocks[CALC_INDEX_SIMPLE(x, (y - 1), z)]))
					return true;
				
					break;
			}
			case ECubeFace::UP:
			{
				if (y == CHUNK_SIZE - 1 && nc.upper_Chunk && nc.upper_Chunk->blocks[CALC_INDEX_SIMPLE(x, 0, z)])
					return false;
				
				else if (y == CHUNK_SIZE - 1 || !blocks[CALC_INDEX_SIMPLE(x, (y + 1), z)])
					return true;

				break;
			}
			case ECubeFace::BACK:
			{
				if (z == 0 && nc.back_Chunk && nc.back_Chunk->blocks[CALC_INDEX_SIMPLE(x, y, (CHUNK_SIZE - 1))])
					return false;
				
				else if (z == 0 || (z > 0 && !blocks[CALC_INDEX_SIMPLE(x, y, (z - 1))]))
					return true;
				
				break;
			}
			case ECubeFace::FRONT:
			{
 				if (z == CHUNK_SIZE - 1 && nc.front_Chunk && nc.front_Chunk->blocks[CALC_INDEX_SIMPLE(x, y, 0)])
 					return false;
 				
 				else if (z == CHUNK_SIZE - 1 || !blocks[CALC_INDEX_SIMPLE(x, y, (z + 1))])
 					return true;

				break;
			}
		}

		return false;
	}

	uint32_t Chunk::PackVertexAtbs(const uint8_t x, const uint32_t y, const uint8_t z, const uint8_t normalLight, const uint32_t textureID, const uint8_t textureCoordsIndex, const uint8_t type, const uint8_t Length1, const uint8_t Length2)
	{
		uint32_t Pack =  (Length1 << 2) | (textureCoordsIndex << 6) | (textureID << 8) | (normalLight << 13) | (z << 16) | (x << 20) | (Length2 << 24) | (y << 28);
		
		//	 Y    ATB2    X    Z      N    I    TC    ATB1 LEFT
		// |0000 |0000| |0000 0000| |000 00000| 00    0000 00 
		//LEFTING: 0000 0000 00

		//z 0-8
		//x 8-16
		//y 16-24

		//X - 16
		//Z - 16
		//Y - 256

		return Pack;
	}

	void Chunk::GenCubeFace(const uint8_t x, const uint32_t y, const uint8_t z, const uint8_t length, const uint32_t height, const uint8_t depth, const uint8_t type, uint32_t& vertexIterator, uint8_t textureID, ECubeFace face)
	{
		switch (face)
		{
			//#TODO: All faces (specially RIGHT and LEFT) doesn't follow a pattern of vertex setting, put them uniform.
			case ECubeFace::BACK:
			{
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y,           z, 2, textureID, 3, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x,		  y,		   z, 2, textureID, 2, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x,		  y + height,  z, 2, textureID, 1, type, length, height);

				vertex[vertexIterator++] = PackVertexAtbs(x,		  y + height,  z, 2, textureID, 1, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y + height,  z, 2, textureID, 0, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y,           z, 2, textureID, 3, type, length, height);

				break;
			}
	
	
			
			case ECubeFace::FRONT:
			{			
				vertex[vertexIterator++] = PackVertexAtbs(x,          y,          z + 1, 4,	 textureID, 2, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y,          z + 1, 4,	 textureID, 3, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y + height, z + 1, 4,  textureID, 0, type, length, height);
																							 
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y + height, z + 1, 4,  textureID, 0, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x,          y + height, z + 1, 4,	 textureID, 1, type, length, height);
				vertex[vertexIterator++] = PackVertexAtbs(x,          y,          z + 1, 4,	 textureID, 2, type, length, height);

				break;
			}
			case ECubeFace::LEFT:
			{
				vertex[vertexIterator++] = PackVertexAtbs(x, y,          z,		    4,  textureID, 3, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x, y,		     z + depth, 4,  textureID, 2, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x, y + height, z,         4,  textureID, 0, type, depth, height);
																											
				vertex[vertexIterator++] = PackVertexAtbs(x, y + height, z,         4,  textureID, 0, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x, y,          z + depth, 4,  textureID, 2, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x, y + height, z + depth, 4,  textureID, 1, type, depth, height);

				break;
			}
			case ECubeFace::RIGHT:
			{
				vertex[vertexIterator++] = PackVertexAtbs(x + 1, y,			 z,          2, textureID, 2, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + 1, y + height, z,		     2, textureID, 1, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + 1, y,			 z + depth,  2, textureID, 3, type, depth, height);
																												
				vertex[vertexIterator++] = PackVertexAtbs(x + 1, y + height, z,          2, textureID, 1, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + 1, y + height, z + depth,  2, textureID, 0, type, depth, height);
				vertex[vertexIterator++] = PackVertexAtbs(x + 1, y,			 z + depth,  2, textureID, 3, type, depth, height);

				break;
			}
			case ECubeFace::UP:
			{
 				vertex[vertexIterator++] = PackVertexAtbs(x,		   	 y + 1, z,         5,  textureID, 0, type, length, depth);
 				vertex[vertexIterator++] = PackVertexAtbs(x,		  	 y + 1, z + depth, 5,  textureID, 3, type, length, depth);
 				vertex[vertexIterator++] = PackVertexAtbs(x + length,    y + 1, z,		   5,  textureID, 1, type, length, depth);
 
 				vertex[vertexIterator++] = PackVertexAtbs(x + length, y + 1, z,			   5,  textureID, 1, type, length, depth);
 				vertex[vertexIterator++] = PackVertexAtbs(x,          y + 1, z + depth,    5,  textureID, 3, type, length, depth);
 				vertex[vertexIterator++] = PackVertexAtbs(x + length, y + 1, z + depth,    5,  textureID, 2, type, length, depth);



				break;
			}
			case ECubeFace::DOWN:
			{
				vertex[vertexIterator++] = PackVertexAtbs(x,          y, z,         1,  textureID, 0, type, length, depth);
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y, z,         1,  textureID, 1, type, length, depth);
				vertex[vertexIterator++] = PackVertexAtbs(x,          y, z + depth, 1,  textureID, 3, type, length, depth);

				vertex[vertexIterator++] = PackVertexAtbs(x + length, y, z,         1,  textureID, 1, type, length, depth);
				vertex[vertexIterator++] = PackVertexAtbs(x + length, y, z + depth, 1,  textureID, 2, type, length, depth);
				vertex[vertexIterator++] = PackVertexAtbs(x,          y, z + depth, 1,  textureID, 3, type, length, depth);

				break;																					
			}
		}
	}

	//Although we use ECubeFace for readability inside our functions, we need to use literal integers in order to reduce the code to half 
	//And since it's not needed scalability (since we will never have more than six faces), we can use those integers without problem.
	//Each face have a number (that matches ECubeFace) reserved for it and we will use this here.
	//FRONT = 0, BACK = 1, UP = 2, DOWN = 3, LEFT = 4, RIGHT = 5
	//Then, we can cast the integer to the ECubeFace (which will be right) and use this same integer into CALC_INDEX.
	//Also, we can use those functions in whatever order we want.

	void Chunk::CalcFrontAndBackFace(const uint8_t x, const uint32_t y, const uint8_t z, uint8_t type, uint32_t& vertexBufferIterator)
	{
		//Front = 0 and Back = 1
		for (uint8_t i = 0; i < 2; i++)
		{
			uint8_t length = 0, height = 0;
			uint32_t PreviousLength = 0;
			
			//Since the greedy always work with the adjacent block, we will use this to process the last block
			uint32_t cacheY = 0, cacheX = 0;

			ECubeFace face = (ECubeFace)i;
			uint8_t textureID = 0;
			for (uint32_t yy = y; yy < CHUNK_SIZE; yy++)
			{
				cacheY = yy;

				for (uint32_t xx = x; xx < CHUNK_SIZE; xx++)
				{
					cacheX = xx;

					uint32_t PreCalculatedIndex = CALC_INDEX(xx, yy, z, i);
					uint32_t PreCalculatedBlocksIndex = CALC_INDEX_SIMPLE(xx, yy, z);

					//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
					if (!blocks[PreCalculatedBlocksIndex] || (blocks[PreCalculatedBlocksIndex] != blocks[CALC_INDEX_SIMPLE(xx, y, z)] || blocks[PreCalculatedBlocksIndex] != blocks[CALC_INDEX_SIMPLE(x, yy, z)]) || VisitedBlocks[PreCalculatedIndex] || !isFaceVisible(xx, yy, z, face))
						break;
					
	
					//Salvamos falando que o bloco ja foi visitado
					VisitedBlocks[PreCalculatedIndex] = true;
					
	
					textureID =  m_TexturesID[CALC_INDEX(x, y, z, i)];
		
					//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
					length++;
				}
	
				if (yy > 0 && (PreviousLength != length || yy == CHUNK_SIZE))
				{
					GenCubeFace(x, yy - height, z, PreviousLength, height, 1, type, vertexBufferIterator, textureID, face);
					height = 0;
				}
	
				PreviousLength = length;
				length = 0;
	
				height++;
			}

			if (cacheY > 0 && (PreviousLength != length || cacheY == CHUNK_SIZE))
				GenCubeFace(x, (cacheY+1) - height, z, PreviousLength, height, 1, type, vertexBufferIterator, textureID, face);
			
		}

	}
	void Chunk::CalcUpAndDownFace(const uint8_t x, const uint32_t y, const uint8_t z, uint8_t type, uint32_t& vertexBufferIterator)
	{
		//Up = 2 and Down = 3
		for (uint8_t i = 2; i < 4; i++)
		{
			uint8_t length = 0, depth = 0;
			uint32_t PreviousLength = 0;

			//Since the greedy always work with the adjacent block, we will use this to process the last block
			uint32_t cacheZ = 0, cacheX = 0;

			ECubeFace face = (ECubeFace)i;

			uint8_t textureID = 0;

			for (uint32_t zz = z; zz < CHUNK_SIZE; zz++)
			{
				cacheZ = zz;

				for (uint32_t xx = x; xx < CHUNK_SIZE; xx++)
				{
					cacheX = xx;

					uint32_t PreCalculatedIndex = CALC_INDEX(xx, y, zz, i);
					uint32_t PreCalculatedBlocksIndex = CALC_INDEX_SIMPLE(xx, y, zz);
				
					if (!blocks[PreCalculatedBlocksIndex] || (blocks[PreCalculatedBlocksIndex] != blocks[CALC_INDEX_SIMPLE(xx, y, z)] || blocks[PreCalculatedBlocksIndex] != blocks[CALC_INDEX_SIMPLE(x, y, zz)]) || VisitedBlocks[PreCalculatedIndex] || !isFaceVisible(xx, y, zz, face))
						break;

					VisitedBlocks[PreCalculatedIndex] = true;
					textureID = m_TexturesID[CALC_INDEX(x, y, z, i)];
					
					length++;
				}

				if (zz > 0 && (PreviousLength != length || zz == CHUNK_SIZE))
				{
					GenCubeFace(x, y, zz - depth, PreviousLength, 1, depth, type, vertexBufferIterator, textureID, face);
					depth = 0;
				}

				PreviousLength = length;
				length = 0;

				depth++;
			}

			if (cacheZ > 0 && (PreviousLength != length || cacheZ == CHUNK_SIZE))
				GenCubeFace(x, y, (cacheZ + 1) - depth, PreviousLength, 1, depth, type, vertexBufferIterator, textureID, face);
			
		}
	}
	
	void Chunk::CalcRightAndLeftFace(const uint8_t x, const uint32_t y, const uint8_t z, uint8_t type, uint32_t& vertexBufferIterator)
	{
		//Left = 4 and Right = 5
		for (uint8_t i = 4; i < 6; i++)
		{
			uint8_t depth = 0, height = 0;
			uint32_t PreviousDepth = 0;

			//Since the greedy always work with the adjacent block, we will use this to process the last block
			uint32_t cacheZ = 0, cacheY = 0;

			ECubeFace face = (ECubeFace)i;
			uint8_t textureID = 0;

			for (uint32_t yy = y; yy < CHUNK_SIZE; yy++)
			{
				cacheY = yy;

				for (uint32_t zz = z; zz < CHUNK_SIZE; zz++)
				{
					cacheZ = zz;

					uint32_t PreCalculatedIndex = CALC_INDEX(x, yy, zz, i);
					uint32_t PreCalculatedBlockIndex = CALC_INDEX_SIMPLE(x, yy, zz);


					//O bloco é diferente do atual, é vazio ou não visivel? Se sim, não o processe
					if (!blocks[PreCalculatedBlockIndex] || (blocks[PreCalculatedBlockIndex] != blocks[CALC_INDEX_SIMPLE(x, y, zz)] || blocks[PreCalculatedBlockIndex] != blocks[CALC_INDEX_SIMPLE(x, yy, z)]) || VisitedBlocks[PreCalculatedIndex] || !isFaceVisible(x, yy, zz, face))
						break;

					//Salvamos falando que o bloco ja foi visitado
					VisitedBlocks[PreCalculatedIndex] = true;

					textureID = m_TexturesID[CALC_INDEX(x, y, z, i)];

					//Caso não seja, aumentamos o length, ou seja, mais um bloco à direita que cubrimos.
					depth++;
				}

				if (yy > 0 && (PreviousDepth != depth || yy == CHUNK_SIZE))
				{
					GenCubeFace(x, yy - height, z, 1, height, PreviousDepth, type, vertexBufferIterator, textureID, face);
					height = 0;
				}

				PreviousDepth = depth;
				depth = 0;

				height++;
			}

			if (cacheY > 0 && (PreviousDepth != depth || cacheY == CHUNK_SIZE))
				GenCubeFace(x, (cacheY+1) - height, z, 1, height, PreviousDepth, type, vertexBufferIterator, textureID, face);
			
		}
	}
}
