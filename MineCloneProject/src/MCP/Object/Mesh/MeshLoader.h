#pragma once
#include <vector> 
#include "MCP/Maths/vec3.h"
#include "MCP/Maths/vec2.h"
#include <map>


namespace MC
{
	struct MeshData
	{
		MeshData() = default;
		MeshData(vec3 VertexPos, vec3 NormalDir, vec2 UV) : Vertex(VertexPos), Normal(NormalDir), TextureCoods(UV) {};

		//para conseguirmos usar o Map
		inline bool operator<(const MeshData data) const { return memcmp((void*)this, (void*)&data, sizeof(data)) < 0; }

		vec3 Vertex;
		vec3 Normal;
		vec2 TextureCoods;
	};

	struct Mesh
	{
		std::vector<MeshData> Data;		
		std::vector<unsigned int> indices;
	};

	class MeshLoader
	{
	public:
		static Mesh loadOBJFile(const char* path);
		
	private:
		static Mesh indexBuffer(Mesh& data);
		static bool getSimilarVertex(MeshData& data, std::map<MeshData, unsigned int>& vertexToIndex, unsigned int& result);
	};
}