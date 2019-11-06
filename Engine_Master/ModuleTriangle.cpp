#include "ModuleTriangle.h"
#include "Libraries/MathGeoLib/include/Geometry/Frustum.h"
#include "Libraries/MathGeoLib/include/Math/MathAll.h"
#include "Application.h"
#include "ModuleProgram.h"


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
	
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}



update_status ModuleTriangle::Update() {
	glEnableVertexAttribArray(0); // attribute 0 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // number of componentes (3 floats) 
		GL_FLOAT,           // data type 
		GL_FALSE,           // should be normalized? 
		0,                  // stride 
		(void*)0            // array buffer offset 
	);
	glUseProgram(App->program->ID);    

	glDrawArrays(GL_TRIANGLES, 0, 3); // start at 0 and 3 tris            
	glDisableVertexAttribArray(0);   
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return UPDATE_CONTINUE;
}
