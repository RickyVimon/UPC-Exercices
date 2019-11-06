#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleTriangle;
class ModuleIMGUI;
class ModuleProgram;
class ModuleCamera;

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
	ModuleTriangle* triangle = nullptr;
	ModuleProgram* program = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleIMGUI* imgui = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
