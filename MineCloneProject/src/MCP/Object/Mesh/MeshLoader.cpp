#include "mcpch.h"
#include "MeshLoader.h"
#include "MCP/Utils/Logger.h"

#include <fstream>
#include <sstream>
#include <string>

namespace MC
{
	//TODO@: Load into a buffer and then parse the buffer
	Mesh MeshLoader::loadOBJFile(const char* path)
	{
		std::ifstream source(path, std::ifstream::binary);

		if (!source)
		{
			MC_LOG_ERROR("Can't load .OBJ file!");
		}

		std::vector<vec3> verticesTemp;
		std::vector<vec2> UVTemp;
		std::vector<vec3> NormalsTemp;

		std::vector<unsigned int> verticesIndices, normalsIndices, UVIndices;

		Mesh data;

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

			index = UVIndices[x];
			vec2 textureCoord = UVTemp[index - 1];

			index = normalsIndices[x];
			vec3 normalPos = NormalsTemp[index - 1];

			MeshData md(vertexPos, normalPos, textureCoord);
			data.Data.push_back(md);
		}
		
		//Tira os valores repetidos mas repete o index deles no buffer, para criar o indexed buffer.
		return indexBuffer(data);

	}


	Mesh MeshLoader::indexBuffer(Mesh& data)
	{
		Mesh outData;

		std::map<MeshData, unsigned int> vertexToIndex;

		for (unsigned int x = 0; x < data.Data.size(); x++)
		{
			MeshData intermediate = data.Data[x];
	

			unsigned int index;

			bool found = getSimilarVertex(intermediate, vertexToIndex, index);

			if (found)
				outData.indices.push_back(index);
			else
			{
				MeshData md(data.Data[x].Vertex, data.Data[x].Normal, data.Data[x].TextureCoods);
				outData.Data.push_back(md);
				unsigned int newIndex = (unsigned int)outData.Data.size() - 1;
				outData.indices.push_back(newIndex);
				vertexToIndex[intermediate] = newIndex;
			}
		}

		data = outData;
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

}