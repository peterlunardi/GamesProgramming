#include "pch.h"
#include "Mesh.h"
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices)
{
	m_indices = indices;
	m_vertices = vertices;

	//generate and bind vao so that it keeps the current vbo and ebo and attribs
	GL_ATTEMPT(glGenVertexArrays(1, &m_vao));
	GL_ATTEMPT(glBindVertexArray(m_vao));

	GL_ATTEMPT(glGenBuffers(1, &m_vbo));
	GL_ATTEMPT(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GL_ATTEMPT(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW));

	GL_ATTEMPT(glGenBuffers(1, &m_ebo));
	GL_ATTEMPT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
	GL_ATTEMPT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW));

	//tell the VAO that 0 is the position element
	SetUpAttrib(0, 3, GL_FLOAT, 0);

	//tell the VAO that 1 is the color element
	SetUpAttrib(1, 4, GL_FLOAT, sizeof(glm::vec3));

	//uv
	SetUpAttrib(2, 2, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4));

	//normals
	SetUpAttrib(3, 3, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2));
}
void Mesh::SetUpAttrib(int index, int count, int type, size_t offset)
{
	GL_ATTEMPT(glEnableVertexAttribArray(index));
	GL_ATTEMPT(glVertexAttribPointer(index, count, type, GL_FALSE, sizeof(Vertex), (void**)offset));
}
void Mesh::Bind()
{
	//TODO: don't bind mesh if it has already been bound
	GL_ATTEMPT(glBindVertexArray(m_vao));
}