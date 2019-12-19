#pragma once
#include "Mesh.h"
#include <vector> 
#include <map>
#include "MCP/Core.h"

namespace MC
{
	class MeshLoader
	{
	public:
		static Ref<Mesh> loadOBJFile(const char* path, bool batched = false);
		
	private:
		static Ref<MeshBuffers> indexBuffer(Ref<MeshBuffers> data);
		static bool getSimilarVertex(MeshData& data, std::map<MeshData, unsigned int>& vertexToIndex, unsigned int& result);
		static Ref<Mesh> batchAttribs(Ref<MeshBuffers> data);
		static Ref<Mesh> combineAttribs(Ref<MeshBuffers> data);
	};
}