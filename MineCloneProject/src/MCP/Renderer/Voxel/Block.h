#include <stdint.h>

namespace MC
{
	enum class BlockType : uint8_t
	{
		MC_Default = 0,
		MC_Grass,
	};

	class Block
	{
	public:
		Block() : m_BlockType(BlockType::MC_Default), m_Active(true) {};
		~Block() = default;

		inline bool isActive() const { return m_Active; };
		inline bool setActive(const bool& active) { m_Active = active; }

	private:
		bool m_Active;
		BlockType m_BlockType;
	};

}