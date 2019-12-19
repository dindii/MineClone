#include "mcpch.h"
#include "MeshLoader.h"
#include "MCP/Utils/Logger.h"

#include <fstream>
#include <sstream>
#include <string>

#include <memory>

#include "MCP/Core.h"

namespace MC
{
	//TODO@: Throw a warning if vectors don't have the same size
	//TODO@: Load into a buffer and then parse the buffer
	Ref<Mesh> MeshLoader::loadOBJFile(const char* path, bool batched)
	{
		std::ifstream source(path, std::ifstream::binary);

		if (!source)
		{
			MC_LOG_ERROR("Can't load .OBJ file!");
			return 0;
		}
		
		std::vector<vec3> verticesTemp;
		std::vector<vec2> UVTemp;
		std::vector<vec3> NormalsTemp ;
	
		std::vector<unsigned int>	verticesIndices;
		std::vector<unsigned int>	normalsIndices ;
		std::vector<unsigned int>	UVIndices;

		Ref<MeshBuffers> data(new MeshBuffers());

		for (std::string line; std::getline(source, line); )
		{
			std::istringstream in(line);

			std::string type;

			in >> type;
	
			float a, b, c;

			if (type == "v")
			{
				in >> a >> b >> c;
				verticesTemp.push_back({ a, b, c });
			}
			else if (type == "vt")
			{
				in >> a >> b;
				UVTemp.push_back({ a, b });
			}
			else if (type == "vn")
			{
				in >> a >> b >> c;
				NormalsTemp.push_back({ a, b, c });
			}

			else if (type == "f")
			{
				//Vertex, Texture Coords and Normal Indices
				unsigned int VIndices[3], TIndices[3], NIndices[3];

				char slash;
				in >> VIndices[0] >> slash >> TIndices[0] >> slash >> NIndices[0];
				in >> VIndices[1] >> slash >> TIndices[1] >> slash >> NIndices[1];
				in >> VIndices[2] >> slash >> TIndices[2] >> slash >> NIndices[2];

				for (unsigned int x = 0; x < 3; x++)
				{
					verticesIndices.push_back(VIndices[x]);
					UVIndices.push_back(TIndices[x]);
					normalsIndices.push_back(NIndices[x]);
				}
			}

		}

		
		for (unsigned int x = 0; x < verticesIndices.size(); x++)
		{
			unsigned int index = verticesIndices[x];
			vec3 vertexPos = verticesTemp[index - 1];
			data->Mesh_Vertices.push_back(vertexPos);

			index = UVIndices[x];
			vec2 textureCoord = UVTemp[index - 1];
			data->Mesh_UVs.push_back(textureCoord);

			index = normalsIndices[x];
			vec3 normalPos = NormalsTemp[index - 1];
			data->Mesh_Normals.push_back(normalPos);
		}
		

		//Tira os valores repetidos mas repete o index deles no buffer, para criar o indexed buffer.
		indexBuffer(data);

		//Juntar em um vector só
		if (batched)
			return batchAttribs(data);

		else
			return combineAttribs(data);
	}


	Ref<MeshBuffers> MeshLoader::indexBuffer(Ref<MeshBuffers> data)
	{
		MeshBuffers outData;

		std::map<MeshData, unsigned int> vertexToIndex;

		MeshData int_Data;

		for (unsigned int x = 0; x < data->Mesh_Vertices.size(); x++)
		{
			int_Data.Vertex = data->Mesh_Vertices[x];
			int_Data.TextureCoods = data->Mesh_UVs[x];
			int_Data.Normal = data->Mesh_Normals[x];
	

			unsigned int index;

			bool found = getSimilarVertex(int_Data, vertexToIndex, index);

			if (found)
				outData.indices.push_back(index);
			
			else
			{
				outData.Mesh_Vertices.push_back(data->Mesh_Vertices[x]);
				outData.Mesh_Normals.push_back(data->Mesh_Normals[x]);
				outData.Mesh_UVs.push_back(data->Mesh_UVs[x]);

				unsigned int newIndex = (unsigned int)outData.Mesh_Vertices.size() - 1;
				outData.indices.push_back(newIndex);
				vertexToIndex[int_Data] = newIndex;
			}
		}

		*data = outData;
		return data;

	}

	bool MeshLoader::getSimilarVertex(MeshData& data, std::map<MeshData, unsigned int>& vertexToIndex, unsigned int& result)
	{
		std::map<MeshData, unsigned int>::iterator it = vertexToIndex.find(data);

		if (it == vertexToIndex.end())
			return false;
		else
		{
			result = it->second;
			return true;
		}

	}

	//@TODO: Tomar conta do numero de atributos para caso houver mais no futuro.

	Ref<Mesh> MeshLoader::batchAttribs(Ref<MeshBuffers> data)
	{
		for (uint32_t x = 0; x < data->Mesh_Vertices.size()  ; x++)
		{
 				data->Mesh_Attributes.push_back(data->Mesh_Vertices[x].x);
 				data->Mesh_Attributes.push_back(data->Mesh_Vertices[x].y);
 				data->Mesh_Attributes.push_back(data->Mesh_Vertices[x].z);
		}

		for (uint32_t x = 0; x < data->Mesh_Vertices.size(); x++)
		{
				data->Mesh_Attributes.push_back(data->Mesh_Normals[x].x);
				data->Mesh_Attributes.push_back(data->Mesh_Normals[x].y);
				data->Mesh_Attributes.push_back(data->Mesh_Normals[x].z);
		}

		for (uint32_t x = 0; x < data->Mesh_Vertices.size(); x++)
		{
				data->Mesh_Attributes.push_back(data->Mesh_UVs[x].x);
				data->Mesh_Attributes.push_back(data->Mesh_UVs[x].y);
		}							 

		Ref<Mesh> orderedMesh(new Mesh());

		orderedMesh->setMeshIndices(data->indices);
		orderedMesh->setMeshData(data->Mesh_Attributes);

		return orderedMesh;
	}

	MC::Ref<Mesh> MeshLoader::combineAttribs(Ref<MeshBuffers> data)
	{
		for (uint32_t x = 0; x < data->Mesh_Vertices.size(); x++)
		{
			data->Mesh_Attributes.push_back(data->Mesh_Vertices[x].x);
			data->Mesh_Attributes.push_back(data->Mesh_Vertices[x].y);
			data->Mesh_Attributes.push_back(data->Mesh_Vertices[x].z);
									 
			data->Mesh_Attributes.push_back(data->Mesh_Normals[x].x);
			data->Mesh_Attributes.push_back(data->Mesh_Normals[x].y);
			data->Mesh_Attributes.push_back(data->Mesh_Normals[x].z);
									  
			data->Mesh_Attributes.push_back(data->Mesh_UVs[x].x);
			data->Mesh_Attributes.push_back(data->Mesh_UVs[x].y);
		}

		MC::Ref<Mesh> orderedMesh(new Mesh());

		orderedMesh->setMeshIndices(data->indices);
		orderedMesh->setMeshData(data->Mesh_Attributes);

		return orderedMesh;
	}

}