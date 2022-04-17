#include "meshLoader.h"

#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"

#include <iostream>

namespace Funny
{
	std::vector<Mesh*> MeshLoader::meshStore = std::vector<Mesh*>();

	void MeshLoader::Clean()
	{
		for (unsigned int i = 0; i < MeshLoader::meshStore.size(); i++)
		{
			delete MeshLoader::meshStore[i];
		}
	}

	SceneNode* MeshLoader::LoadMesh(Renderer* renderer, std::string path, bool setDefaultMaterial /* = true */)
	{
		std::cout << "Load mesh file at: " << path << std::endl;

	}

	SceneNode* MeshLoader::processNode(Renderer* renderer, aiNode* aNode, const aiScene* aScene, std::string directory, bool setDefaultMaterial)
	{

	}

	Mesh* MeshLoader::parseMesh(aiMesh* aMesh, const aiScene* aScene, glm::vec3& out_Min, glm::vec3& out_Max)
	{

	}

	Material*  MeshLoader::parseMaterial(Renderer* renderer, aiMaterial* aMaterial, const aiScene* aScene, std::string directory)
	{

	}


	std::string MeshLoader::processPath(aiString* path, std::string directory)
	{

	}
}