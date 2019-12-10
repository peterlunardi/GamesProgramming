#pragma once
#include "pch.h"
#include "Log.h"
#include "Transform.h"
#include "Application.h"

enum CameraType { PERSPECTIVE, ORTHOGRAPHIC };
enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

//Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.0f;
const float SENSITIVITY = 0.1f;

class Camera
{
private:
	Transform* m_parentTransform;
	glm::mat4 m_projMatrix, m_viewMatrix, VP;
	CameraType m_type = CameraType::PERSPECTIVE;

	float m_nearPlane = 0.1f;
	float m_farPlane = 1000.f;
	union
	{
		float m_fov = 45.f;
		float m_bottom;
	};
	union
	{
		float m_ratio = (float)WINDOW_W / (float)WINDOW_H;
		float m_left;
	};

	float m_right = 0;
	float m_top = 0;

	Camera();

	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 worldUp;
	void UpdateCameraVectors();

public:
	//camera attributes
	glm::vec3 Right;
	glm::vec3 Up;
	//euler angles
	float Yaw;
	float Pitch;
	//camera options
	float MovementSpeed;
	float MouseSensitivity;

	Camera(Transform* parent, CameraType type = CameraType::PERSPECTIVE);

	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);

	void Recalculate();

	inline glm::mat4 Get() { return VP; }

	void SetParentTransform(Transform* transform) {
		m_parentTransform = transform;
	}

	Transform* GetParentTransform() { return m_parentTransform; }

	inline glm::mat4 GetView() { return m_viewMatrix; }

	inline glm::mat4 GetProj() { return m_projMatrix; }

	inline CameraType GetType() { return m_type; }

	//sets the perspective projection
	void SetProjPersp(float fov, float ratio, float nearPlane, float farPlane);
	//sets the orthographic projection
	void SetProjOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
};


