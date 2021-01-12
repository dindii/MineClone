#pragma once

namespace MC
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		Texture2D(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels = 4);
		Texture2D();

		~Texture2D();

		uint32_t GetWidth()   const { return m_Width; }
		uint32_t GetHeight()  const { return m_Height; }
		uint32_t GetID()      const { return m_RendererID; }
		std::string GetPath()const { return m_Path; }
		virtual void SetData(void* data);

		virtual void Bind(uint32_t slot = 0) const;

		bool operator!() { return m_RendererID == 0 || m_RendererID < 0; }
		bool operator==(const Texture2D& other) const { return (this->m_RendererID == other.GetID()); };
	private:
		void LoadTextureFromData(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels);

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		std::string m_Path;
		uint32_t m_InternalFormat, m_DataFormat;
	};

}