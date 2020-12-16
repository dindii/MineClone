#include "mcpch.h"
#include "SubTexture2D.h"


namespace MC
{
	SubTexture2D::SubTexture2D(const Texture2D* texture, const vec2& min, const vec2& max)
		: m_Texture(texture)
	{

	}

	SubTexture2D SubTexture2D::CreateFromCoords(const Texture2D* texture, const vec2& coords, const vec2& spriteSize)
	{
	
		vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
		vec2 max = {((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight()};


		return SubTexture2D(texture, min, max);
	}

}