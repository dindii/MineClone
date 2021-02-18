#pragma once
#include "MCP/Physic/AABB.h"

namespace MC
{
	class AABBCell
	{
	public:
		AABBCell() : m_LeftChild(nullptr), m_RightChild(nullptr) {};
		AABBCell(AABBCell* left, AABBCell* right) : m_LeftChild(left), m_RightChild(right) {};
		~AABBCell() { delete m_LeftChild; delete m_RightChild; }

		inline AABB& GetCollisionComponent() { return m_CollisionVolume; }
		
		private:
		AABB m_CollisionVolume;
		AABBCell* m_LeftChild;
		AABBCell* m_RightChild;
	};


}