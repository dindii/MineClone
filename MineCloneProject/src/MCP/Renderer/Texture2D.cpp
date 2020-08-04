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

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			switch (channels)
			{
				case 1:
				{
					internalFormat = GL_R8;
					dataFormat = GL_RED;

					/*    Por mais que seja uma imagem de apenas um canal (grayscale), o imgui estava setando o vec4 de cor para esses dados
						  então, haviamos no fim, uma cor (N, 0, 0, 0) fazendo com que saísse com um color tint vermelho. Com essa função
						  podemos aplicar para os outros canais, o mesmo valor de N, ficando então (N, N, N, 1) e obtemos o resultado desejado.
					*/
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_R, GL_RED);
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_G, GL_RED);
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_B, GL_RED);
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_A, GL_ONE);

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

			glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		

			// Necessário pro imgui ler a textura e não pular a row muito tarde
			// Um setup adicional necessário se caso os dados foram gerados por nós e estejam crus 
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

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

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			switch (channels)
			{
				case 1:
				{
					internalFormat = GL_R8;
					dataFormat = GL_RED;

					/*    Por mais que seja uma imagem de apenas um canal (grayscale), o imgui estava setando o vec4 de cor para esses dados
						  então, haviamos no fim, uma cor (N, 0, 0, 0) fazendo com que saísse com um color tint vermelho. Com essa função
						  podemos aplicar para os outros canais, o mesmo valor de N, ficando então (N, N, N, 1) e obtemos o resultado desejado.
					*/
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_R, GL_RED);
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_G, GL_RED);
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_B, GL_RED);
					glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_A, GL_ONE);

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