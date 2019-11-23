#include "ModuleTexture.h"

ModuleTexture::ModuleTexture()
{
}


ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	ilGenImages(1, &imageName);
	ilBindImage(imageName);

	return true; 
	return true; 
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

Texture ModuleTexture::LoadTexture(const char* path) 
{
	//Texture texture;
	ilLoadImage(path);
	iluGetImageInfo(&imageInfo);
	if (imageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}
	texture.id = ilutGLBindTexImage();
	texture.width = ilGetInteger(IL_IMAGE_WIDTH);
	texture.height = ilGetInteger(IL_IMAGE_HEIGHT);
	texture.data = ilGetData();
	texture.path = path;

	return texture;
}

bool ModuleTexture::CleanUp() {
	ilDeleteImages(1, &imageName);
	return true;
}