#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Log.h"
#include "Application.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(Mesh* mesh, ShaderProgram* program, Texture* texture)
{
	m_mesh = mesh;
	m_program = program;
	m_texture = texture;
}

void MeshRenderer::OnUpdate(float deltaTime)
{
	//LOG_DEBUG("I'm Updating!");
}

void MeshRenderer::OnRender()
{
	m_program->Use();
	//set uniforms here!
	glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();
	//glm::mat4 view = glm::lookAt(
	//	glm::vec3(0.f, 0.f, 0.f),
	//	glm::vec3(0.f, 0.f, 1.f) - glm::vec3(0.f, 0.f, 0.f),
	//	glm::vec3(0.f, 1.f, 0.f)
	//);
	//
	//glm::mat4 proj = glm::perspective(45.5f, (float)WINDOW_W / (float)WINDOW_H, 0.1f, 1000.f);
	//glm::mat4 mvp = proj * view * model;

	glm::mat4 mvp = Application::GetInstance()->GetCamera()->Get() * model;

	GLuint loc = glGetUniformLocation(m_program->Get(), "MVP");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(mvp));

	glm::vec3 oColor = glm::vec3(1.f, 0.f, 0.f);
	loc = glGetUniformLocation(m_program->Get(), "objectColor");
	glUniform3f(loc, oColor.x, oColor.y, oColor.z);

	m_texture->Bind();
	m_mesh->Bind();
	GL_ATTEMPT(glDrawElements(GL_TRIANGLES, m_mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
}
