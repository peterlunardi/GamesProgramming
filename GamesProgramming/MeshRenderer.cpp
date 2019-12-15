#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Log.h"
#include "Application.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(std::shared_ptr <Model> model, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture)
{
	m_model = model;
	m_program = program;
	m_texture = texture;
}

void MeshRenderer::OnUpdate(float deltaTime)
{
	//LOG_DEBUG("I'm Updating!");
}

void MeshRenderer::OnRender()
{
	//bind the shader program before setting uniforms and rendering
	m_program->Use();

	//set uniforms here! (common uniforms used for all meshes i.e mvp)

	//Model view projection matrix uniform
	glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();
	glm::mat4 vp = Application::GetInstance()->GetCamera()->Get();
	m_program->setMat4("model", model);
	m_program->setMat4("VP", vp);

	m_texture->Bind();

	for (Mesh* mesh : m_model->GetMeshes())
	{
		mesh->Bind();
		if (m_texture) m_texture->Bind();
		GL_ATTEMPT(glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
	}
}
