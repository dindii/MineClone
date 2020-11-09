#pragma once

#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Maths/bvec4.h"

namespace MC
{
	//funções para setar o chunk size globalmente
	constexpr uint8_t CHUNK_SIZE = 16;
	constexpr uint8_t CUBE_FACES = 6;
	constexpr uint8_t FACE_VERTICES_NUMBER = 6;

	struct Chunk
	{
	private:
		struct NeighboursChunks
		{
			Chunk* left_Chunk =  nullptr;
			Chunk* right_Chunk = nullptr;
			Chunk* upper_Chunk = nullptr;
			Chunk* below_Chunk = nullptr;
			Chunk* front_Chunk = nullptr;
			Chunk* back_Chunk =  nullptr;
		};

		enum class ECubeFace : uint8_t { UP = 1, DOWN, FRONT, BACK, LEFT, RIGHT};

	public:
		Chunk();
		~Chunk();

		uint8_t get(int x, int y, int z);
		void set(int x, int y, int, uint8_t type);

		void update();

		//#TODO: enum class, setter and getter
		//All of those who are + 1 it's because the greedy algorithm that needs to use the 0 index of them for position but at the same time it needs one more index
		// of the array so the CHUNK_SIZE can be completely evaluated (since the key attribute as length or height is always one before the rest),
		//With this, we can make a chunks with properly e.g 32 blocks round
		uint8_t blocks[CHUNK_SIZE+1][CHUNK_SIZE+1][CHUNK_SIZE+1]; //types of blocks e.g: grass, stone, sand etc

		bvec4 vertex[(CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1) * FACE_VERTICES_NUMBER * CUBE_FACES]; //mesh data

		//Set by SuperChunk
		NeighboursChunks nc;

		//Used by Renderer
		uint32_t VBO;
		int elements;
		bool changed;

	private:
		bool VisitedBlocks[((CHUNK_SIZE + 1) * (CHUNK_SIZE + 1) * (CHUNK_SIZE + 1) * CUBE_FACES)];
		

		void GenCubeFace(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t length, const uint32_t height, const uint32_t depth,
		const uint8_t type, uint32_t& vertexIterator, ECubeFace face);

		bool isFaceVisible(const uint32_t x, const uint32_t y, const uint32_t z, ECubeFace face, Chunk* chunkTarget);

		void GreedyFrontFace( const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget);
		void GreedyBackFace ( const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget);
		void GreedyUpFace   ( const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget);
		void GreedyDownFace ( const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget);
		void GreedyRightFace( const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget);
		void GreedyLeftFace ( const uint32_t x, const uint32_t y, const uint32_t z, uint32_t& vertexBufferIterator, Chunk* chunkTarget);
	};
}