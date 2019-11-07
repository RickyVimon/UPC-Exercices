#pragma once
#include "Module.h"
#include "GL/glew.h";
#include "IL/il.h"
#include "IL/ilut.h"
#include "IL/ilu.h"

class ModuleTexture :
	public Module
{
public:
	ModuleTexture();
	virtual ~ModuleTexture();
	bool Init();
	update_status Update();

public:
	ILuint Lena;
	ILuint Width, Height;
	GLuint Texture;
	ILubyte *Data;
};

