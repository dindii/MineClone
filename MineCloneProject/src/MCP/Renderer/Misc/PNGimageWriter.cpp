#include "mcpch.h"
#include "PNGimageWriter.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi/stb_image.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

#include "MCP/Utils/Logger.h"
#include "MCP/Maths/Maths.h"


namespace MC
{
	PNGimageWriter::PNGimageWriter(const char* file, const uint32_t& width, const uint32_t& height) : m_filename(file), m_width(width), m_height(height),
		m_data(nullptr)
	{
		m_data = new uint8_t[m_width * m_height];
		m_index = (m_height * m_width) - 1;
	}

	PNGimageWriter::~PNGimageWriter()
	{
		delete[] m_data;
	}

	void PNGimageWriter::Write()
	{
		stbi_write_png(m_filename, m_width, m_height, 1, m_data, m_width);
	}

	//#TODO: Fix error for non-equal terrain
	void PNGimageWriter::Set(const float& value)
	{
		if ((m_index >= 0))
			m_data[m_index--] = floatToByte(value);
	}

	void PNGimageWriter::Set(const int& value)
	{
		if ((m_index >= 0))
			m_data[m_index--] =  clamp(0, 255, value);
	}

	void PNGimageWriter::Set(const uint32_t x, const uint32_t y, const float value)
	{
		m_data[x * m_width + y] = floatToByte(value);
	}

}