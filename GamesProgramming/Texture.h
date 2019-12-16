#pragma once
#include "pch.h"
#include "Log.h"

class Texture
{
private:
	GLuint m_texture;
	std::string m_directory;
	static GLuint Load(const std::string& directory);

public:
	Texture(std::string path);
	~Texture();
	void Bind();
};
