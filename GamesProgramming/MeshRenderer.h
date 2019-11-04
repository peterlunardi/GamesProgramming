#pragma once
#include "Component.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

class MeshRenderer : public Component
{
private:
	Mesh* m_mesh;
	ShaderProgram* m_program;
	Texture* m_texture;

public:

	// Inherited via Component
	MeshRenderer(Mesh* mesh, ShaderProgram* program, Texture* texture);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};

