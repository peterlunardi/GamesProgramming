#pragma once
#include "Component.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class MeshRenderer : public Component
{
private:
	Mesh* m_mesh;
	ShaderProgram* m_program;

public:
	// Inherited via Component
	MeshRenderer(Mesh* mesh, ShaderProgram* program);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};

