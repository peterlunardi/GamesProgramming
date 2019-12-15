#pragma once
enum SHADER_TYPE
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	GEOMETRY_SHADER = GL_GEOMETRY_SHADER
};

class Shader
{
private:
	GLuint m_shader;

public:
	Shader(const std::string& fileName, SHADER_TYPE type);
	~Shader();
	GLuint Get() { return m_shader; }
	GLuint LoadShaderFromMemory(const char* pMem, SHADER_TYPE type);
	GLuint LoadShaderFromFile(const std::string& fileName, SHADER_TYPE type);
	bool CheckForCompileErrors(const std::string& fileName);
};

