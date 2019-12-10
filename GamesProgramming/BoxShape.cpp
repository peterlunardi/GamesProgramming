#include "pch.h"
#include "BoxShape.h"

BoxShape::BoxShape(glm::vec3 halfExtents)
{
	m_halfExtents = halfExtents;
	m_shape = new btBoxShape(btVector3(halfExtents.x, halfExtents.y, halfExtents.z));
	m_type = CShapeType::BOX;
}