#include "ModuleCamera.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"



ModuleCamera::ModuleCamera()
{
}


ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	return true;
}

update_status ModuleCamera::PreUpdate()
{
	return UPDATE_CONTINUE;
}
// Called every draw update
update_status ModuleCamera::Update()
{
	if (flag_ground) {
		ShowGrid();
	}
	if (flag_axis) {
		ShowAxis();
	}

	
	return UPDATE_CONTINUE;
}

void ModuleCamera::ShowGrid()
{
	glLineWidth(1.0f);
	float d = 200.0f;
	glBegin(GL_LINES);
	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();

}

void ModuleCamera::ShowAxis()
{
	glLineWidth(2.0f); glBegin(GL_LINES);

	// red X 
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); 
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(1.0f, 0.0f, 0.0f); 
	glVertex3f(1.0f, 0.1f, 0.0f); 
	glVertex3f(1.1f, -0.1f, 0.0f); 
	glVertex3f(1.1f, 0.1f, 0.0f); 
	glVertex3f(1.0f, -0.1f, 0.0f);

	// green Y 
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); 
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, 1.0f, 0.0f); 
	glVertex3f(-0.05f, 1.25f, 0.0f); 
	glVertex3f(0.0f, 1.15f, 0.0f); 
	glVertex3f(0.05f, 1.25f, 0.0f); 
	glVertex3f(0.0f, 1.15f, 0.0f); 
	glVertex3f(0.0f, 1.15f, 0.0f); 
	glVertex3f(0.0f, 1.05f, 0.0f);

	// blue Z 
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); 
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, 0.0f, 1.0f); 
	glVertex3f(-0.05f, 0.1f, 1.05f); 
	glVertex3f(0.05f, 0.1f, 1.05f); 
	glVertex3f(0.05f, 0.1f, 1.05f); 
	glVertex3f(-0.05f, -0.1f, 1.05f); 
	glVertex3f(-0.05f, -0.1f, 1.05f); 
	glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd(); glLineWidth(1.0f);

}

