#include "mcpch.h"
#include "Texture2D.h"
#include "stbi/stb_image.h"
#include "MCP/Core.h"
#include "stbi/stb_image.h"
#include <glad/glad.h>
#include "MCP/Utils/Logger.h"

namespace MC
{
		Texture2D::Texture2D() : m_Width(0), m_Height(0), m_InternalFormat(0), m_DataFormat(0), m_RendererID(0)
		{
			//If someone's misses to set a texture, will display a nice placeholder
			LoadErrorTexture();
		}

		void Texture2D::LoadErrorTexture()
		{
			int width, height, channels;
			stbi_uc* data = stbi_load("../MineCloneProject/res/Textures/texerror.png", &width, &height, &channels, 0);

			m_Width = width;
			m_Height = height;

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;


			glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);
		}


		Texture2D::Texture2D(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels /*= 4*/)
		{
			if (!data)
			{
				MC_LOG_ERROR("Could not load the texture!");
				LoadErrorTexture();
				return;
			}

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
					MC_LOG_ERROR("Unknown texture format type!");
					LoadErrorTexture();
					return;
				}
			}

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

			if (channels == 1)
			{
				// Parameters to avoid ImGui messing up grayscale textures.	
				// This will make sure that the ImGui's shader can output
				// Color(val, val, val, 1.0) instead of Color(1.0, 0.0, 0.0, 1.0).
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_R, GL_RED);
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_G, GL_RED);
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_B, GL_RED);
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_A, GL_ONE);
			}

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
			//This will give support to every dimension, even those that aren't even.
			if(! ( (width % 2) == 0) )
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		
			glBindTexture(GL_TEXTURE_2D, 0);
		}


		Texture2D::Texture2D(const std::string& path) : m_Path(path)
		{
			int width = 0, height = 0, channels = 0;
			stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

			if (!data)
			{
				MC_LOG_ERROR("Could not load the texture!");
				LoadErrorTexture();
				return;
			}

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
					MC_LOG_ERROR("Unknown texture format type!");
					LoadErrorTexture();
					return;	
				}
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

			if (channels == 1)
			{
				// Parameters to avoid ImGui messing up grayscale textures.	
		     	// This will make sure that the ImGui's shader can output
			    // Color(val, val, val, 1.0) instead of Color(1.0, 0.0, 0.0, 1.0).
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_R, GL_RED);
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_G, GL_RED);
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_B, GL_RED);
				glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_A, GL_ONE);
			}


			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//This will give support to every dimension, even those that aren't even.
			if (!((width % 2) == 0))
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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