#pragma once
#include "Log.h"
#include "Vertex.h"
#include "ShaderProgram.h"

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;
	GLuint m_vao, m_ebo, m_vbo;

public:
	Mesh(std::vector<Vertex> Vertices, std::vector<int> indices);
	void SetUpAttrib(int index, int count, int type, size_t offset);
	void Bind();
	int GetIndiciesCount() { return (int)m_indices.size(); }
};

