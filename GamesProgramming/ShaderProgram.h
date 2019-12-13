#pragma once
#include "pch.h"
#include "Shader.h"

class ShaderProgram
{
private:
	//TODO:Track currently active shader
	GLuint m_program;
	Shader* m_vShader, * m_fShader;
	bool CheckForLinkErrors();

public:
	ShaderProgram(const std::string& vShaderFile, const std::string& fShaderFile);
	~ShaderProgram();
	void BindAttribLoc(GLuint loc, const char* name);
	void Link();
	void Use();
	GLuint Get() { return m_program; }

	//FUNCTIONS USED TO SET UNIFORM VARIABLES IN OUR SHADERS----------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(m_program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
};

