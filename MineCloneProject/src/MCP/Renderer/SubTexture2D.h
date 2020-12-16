#pragma once

#include "Texture2D.h"
#include "MCP/Maths/vec2.h"

namespace MC
{
	class SubTexture2D
	{
		SubTexture2D(const Texture2D* texture, const vec2& min, const vec2& max);

		const Texture2D* GetTexture() const { return m_Texture; }
		inline const vec2* GetTextCoords() const { return m_TexCoords; }

		static SubTexture2D CreateFromCoords(const Texture2D* texture, const vec2& coords, const vec2& spriteSize);

	private:
		const Texture2D* m_Texture;
		vec2 m_TexCoords[4];
	};



}