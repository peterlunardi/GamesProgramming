#pragma once
#include "pch.h"
#include "Vertex.h"

namespace Quad
{
	std::vector<Vertex> quadVertices
	{
	Vertex(glm::vec3( 0.5,   0.5f, 0.f), glm::vec4(1), glm::vec2(1, 1)), //topRight
	Vertex(glm::vec3( 0.5f, -0.5f, 0.f), glm::vec4(1), glm::vec2(1, 0)), //bottomRight
	Vertex(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec4(1), glm::vec2(0, 0)), //bottomLeft
	Vertex(glm::vec3(-0.5f,  0.5f, 0.f), glm::vec4(1), glm::vec2(0, 1))  //topLeft
	};

	std::vector<int> quadIndices
	{
		0, 3, 1,
		1, 3, 2
	};
}