#ifndef _MODEL_H_
#define _MODEL_H_
#include "Mesh.h"
#include "ModuleTexture.h"
#include <string>
#include <vector>

class Model
{
public:
	Model();
	Model(const char * name);
	~Model();
	void Draw(unsigned int program);
	update_status Update();

public:
	std::string name;
	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;
	bool active = false;

};

#endif //_MODEL_H_

