#include "pch.h"
#include "Camera.h"

Camera::Camera(Transform* parent, CameraType type)
{
	UpdateCameraVectors();

	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Yaw = YAW;
	Pitch = PITCH;

	m_parentTransform = parent;
	m_type = type;
	switch (m_type)
	{
	case ORTHOGRAPHIC:
		SetProjOrtho(0, (float)WINDOW_W, 0, (float)WINDOW_H, m_nearPlane, m_farPlane);
		break;
	case PERSPECTIVE:
		SetProjPersp(m_fov, m_ratio, m_nearPlane, m_farPlane);
		break;
	}
}

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	forward = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(forward, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, forward));
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;

	if (direction == FORWARD)
		pos += forward * velocity;

	if (direction == BACKWARD)
		pos -= forward * velocity;

	if (direction == LEFT)
		pos -= Right * velocity;

	if (direction == RIGHT)
		pos += Right * velocity;

	if (direction == UP)
		pos += Up * velocity;

	if (direction == DOWN)
		pos -= Up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
	Recalculate();
}

void Camera::Recalculate()
{
	if (m_parentTransform != nullptr)
	{
		m_viewMatrix = glm::lookAt(
			pos,
			pos + forward,
			worldUp
		);

		VP = m_projMatrix * m_viewMatrix;

		m_parentTransform->SetPosition(pos);
	}
}

void Camera::SetProjPersp(float fov, float ratio, float nearPlane, float farPlane)
{
	m_type = CameraType::PERSPECTIVE;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	m_fov = fov;
	m_ratio = ratio;
	pos = m_parentTransform->GetPosition();
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_projMatrix = glm::perspective(fov, ratio, nearPlane, farPlane);
}

void Camera::SetProjOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	m_type = CameraType::ORTHOGRAPHIC; float m_nearPlane = nearPlane;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	m_bottom = bottom;
	m_left = left;
	m_top = top;
	m_right = right;
	m_projMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}
