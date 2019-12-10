#include "pch.h"
#include "Model.h"
#include "Log.h"

void Model::Load()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(m_directory, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_DEBUG(importer.GetErrorString());
		return;
	}

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mColors[0])
		{
			vertex.color.r = mesh->mColors[0][i].r;
			vertex.color.g = mesh->mColors[0][i].g;
			vertex.color.b = mesh->mColors[0][i].b;
			vertex.color.a = mesh->mColors[0][i].a;
		}
		else
		{
			vertex.color = glm::vec4(1.f);
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.texture.x = mesh->mTextureCoords[0][i].x;
			vertex.texture.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texture = glm::vec2(0.f, 0.f);
		}

		vertices.push_back(vertex);
	}

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new Mesh(vertices, indices);
}

Model::Model(std::string path)
{
	m_directory = path;
	Load();
}
