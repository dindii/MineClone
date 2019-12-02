#pragma once
#include "Mesh.h"
#include <vector> 
#include <map>

namespace MC
{
	class MeshLoader
	{
	public:
		static Mesh loadOBJFile(const char* path);
		
	private:
		static Mesh indexBuffer(Mesh& data);
		static bool getSimilarVertex(MeshData& data, std::map<MeshData, unsigned int>& vertexToIndex, unsigned int& result);
		static Mesh combineAttribs(Mesh& data);
	};
}