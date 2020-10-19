#pragma once

#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Maths/bvec4.h"

namespace MC
{
	constexpr uint8_t CHUNK_SIZE = 64;
	constexpr uint8_t CUBE_FACES = 6;
	constexpr uint8_t FACE_VERTICES_NUMBER = 6;

	struct Chunk
	{
	private:
		struct NeighboursChunks
		{
			Chunk* left_Chunk = nullptr;
			Chunk* right_Chunk = nullptr;
			Chunk* upper_Chunk = nullptr;
			Chunk* below_Chunk = nullptr;
			Chunk* front_Chunk = nullptr;
			Chunk* back_Chunk = nullptr;
		};

		enum class ECubeFace : uint8_t { UP = 1, DOWN, FRONT, BACK, LEFT, RIGHT};

		void GenCubeFace(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t length, const uint32_t height, const uint32_t depth, const uint8_t type, uint32_t& vertexIterator, ECubeFace face);
	public:
		Chunk();
		~Chunk();

		uint8_t get(int x, int y, int z);
		void set(int x, int y, int, uint8_t type);

		void update();

		uint8_t blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]; //types of blocks e.g: grass, stone, sand etc
		bvec4 vertex[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * FACE_VERTICES_NUMBER * CUBE_FACES]; //mesh data

		//Set by SuperChunk
		NeighboursChunks nc;

		//Used by Renderer
		uint32_t VBO;
		int elements;
		bool changed;

	private:
		//@TODO: Promote to a pointer. Keep it here so others instances of Chunk will not share this array between them.

		//Turn this to 2D array? Mix all together into a single array
		bool VisitedFront[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool VisitedBack[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool VisitedUp[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool VisitedDown[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool VisitedRight[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool VisitedLeft[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		

		//One function with switch 
		bool IsFaceVisibleFront(const uint32_t x, const uint32_t y, const uint32_t z);
		bool isFaceVisibleBack(const uint32_t x, const uint32_t y, const uint32_t z);
		bool isFaceVisibleUp(const uint32_t x, const uint32_t y, const uint32_t z);
		bool isFaceVisibleDown(const uint32_t x, const uint32_t y, const uint32_t z);
		bool isFaceVisibleRight(const uint32_t x, const uint32_t y, const uint32_t z);
		bool isFaceVisibleLeft(const uint32_t x, const uint32_t y, const uint32_t z);
	};



}