#pragma once
#include "pch.h"
#include "CollisionShape.h"

class CylinderShape : public CollisionShape
{
private:
	glm::vec3 m_halfExtents;
public:
	CylinderShape(glm::vec3 halfExtents);
};

