#pragma once
#include "pch.h"
#include "Log.h"

struct InputState
{
	InputState()
	{
		keys.fill(false);
	}

	std::array<char, 400> keys;
	glm::ivec2 mousePos;
};
