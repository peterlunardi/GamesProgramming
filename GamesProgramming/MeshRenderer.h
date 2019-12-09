#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"

class MeshRenderer : public Component
{
private:
	Model* m_model;
	ShaderProgram* m_program;
	Texture* m_texture;

public:

	// Inherited via Component
	MeshRenderer(Model* model, ShaderProgram* program, Texture* texture);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};

