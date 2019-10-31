#pragma once
#include "Module.h"
#include "Libraries/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "Libraries/MathGeoLib/include/MathGeoLib.h"
class ModuleProgram :
	public Module
{
public:
	ModuleProgram();
	virtual ~ModuleProgram();
	bool Init();
	void Shader(const char * vertexPath, const char * fragmentPath);
	GLuint ID;
};

