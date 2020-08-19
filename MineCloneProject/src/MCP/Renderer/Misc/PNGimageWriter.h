#pragma once

#include <stdint.h>

namespace MC
{

	//a basic wrapper for STBI PNG writer
	class PNGimageWriter
	{
	public:
		PNGimageWriter(const char* file, const uint32_t& width, const uint32_t& height);
		~PNGimageWriter();

	    void Write();
	    void Set(const float& value);
	    void Set(const int& value);

		inline	uint8_t* GetData() { return m_data; }
		inline	uint32_t getHeight() const { return m_height; }
		inline	uint32_t getWidth()  const { return m_width; }

	private:
		uint32_t m_index;
		uint32_t m_width;
		uint32_t m_height;
		uint8_t* m_data;
		const char* m_filename;
	};


}