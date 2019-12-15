#include "ConeShape.h"

ConeShape::ConeShape(float radius, float height)
{
	m_radius = radius;
	m_height = height;
	m_shape = new btConeShape(btScalar(radius), btScalar(height));
	m_type = CShapeType::CONE;
}
