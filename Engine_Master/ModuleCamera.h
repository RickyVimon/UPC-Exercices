#pragma once
#include "Module.h"
class ModuleCamera :
	public Module
{
public:
	ModuleCamera();
	virtual ~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	void ShowGrid();
	void ShowAxis();

public:
	bool flag_ground = false;
	bool flag_axis = false;

};

