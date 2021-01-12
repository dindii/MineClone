#pragma once

#include "MCP/Renderer/Shader/Shader.h"
#include "MCP/Maths/bvec4.h"
#include "MCP/Renderer/Texture2D.h"

namespace MC
{
	//#TODO: Make a global function to change the size of the chunk and superchunk
	constexpr uint8_t CHUNK_SIZE = 15;
	constexpr uint8_t CUBE_FACES = 6;
	constexpr uint8_t FACE_VERTICES_NUMBER = 6;

	struct Chunk
	{
	private:
		//We keep track of the neighbours chunks in order to cull the edges of the actual chunk
		//i.e: even if a block is in the limit of the actual chunk, we don't render it if theres a neighbour chunk (he wouldn't be visible)
		struct NeighboursChunks
		{
			Chunk* left_Chunk =  nullptr;
			Chunk* right_Chunk = nullptr;
			Chunk* upper_Chunk = nullptr;
			Chunk* below_Chunk = nullptr;
			Chunk* front_Chunk = nullptr;
			Chunk* back_Chunk =  nullptr;
		};

		//Some internal functions will use this system to be more readable, although, the order its important and will be taken into account. (FRONT = 0 ...)
		enum  ECubeFace : uint8_t { FRONT, BACK, UP, DOWN, LEFT, RIGHT};

	public:
		Chunk();
		~Chunk();

		//Get a type of a specific block
		uint8_t get(int x, int y, int z);

		//Set a type of a specific block
		void set(int x, int y, int, uint8_t type, const Texture2D* texture);

		//Regen the current chunk, this will be called if we detect changes in the chunk
		void update();


		//Our actual neighbours chunks, this will be set by the SuperChunk class who will own this Chunk and will have sight of the other chunks as a whole
		NeighboursChunks nc;

		//Mesh and OpenGL details, this will be used by the Renderer and it will possibly be abstracted away further
		uint32_t VBO;
		int elements;
		bool changed;

		//Our actual mesh data. Explanation on why the "+1" below.
		uint32_t vertex[(CHUNK_SIZE+1) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1) * FACE_VERTICES_NUMBER * CUBE_FACES];
	private:
		/**
		* @brief This function is reponsible to build the face in our vertex array, it generates 6 vertices based on the actual arguments.
		* @param x, y and z - The position in the world of the vertex
		* @param height, depth and length - This is sent by the greedy vertex algorithm and will determine the size of the face ( x + width, y + height, z + depth)
		* @param type - Type of the block (dirt, grass, stone, custom etc...), this is sent by the face calculations functions.
		* @param vertexIterator - A reference, it's the actual position in the vertex array. Each vertex adds + 1 in this iterator, for each face we have + 6 on it.
		  it's also used to check how many elements we have at the end, saving us of batching non-existent blocks
		* @param face - Since this can generate all the six faces, we can choose which face we want to gen. e.g: ECubeFace::FRONT
		*/
		void GenCubeFace(const uint8_t x, const uint32_t y, const uint8_t z, const uint8_t length, const uint32_t height, const uint8_t depth,
						 const uint8_t type, uint32_t& vertexIterator, ECubeFace face);


		uint32_t PackVertexAtbs(const uint8_t x, const uint32_t y, const uint8_t z, const uint8_t normalLight, const uint8_t textureID, const uint8_t textureCoordsIndex, const uint8_t type);

		/**
		* @brief This function checks if a face is visible or not, this is, check if the face is in a border and if it is, check if there's a chunk next and if it's face is active
		  or not.
		* @param x, y and z - The block coords in the chunk (not world coords!)
		* @param face - Since this can generate all the six faces, we can choose which face we want to gen. e.g: ECubeFace::FRONT
		*/
		bool isFaceVisible(const uint8_t x, const uint32_t y, const uint8_t z, ECubeFace face);


		/**
		* @brief This function is reponsible for calculating the Greedy Meshing Voxel algorithm of Front and Back face,
		  it checks a bunch of things to verify how far can a face be optmized 
		* @param x, y and z - The block coords in the chunk (not world coords!)
		* @param type - Type of the block (dirt, grass, stone, custom etc...), this will be sent for "GenCubeFace" function.
		* @param vertexIterator - A reference, it's the actual position in the vertex array. Each vertex adds + 1 in this iterator, for each face we have + 6 on it.
		  it's also used to check how many elements we have at the end, saving us of batching non-existent blocks
	    */
		void CalcFrontAndBackFace(const uint8_t x, const uint32_t y, const uint8_t z, uint8_t type, uint32_t& vertexBufferIterator);

		/**
		* @brief This function is reponsible for calculating the Greedy Meshing Voxel algorithm of Up and Down face,
		  it checks a bunch of things to verify how far can a face be optmized
		* @param x, y and z - The block coords in the chunk (not world coords!)
		* @param type - Type of the block (dirt, grass, stone, custom etc...), this will be sent for "GenCubeFace" function.
		* @param vertexIterator - A reference, it's the actual position in the vertex array. Each vertex adds + 1 in this iterator, for each face we have + 6 on it.
		  it's also used to check how many elements we have at the end, saving us of batching non-existent blocks
		*/
		void CalcUpAndDownFace   (const uint8_t x, const uint32_t y, const uint8_t z, uint8_t type, uint32_t& vertexBufferIterator);

		/**
		* @brief This function is reponsible for calculating the Greedy Meshing Voxel algorithm of Right and Left face,
		  it checks a bunch of things to verify how far can a face be optmized
		* @param x, y and z - The block coords in the chunk (not world coords!)
		* @param type - Type of the block (dirt, grass, stone, custom etc...), this will be sent for "GenCubeFace" function.
		* @param vertexIterator - A reference, it's the actual position in the vertex array. Each vertex adds + 1 in this iterator, for each face we have + 6 on it.
		  it's also used to check how many elements we have at the end, saving us of batching non-existent blocks
		*/
		void CalcRightAndLeftFace(const uint8_t x, const uint32_t y, const uint8_t z, uint8_t type, uint32_t& vertexBufferIterator);




		//Contains our actual blocks. If 0 then the block does not exist.
		//Our Greedy Voxel Meshing is always one block behind, so if we want to use ALL blocks of CHUNK_SIZE we must use CHUNK_SIZE+1
		//e.g: 16 of CHUNK_SIZE would result in 15 blocks generated. But 17 would result in 16.
		//There's no problem with this because the additional block are never going to be generated, avoiding geometry clipping.
		uint8_t blocks[CHUNK_SIZE+1][CHUNK_SIZE+1][CHUNK_SIZE+1];

		uint8_t m_TexturesID[CHUNK_SIZE + 1][CHUNK_SIZE + 1][CHUNK_SIZE + 1];
		
		

		//Our visited blocks for every face. They are combined in one single array.
		bool VisitedBlocks[((CHUNK_SIZE + 1) * (CHUNK_SIZE + 1) * (CHUNK_SIZE + 1) * CUBE_FACES)];
	};
}