#pragma once
#include "pch.h"
#include "CollisionShape.h"

class SphereShape : public CollisionShape
{
private:
	
	float m_radius;

public:

	SphereShape(float radius);
};

