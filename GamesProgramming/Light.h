#pragma once
#include "pch.h"
#include "Component.h"

class Light : public Component
{
public:
	Light(glm::vec3 position, glm::vec3 colour)
	{
		m_lightPos = position;
		m_lightColour = colour;
	}

	glm::vec3 GetPos() { return m_lightPos; }

	glm::vec3 GetColour() { return m_lightColour; }

	void SetPos(glm::vec3 position) { m_lightPos = position; }
	void SetColour(glm::vec3 colour) { m_lightColour = colour; }

	//inherited via component
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

private:
	glm::vec3 m_lightPos;
	glm::vec3 m_lightColour;
};

