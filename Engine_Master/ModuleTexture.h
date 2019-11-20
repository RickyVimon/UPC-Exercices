#ifndef _MODULETEXTURE_H_
#define _MODULETEXTURE_H_

#include "Module.h"
#include "GL/glew.h";
#include "IL/il.h"
#include "IL/ilut.h"
#include "IL/ilu.h"
#include "Mesh.h"

class ModuleTexture :
	public Module
{
public:
	ModuleTexture();
	virtual ~ModuleTexture();
	bool Init();
	update_status Update();
	ILuint imageName;
	ILinfo imageInfo;
	ILuint Width, Height;
	GLuint texture;
	ILubyte *Data;
	Texture LoadTexture(const char* path);
	bool CleanUp();
};

#endif

