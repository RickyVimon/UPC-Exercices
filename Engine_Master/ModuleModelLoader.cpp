#include "ModuleModelLoader.h"
#include <assimp/cimport.h> 
#include <assimp/postprocess.h> 
#include <assimp/scene.h> 
#include <assimp/material.h> 
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>

ModuleModelLoader::ModuleModelLoader()
{
}


ModuleModelLoader::~ModuleModelLoader()
{
}

bool ModuleModelLoader::Init()
{
	//const aiScene* scene = aiImportFile(ﬁle, postprocess_ﬂags); 
	//aiProcessPreset_TargetRealtime_MaxQuality;
	//If scene == NULL → aiGetErrorString
	return true;
}
