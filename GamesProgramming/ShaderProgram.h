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
};

