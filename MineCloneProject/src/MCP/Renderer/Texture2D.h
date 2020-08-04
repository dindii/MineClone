#pragma once

namespace MC
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		Texture2D(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels = 4);
		Texture2D(uint32_t width, uint32_t height);
		~Texture2D();

		uint32_t GetWidth()   const { return m_Width; }
		uint32_t GetHeight()  const { return m_Height; }
		uint32_t GetID()      const { return m_RendererID; }

		virtual void SetData(void* data, uint32_t size);

		virtual void Bind(uint32_t slot = 0) const;

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		std::string m_Path;
		uint32_t m_InternalFormat, m_DataFormat;
	};

}