#include "pch.h"
#include "Resources.h"
Resources::Resources()
{

}

Resources::~Resources()
{
	ReleaseResources();
}

Resources* Resources::m_instance = nullptr;

Resources* Resources::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Resources();
	}
	return m_instance;
}

void Resources::AddModel(const std::string& directory)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = std::make_shared<Model>(ASSET_PATH + directory);
		LOG_DEBUG("Model Loaded from " + directory);
	}
}

void Resources::AddTexture(const std::string& directory)
{
	if (m_textures.find(directory) == m_textures.end())
	{
		m_textures[directory] = std::make_shared<Texture>(ASSET_PATH + directory);
		LOG_DEBUG("Texture Loaded from " + directory);
	}
}

std::shared_ptr<ShaderProgram> Resources::GetShader(const std::string& name)
{
	return m_shaderPrograms[name];
}

std::shared_ptr<Model> Resources::GetModel(const std::string& name)
{
	return m_models[name];
}

std::shared_ptr<Texture> Resources::GetTexture(const std::string& name)
{
	return m_textures[name];
}

void Resources::ReleaseResources()
{
	//using an iterator pattern to iterate through all elements
	//for (auto iter = m_models.begin(); iter != m_models.end(); iter++)
	//	delete iter->second;
	//
	//for (auto iter = m_textures.begin(); iter != m_textures.end(); iter++)
	//	delete iter->second;
	//
	//for (auto iter = m_shaderPrograms.begin(); iter != m_shaderPrograms.end(); iter++)
	//	delete iter->second;

	//TODO: release other resources properly
}
