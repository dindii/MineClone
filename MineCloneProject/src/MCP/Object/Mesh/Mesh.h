#pragma once
#include "MCP/Maths/vec3.h"
#include "MCP/Maths/vec2.h"
#include <map>
#include <vector>

namespace MC
{
	struct MeshData
	{
		MeshData() = default;
		MeshData(vec3 VertexPos, vec3 NormalDir, vec2 UV) : Vertex(VertexPos), Normal(NormalDir), TextureCoods(UV) {};

		//para que consigamos usar o Map
		inline bool operator<(const MeshData data) const { return memcmp((void*)this, (void*)&data, sizeof(data)) > 0; }

		vec3 Vertex;
		vec3 Normal;
		vec2 TextureCoods;
	};

	struct Mesh
	{
		//Debug purpose
		std::vector<vec3> Mesh_Vertices;
		std::vector<vec3> Mesh_Normals;
		std::vector<vec2> Mesh_UVs;
		//Debug purpose

		std::vector<float> Mesh_Attributes;

		std::vector<unsigned int> indices;
	};
}