﻿#include "Application.h"
#include "ModuleModelLoader.h"
#include "ModuleTexture.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"
#include "assimp/Logger.hpp"
#include "assimp/DefaultLogger.hpp"
#include "IMGUI/imgui.h"
#include <string>
#include <io.h>


class myStream : public Assimp::LogStream {
public:
	// LOG assimp debug output to GUI console
	void write(const char *message) {
		LOG("%s", message);
	}
};

ModuleModelLoader::ModuleModelLoader() {}

ModuleModelLoader::~ModuleModelLoader() {}

bool ModuleModelLoader::Init() {

	return true;
}

bool ModuleModelLoader::CleanUp() 
{
	return true;
}

void ModuleModelLoader::Draw(unsigned int program)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i]->Draw(program);
}



void ModuleModelLoader::LoadModel(const char* path) 
{
	// Assimp logger
	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
	Assimp::DefaultLogger::get()->info("this is my info-call");
	const unsigned int severity = Assimp::Logger::Debugging | Assimp::Logger::Info | Assimp::Logger::Err | Assimp::Logger::Warn;
	Assimp::DefaultLogger::get()->attachStream(new myStream, severity);

	// Assimp import model
	Assimp::Importer importer;
	scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LOG("Error loading the file:  %s\n", importer.GetErrorString());
		return;
	}
	//TODO: check if path of the model to be loaded is alredy one of the models alredy loaded on the scene
	Model model;
	processNode(scene->mRootNode, scene, &model);
	for (int i = 0; i < loadedModels.size(); ++i) {
		loadedModels[i].active = false;
	}
	model.active = true;
	loadedModels.push_back(model);
}



void ModuleModelLoader::processNode(aiNode *node, const aiScene *scene, Model* model) 
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) 
	{
		
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(new Mesh(processMesh(mesh, scene)));
		model->meshes.push_back(new Mesh(processMesh(mesh, scene)));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) 
	{
		processNode(node->mChildren[i], scene, model);
	}
}



Mesh ModuleModelLoader::processMesh(aiMesh *mesh, const aiScene *scene) 
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		float3 vector;

		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		// texture coordinates
		if (mesh->mTextureCoords[0]) 
		{
			float2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else 
			vertex.TexCoords = float2(0.0f, 0.0f);

		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;

		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// 2. specular maps
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// 3. normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// 4. height maps

	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(vertices, indices, textures);
}


std::vector<Texture> ModuleModelLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, char* typeName) 
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++) 
		{
			if (std::strcmp(texturesLoaded[j].path, str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			finalPath = str.C_Str();
			LOG("Trying to load texture from path: %s\n", str.C_Str());
			if (FileExists(str.C_Str()))
			{
				LOG("Texture loaded from: %s\n", str.C_Str());
				finalPath = str.C_Str();
			}
			else
			{
				size_t found = finalPath.find_last_of("/\\");
				directory = finalPath.substr(found + 1);
				if (FileExists((modelPath + directory).c_str()))
				{
					finalPath = (modelPath + directory).c_str();
					LOG("Texture loading from Models Path: %s\n", finalPath.c_str());
					
				}
				else
				{
					
					//myTexturesPath.append(finalPath);
					if (FileExists((myTexturesPath + directory).c_str()))
					{
						finalPath = (myTexturesPath + directory).c_str();
						LOG("Texture loading from default Textures Path: %s\n", finalPath.c_str());
					}
				}
			}
				
			Texture texture = App->texture->LoadTexture(finalPath.c_str());
			texture.type = typeName;
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}
	return textures;
}

void ModuleModelLoader::ChangeModel(const char* path)
{
	meshes.clear();
	directory.clear();
	LoadModel(path);
}

void ModuleModelLoader::SetImgui() 
{
	for (int i = 0; i < meshes.size(); ++i) 
	{
		ImGui::Text("Mesh %d:", i);
		ImGui::BulletText("Num. Vertex: %d", meshes[i]->vertices.size());
		ImGui::BulletText("Num. Triangles: %d", meshes[i]->vertices.size()/3);
	}

}

void ModuleModelLoader::SetImguiTextures()
{
	ImGui::Checkbox("Show Mesh", &show_mesh);
	if (show_mesh)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int i = 0; i < texturesLoaded.size(); ++i) 
	{
		ImGui::Image((void*)(intptr_t)texturesLoaded[i].id, ImVec2(200 * 0.5f, 200 * 0.5f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::SameLine;
		ImGui::Text("Width: %d", texturesLoaded[i].width);
		ImGui::SameLine;
		ImGui::Text("Height: %d", texturesLoaded[i].height);
	}
	
}

bool ModuleModelLoader::FileExists(const char* path)
{
	if (access(path, 0) == -1)
	{
		LOG("File does NOT exist in path %s:\n", path);
		return false;
	}
	return true;
}


void ModuleModelLoader::SetActiveModel(Model *model)
{
	activeModel = model;
}