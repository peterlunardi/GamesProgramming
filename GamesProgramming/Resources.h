#pragma once
#include "pch.h"
#include "Log.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Resources
{
private:
	//TODO: use smart pointers
	std::unordered_map<std::string, ShaderProgram*> m_shaderPrograms;
	std::unordered_map<std::string, Model*> m_models;
	std::unordered_map<std::string, Texture*> m_textures;
	static Resources* m_instance;
	Resources();

public:
	static Resources* GetInstance();

	//adds shader to the map, should be done at the start of application
	void AddShader(ShaderProgram* shader, std::string name)
	{
		m_shaderPrograms[name] = shader;
	};

	//adds model to the model map
	void AddModel(const std::string& directory);
	void AddModel(const std::string& name, Model* m) 
	{
		m_models[name] =
			m;
	}

	void AddTexture(const std::string& directory);
	void AddTexture(const std::string& name, Texture* t)
	{
		m_textures[name] = t;
	};

	ShaderProgram* GetShader(const std::string& name);
	Model* GetModel(const std::string& name);
	Texture* GetTexture(const std::string& name);

	//Deletes all the things!
	void ReleaseResources();

	//TODO: Release Unused Resources
};

