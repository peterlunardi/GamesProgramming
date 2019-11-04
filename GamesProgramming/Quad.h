#pragma once
#include "pch.h"
#include "Vertex.h"

namespace Quad
{
	std::vector<Vertex> quadVertices
	{
		Vertex(glm::vec3( 0.5,   0.5f,  0.0f)), //topRight
		Vertex(glm::vec3( 0.5f, -0.5f,  0.0f)), //bottomRight
		Vertex(glm::vec3(-0.5f, -0.5f,  0.0f)), //bottomLeft
		Vertex(glm::vec3(-0.5f,  0.5f,  0.0f))  //topLeft
	};

	std::vector<int> quadIndices
	{
		0, 3, 1,
		1, 3, 2
	};
}