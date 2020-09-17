#pragma once

#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Maths/bvec4.h"

namespace MC
{
	constexpr uint8_t CHUNK_SIZE = 16;
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

		void GenCubeFace(const int x, const int y, const int z, const uint8_t type, uint32_t& vertexIterator, ECubeFace face);
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
	};



}