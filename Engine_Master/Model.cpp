#include "Model.h"



Model::Model()
{
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
	/*if (active)
	{
		SDL_GL_MakeCurrent(App->window->window, context);
		Draw(App->program->ID);
	}*/

	return UPDATE_CONTINUE;
}
