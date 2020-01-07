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
	void ComputeBoundingBox();
	update_status Update();

public:
	std::string name;
	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures; //pointer to each texture of each mesh
	std::vector<float3> boundingBox;
	bool active = false;
	bool boundingBoxVisible = true;

};

#endif //_MODEL_H_

