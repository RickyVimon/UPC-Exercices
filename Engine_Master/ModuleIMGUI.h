#pragma once
#include "Module.h"
#include "IMGUI/imgui.h"
#include <iostream> 
#include <vector> 

using namespace std;

class ModuleIMGUI :	public Module
{
public:
	ModuleIMGUI();
	~ModuleIMGUI();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	bool show_demo_window = false;
	bool console_window = false;
	bool fps_window = false;
	bool configuration_window = false;
	bool propierties_window = false;
	vector <float> fps_log;
	bool ScrollToBottom = true;
	ImGuiTextBuffer Buf;
};

