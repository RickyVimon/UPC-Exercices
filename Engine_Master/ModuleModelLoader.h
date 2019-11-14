#pragma once
#include "Module.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class ModuleModelLoader :
	public Module
{
public:
	ModuleModelLoader();
	~ModuleModelLoader();
	bool Init();
};

