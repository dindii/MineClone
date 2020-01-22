#pragma once
#include "Block.h"

#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Maths/bvec4.h"

namespace MC
{
	typedef unsigned int GLuint;

	constexpr int CHUNK_SIZE = 16;

	//Criar o enum : uint8_t com os tipos.

	struct Chunk
	{
	public:

		Chunk();
		~Chunk();

		uint8_t get(int x, int y, int z);
		void set(int x, int y, int, uint8_t type);

		void update();

		uint8_t blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]; //types of blocks
		bvec4 vertex[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6 * 6]; //mesh data

		GLuint VBO;
		int elements;
		bool changed;

	};



}