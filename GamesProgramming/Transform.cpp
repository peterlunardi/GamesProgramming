#include "pch.h"
#include "Transform.h"
glm::mat4 Transform::UpdateTransform()
{
	m_transformMatrix = glm::translate(glm::mat4(1.f), m_position);
	glm::mat4 currentRotate = glm::mat4_cast(m_rotation);
	m_transformMatrix = m_transformMatrix * currentRotate;
	m_transformMatrix = scale(m_transformMatrix, m_scale);

	m_forward = glm::normalize(glm::rotate(m_rotation, glm::vec3(0, 0, -1)));
	m_up = glm::normalize(glm::rotate(m_rotation, glm::vec3(0, 1, 0)));
	m_right = glm::normalize(glm::rotate(m_rotation, glm::vec3(1, 0, 0)));

	m_isDirty = false;
	return m_transformMatrix;
}

Transform::Transform()
{
}

Transform::Transform(glm::vec3 pos) : Transform()
{
	m_position = pos;
}

Transform::Transform(glm::vec3 pos, glm::quat rot) : Transform(pos)
{
	m_rotation = rot;
}

Transform::Transform(glm::vec3 pos, glm::quat rot, glm::vec3 scale) :
	Transform(pos, rot)
{
	m_scale = scale;
}

void Transform::RotateEulerAxis(float angle, glm::vec3 axis)
{
	axis = glm::normalize(axis);
	glm::quat rot = glm::angleAxis(glm::radians(-angle), axis);
	m_rotation = rot * m_rotation;
	m_isDirty = true;
}