#ifndef _MODULEMODELLOADER_H_
#define _MODULEMODELLOADER_H_

#include "Module.h"
#include "Globals.h"
#include "Mesh.h"
#include "assimp/scene.h"
#include <vector>
#include "Model.h"

struct aiScene;

class ModuleModelLoader : public Module
{
public:
	std::vector<Texture> texturesLoaded;
	std::vector<Mesh*> meshes;
	std::string directory;
	std::vector<Model> loadedModels;
	Model activeModel;


	ModuleModelLoader();
	~ModuleModelLoader();

	bool Init();
	bool CleanUp();
	void LoadModel(const char*);
	void Draw(unsigned int program);
	const aiScene* scene = nullptr;
	void ChangeModel(const char * path);

	void SetImgui();

	void SetImguiTextures();

	bool FileExists(const char * path);

private:
	//const char* directory = nullptr;
	std::string modelPath = "Models/";
	std::string myTexturesPath = "Textures/";
	std::string finalPath = "";
	bool show_mesh = false;
	void processNode(aiNode*, const aiScene*);
	Mesh processMesh(aiMesh*, const aiScene*);
	std::vector<Texture> loadMaterialTextures(aiMaterial*, aiTextureType, char*);
};

#endif