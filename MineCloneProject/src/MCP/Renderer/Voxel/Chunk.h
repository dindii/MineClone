#pragma once
#include "Block.h"

#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Maths/bvec4.h"

namespace MC
{
	typedef unsigned int GLuint;

	constexpr unsigned int CHUNK_SIZE = 16;
	constexpr unsigned int CUBE_FACES = 6;
	constexpr unsigned int FACE_VERTICES_NUMBER = 6;

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
		bvec4 vertex[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * FACE_VERTICES_NUMBER * CUBE_FACES]; //mesh data

		GLuint VBO;
		int elements;
		bool changed;

	};



}