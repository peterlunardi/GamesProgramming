#pragma once
#include"Log.h"
class Transform
{
private:
	glm::vec3 m_position = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_forward = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_right = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_up = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_scale = glm::vec3(1.f, 1.f, 1.f);
	glm::quat m_rotation = glm::quat();
	glm::mat4 m_transformMatrix = glm::mat4();
	bool m_isDirty = true;
	glm::mat4 UpdateTransform();

public:
	Transform();
	Transform(glm::vec3 pos);
	Transform(glm::vec3 pos, glm::quat rot);
	Transform(glm::vec3 pos, glm::quat rot, glm::vec3 scale);

	//getters
	inline glm::vec3 GetPosition() { return m_position; }

	inline glm::vec3 GetForward() {
		if (m_isDirty) {
			UpdateTransform();
		}return m_forward;
	}

	inline glm::vec3 GetRight() {
		if (m_isDirty) {
			UpdateTransform();
		}return m_right;
	}

	inline glm::vec3 GetUp() {
		if (m_isDirty) {
			UpdateTransform();
		}return m_up;
	}

	inline glm::quat GetRotation() { return m_rotation; }

	inline glm::vec3 GetScale() { return m_scale; }

	inline glm::mat4 GetTransformationMatrix() {
		if (m_isDirty)
			return UpdateTransform();
		else return m_transformMatrix;
	}

	//setters
	inline void SetPosition(glm::vec3 newPos) {
		m_isDirty = true;
		m_position = newPos;
	}

	inline void AddPosition(glm::vec3 deltaPos) {
		m_isDirty = true;
		m_position += deltaPos;
	}

	inline void SetRotation(glm::quat newRotation) {
		m_isDirty = true;
		m_rotation = newRotation;
	}

	inline void AddRotation(glm::quat deltaRotation) {
		m_rotation = deltaRotation * m_rotation;
		m_isDirty = true;
	}

	inline void SetScale(glm::vec3 newScale) {
		m_isDirty = true;
		m_scale = newScale;
	}

	inline void addScale(glm::vec3 deltaScale) {
		m_isDirty = true;
		m_scale += deltaScale;
	}
	void RotateEulerAxis(float angle, glm::vec3 axis);
};
