#include "ModuleTriangle.h"
#include "Libraries/MathGeoLib/include/Geometry/Frustum.h"
#include "Libraries/MathGeoLib/include/Math/MathAll.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"

ModuleTriangle::ModuleTriangle()
{
}


ModuleTriangle::~ModuleTriangle()
{
}

bool ModuleTriangle::Init()
{

	float3 v1 = { -1.0f, -1.0f, 0.0f };
	float3 v2 = { 1.0f, -1.0f, 0.0f };
	float3 v3 = { 0.0f, 1.0f, 0.0f };



	//create the figure
	float3 buffer_data[] = {
		v1, v2, v3
	};

	

	float buffer_data_texture[] = { 
		-1.0f, -1.0f, 0.0f,  // ← v0 pos
		1.0f, -1.0f, 0.0f,  // ← v1 pos
		0.0f,  1.0f, 0.0f,  // ← v2 pos

		0.0f, 0.0f,         // ← v0 texcoord   
		1.0f, 0.0f,         // ← v1 texcoord
		0.5f, 1.0f          // ← v2 texcoord
	};

	
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_texture), buffer_data_texture, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}



update_status ModuleTriangle::Update() {
	/*glUseProgram(App->program->ID);    	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0); // attribute 0
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0 // buffer offset
	);
	glEnableVertexAttribArray(1); // attribute 1
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(3 * 3 * sizeof(float)) // buffer offset
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->texture->texture);
	glUniform1i(glGetUniformLocation(App->program->ID, "texture0"), 0);
	glUniformMatrix4fv(glGetUniformLocation(App->program->ID, "model"), 1, GL_TRUE, &App->camera->model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->ID, "view"), 1, GL_TRUE, &App->camera->view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->ID, "proj"), 1, GL_TRUE, &App->camera->proj[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3); // start at 0 and 3 tris    
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);   
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/
	return UPDATE_CONTINUE;
	
}
