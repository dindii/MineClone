#include "mcpch.h"
#include "Shader.h"
#include <glad/glad.h>
#include "MCP/Utils/Logger.h"

namespace MC
{
	
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		//Vertex

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		int compiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			
			MC_LOG_ERROR(infoLog.data());
			MC_ASSERT(false, "Vertex shader compilation failure! ");
			return;
		}

		//Fragment

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			MC_LOG_ERROR(infoLog.data());
			MC_ASSERT(false, "Fragment shader compilation failure! ");

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		int isLinked = 0;

		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (!isLinked)
		{
			int maxLenght = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLenght);

			std::vector<GLchar> infoLog(maxLenght);
			glGetProgramInfoLog(m_RendererID, maxLenght, &maxLenght, &infoLog[0]);

			glDeleteProgram(m_RendererID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			MC_LOG_ERROR(infoLog.data());
			MC_ASSERT(false, "Shader link failure!");
			return;

		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const mat4& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat.elements[0]);
		
	}

	void Shader::UploadUniformFloat4(const std::string& name, const vec4& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniform4f(location, mat.x, mat.y, mat.z, mat.w);
	}

}