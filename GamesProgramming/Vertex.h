#pragma once
#include "pch.h"
#include "Log.h"

struct Vertex
{
	glm::vec3 pos		= glm::vec3(0, 0, 0);
	glm::vec4 color		= glm::vec4(0, 0, 0, 0);
	glm::vec2 texture	= glm::vec2(0, 0);
	glm::vec3 normal	= glm::vec3(0, 0, 0);

	Vertex() {}
	Vertex(glm::vec3 p)
	{
		pos = p;
	}

	Vertex(glm::vec3 p, glm::vec4 c) : Vertex(p)
	{
		color = c;
	}

	Vertex(glm::vec3 p, glm::vec4 c, glm::vec2 t) : Vertex(p, c)
	{
		texture = t;
	}

	Vertex(glm::vec3 p, glm::vec4 c, glm::vec2 t, glm::vec3 n) : Vertex(p, c, t)
	{
		normal = n;
	}
};