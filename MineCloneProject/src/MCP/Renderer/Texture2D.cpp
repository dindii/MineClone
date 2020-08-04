#include "mcpch.h"
#include "Texture2D.h"
#include "stbi/stb_image.h"
#include "MCP/Core.h"
#include "stbi/stb_image.h"
#include <glad/glad.h>
#include "MCP/Utils/Logger.h"

namespace MC
{
		Texture2D::Texture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
		{
			

			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			//	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glBindTexture(GL_TEXTURE_2D, 0);


		}

		Texture2D::Texture2D(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels /*= 4*/)
		{
			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;

			switch (channels)
			{
				case 1:
				{
					internalFormat = GL_R8;
					dataFormat = GL_RED;
					break;
				}
				case 3:
				{
					internalFormat = GL_RGB8;
					dataFormat = GL_RGB;
					break;
				}
				case 4:
				{
					internalFormat = GL_RGBA8;
					dataFormat = GL_RGBA;
					break;
				}
				default:
				{
					MC_LOG_FATAL("Unknown format type!");
					break;
				}
			}


			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			MC_ASSERT((internalFormat & dataFormat));

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // Esse aqui é necessário pro imgui ler a textura e não splitar ela
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		

			glBindTexture(GL_TEXTURE_2D, 0);
		}


		Texture2D::Texture2D(const std::string& path) : m_Path(path)
		{
			int width, height, channels;
			//stbi_set_flip_vertically_on_load(1);
			stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;

			switch (channels)
			{
				case 1:
				{
					internalFormat = GL_R8;
					dataFormat = GL_RED;
					break;
				}
				case 3:
				{
					internalFormat = GL_RGB8;
					dataFormat = GL_RGB;
					break;
				}
				case 4:
				{
					internalFormat = GL_RGBA8;
					dataFormat = GL_RGBA;
					break;
				}
				default:
				{
					MC_LOG_FATAL("Unknown format type!");
					break;
				}
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			MC_ASSERT((internalFormat & dataFormat));

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);
		}

		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &m_RendererID);
		}

		void Texture2D::SetData(void* data, uint32_t size)
		{	
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		}

		void Texture2D::Bind(uint32_t slot) const
		{
			glBindTextureUnit(slot, m_RendererID);
		}

	


}