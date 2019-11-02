#pragma once
#include "MCP/Maths/mat4.h"
#include <string>

namespace MC
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader();

		virtual void Bind();
		virtual void UnBind();
		virtual void UploadUniformMat4(const std::string& name, const mat4& mat);
		virtual void UploadUniformFloat4(const std::string& name, const vec4& mat);

	private:
		uint32_t m_RendererID;


	};
}