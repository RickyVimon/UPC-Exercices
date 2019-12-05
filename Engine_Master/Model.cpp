#include "Model.h"
#include "Application.h"
#include "ModuleProgram.h"



Model::Model()
{
}

Model::Model(const char *name)
{
	this->name = name;
}


Model::~Model()
{
}

void Model::Draw(unsigned int program)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i]->Draw(program);
}

update_status Model::Update()
{
	if (active)
	{
		Draw(App->program->ID);
	}

	return UPDATE_CONTINUE;
}
