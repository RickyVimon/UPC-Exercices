#include "ModuleScene.h"



ModuleScene::ModuleScene()
{
}


ModuleScene::~ModuleScene()
{
}

GameObject * ModuleScene::CreateGameObject(const char* name)
{
	GameObject* object = new GameObject(name);
	game_objects.push_back(object);
	return object;
}

void ModuleScene::LoadDefaultScene(const char* path)
{
	if (path != "") 
	{
		//App->moduleloader->LoadModel("Models/BakerHouse.fbx");
	}
	else 
	{
		//TODO: Read a json file and load the scene
	}
}