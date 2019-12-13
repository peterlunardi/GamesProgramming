#include "pch.h"
#include "SphereShape.h"

SphereShape::SphereShape(float radius)
{
	m_radius = radius;
	m_shape = new btSphereShape(radius);
	m_type = CShapeType::SPHERE;
}
