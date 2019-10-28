#pragma once
#include "Module.h"


class ModuleIMGUI :	public Module
{
public:
	ModuleIMGUI();
	~ModuleIMGUI();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool show_demo_window = false;

};

