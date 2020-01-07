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

	if (boundingBoxVisible) {
		glBegin(GL_LINES);
		for (unsigned int j = 0; j < boundingBox.size(); ++j)
			glVertex3f(boundingBox[j].x, boundingBox[j].y, boundingBox[j].z);
		glEnd;
	}
}

void Model::ComputeBoundingBox()
{
	//compute bounding box

	float min_x, min_y, min_z, max_x, max_y, max_z;

	for (int i = 0; i < meshes.size(); ++i)
	{
		min_x = max_x = meshes[i]->vertices[0].Position.x;
		min_y = max_y = meshes[i]->vertices[0].Position.y;
		min_z = max_z = meshes[i]->vertices[0].Position.z;

		for (int j = 0; j < meshes[i]->vertices.size(); ++j) {

					// x-axis
					if (meshes[i]->vertices[j].Position.x < min_x)
						min_x = meshes[i]->vertices[j].Position.x;
					if (meshes[i]->vertices[j].Position.x > max_x)
						max_x = meshes[i]->vertices[j].Position.x;
					// y-axis
					if (meshes[i]->vertices[j].Position.y < min_y)
						min_y = meshes[i]->vertices[j].Position.y;
					if (meshes[i]->vertices[j].Position.y > max_y)
						max_y = meshes[i]->vertices[j].Position.y;
					// z-axis
					if (meshes[i]->vertices[j].Position.z < min_z)
						min_z = meshes[i]->vertices[j].Position.z;
					if (meshes[i]->vertices[j].Position.z > max_z)
						max_z = meshes[i]->vertices[j].Position.z;		
		}
	}

	boundingBox.push_back((float3)(max_z, max_y, max_z));
	boundingBox.push_back((float3)(max_z, max_y, min_z));
	boundingBox.push_back((float3)(max_z, min_y, max_z));
	boundingBox.push_back((float3)(max_z, min_y, min_z));
	boundingBox.push_back((float3)(min_z, max_y, max_z));
	boundingBox.push_back((float3)(min_z, max_y, min_z));
	boundingBox.push_back((float3)(min_z, min_y, max_z));
	boundingBox.push_back((float3)(min_z, min_y, min_z));

}

update_status Model::Update()
{
	if (active)
	{
		Draw(App->program->ID);
	}

	return UPDATE_CONTINUE;
}


