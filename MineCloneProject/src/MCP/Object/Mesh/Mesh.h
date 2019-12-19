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

	//Como eu preciso ter os buffers para oganiza-los em um só buffer, deixa-los em Mesh iria aumentar muito o tamanho de cada Mesh sendo que eu só preciso deles para o ordering
	//então criei o MeshBuffers para servir à  Mesh.
	struct MeshBuffers
	{
		std::vector<vec3> Mesh_Vertices;
		std::vector<vec3> Mesh_Normals;
		std::vector<vec2> Mesh_UVs;

		std::vector<float> Mesh_Attributes;

		std::vector<unsigned int> indices;
	};

	struct Mesh
	{
		std::vector<float> getMeshData() const { return Mesh_Attributes; }
		std::vector<unsigned int> getMeshIndices() const { return indices; }

		void setMeshData(std::vector<float>& data) { Mesh_Attributes = data; }
		void setMeshIndices(std::vector<unsigned int>& indicesData) { indices = indicesData; }
	private:
		std::vector<float> Mesh_Attributes;
		std::vector<unsigned int> indices;
	};
}