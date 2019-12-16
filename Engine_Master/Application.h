#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleIMGUI;
class ModuleTexture;
class ModuleProgram;
class ModuleCamera;
class ModuleModelLoader;
class ModuleTimer;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleIMGUI* imgui = nullptr;
	ModuleModelLoader* moduleloader = nullptr;
	ModuleTimer* timer = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
