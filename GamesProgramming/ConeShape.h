#pragma once
#include "pch.h"
#include "CollisionShape.h"

class ConeShape : public CollisionShape
{
private:
	float m_radius;
	float m_height;

public:
	ConeShape(float radius, float height);
};

