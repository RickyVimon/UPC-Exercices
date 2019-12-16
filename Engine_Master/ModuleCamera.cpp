#include "ModuleCamera.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleTimer.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "IMGUI/imgui.h"




ModuleCamera::ModuleCamera()
{
}


ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->window->window, &windowWidth, &windowHeight);
	aspect = (float)windowWidth / windowHeight;

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = initial_position;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 1000.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) *aspect);

	proj = frustum.ProjectionMatrix();
	model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), float3x3::RotateY(0.0f), float3(1.0f, 1.0f, 1.0f));
	FocusAt((float3::zero - frustum.pos).Normalized());
	//view = LookAt(frustum.pos, frustum.pos + frustum.front, frustum.up);
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

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (Boost())
			Move(Z, 2.0f);
		else
			Move(Z, 1.0f);		
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (Boost())
			Move(Z, -2.0f);
		else
			Move(Z, -1.0f);		
	}
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		if (Boost())
			Move(Y, 2.0f);
		else
			Move(Y, 1.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		if (Boost())
			Move(Y, -2.0f);
		else
			Move(Y, -1.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (Boost())
			Move(X, -2.0f);
		else
			Move(X, -1.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (Boost())
			Move(X, 2.0f);
		else
			Move(X, 1.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		Rotate(Z, 1.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		Rotate(Z, -1.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		Rotate(Y, -1.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		Rotate(Y, 1.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		BackToZero();
	}

	proj = frustum.ProjectionMatrix();
	view = frustum.ViewMatrix();

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
	glLineWidth(2.0f); 
	glBegin(GL_LINES);
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
	glEnd(); 
	glLineWidth(1.0f);
}


float4x4 ModuleCamera::LookAt(float3 eye, float3 target, float3 up) {
	float4x4 matrix;
	math::float3 f(target - eye);
	f.Normalize();
	math::float3 s(f.Cross(up));
	s.Normalize();
	math::float3 u(s.Cross(f));
	matrix[0][0] = s.x;
	matrix[0][1] = s.y;
	matrix[0][2] = s.z;
	matrix[1][0] = u.x;
	matrix[1][1] = u.y;
	matrix[1][2] = u.z;
	matrix[2][0] = -f.x;
	matrix[2][1] = -f.y;
	matrix[2][2] = -f.z;
	matrix[0][3] = -s.Dot(eye);
	matrix[1][3] = -u.Dot(eye);
	matrix[2][3] = f.Dot(eye);
	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;
	return matrix;
}

void ModuleCamera::SetFOV(float fov)
{
	frustum.verticalFov = fov;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) *aspect);

	proj = frustum.ProjectionMatrix();
}

void ModuleCamera::AdjustFOV() {
	aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	proj = frustum.ProjectionMatrix();
}

void ModuleCamera::Move(Axis axis, float movement)
{				
	switch (axis) {
	case X:
		frustum.pos += frustum.WorldRight()  * (movement * mov_speed);
		break;
	case Y:
		frustum.pos += frustum.up * (movement * mov_speed);
		break;
	case Z:
		frustum.pos -= frustum.WorldRight().Cross(float3(0,1,0)) * (movement * mov_speed);
		break;
	}	
}

void ModuleCamera::ZoomIn()
{
	frustum.pos += frustum.front * zoom_speed;
}


void ModuleCamera::ZoomOut()
{
	frustum.pos -= frustum.front * zoom_speed;
}


void ModuleCamera::Rotate(Axis axis, float movement)
{
	switch (axis) {
	case X:

		break;
	case Y:
		rotation_matrix = float3x3::RotateY(movement * rot_speed);
		frustum.up = rotation_matrix * frustum.up;
		frustum.front = rotation_matrix * frustum.front;

		break;
	case Z:
		const float current_angle = asinf(frustum.front.y / frustum.front.Length());
		if (abs(current_angle + movement * rot_speed) >= math::pi / 2) {
			return;
		}
		float3x3 rotation_matrix = float3x3::identity;
		rotation_matrix.SetRotatePart(frustum.WorldRight(), movement * rot_speed);
		frustum.up = rotation_matrix * frustum.up;
		frustum.front = rotation_matrix * frustum.front;
		break;
	}

}

void ModuleCamera::Orbit(Axis axis, float angle)
{
	float3x3 rotation_matrix;
	switch (axis)
	{
	case X:	
		rotation_matrix = float3x3::RotateY(-angle * rot_speed);
		break;

	case Y:
		const float current_angle = asinf(frustum.front.y / frustum.front.Length());
		if (abs(current_angle + angle * rot_speed) >= math::pi / 2) {
			return;
		}
		rotation_matrix = float3x3::identity;
		rotation_matrix.SetRotatePart(frustum.WorldRight(), -angle * rot_speed);
		break;
	}

	frustum.pos = rotation_matrix * frustum.pos;
	FocusAt((float3::zero - frustum.pos).Normalized());
	view = LookAt(frustum.pos, frustum.pos + frustum.front, frustum.up);

}

bool ModuleCamera::Boost() 
{
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		return true;
	else
		return false;
}

void ModuleCamera::SetAspect() {
	aspect = ((float)App->window->width / App->window->height);
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) *aspect);
	proj = frustum.ProjectionMatrix();
}

void ModuleCamera::FocusAt(float3 target) 
{
	float3x3 rotation_matrix = float3x3::LookAt(frustum.front, target, frustum.up, float3::unitY);
	frustum.front = rotation_matrix * frustum.front;
	frustum.up = rotation_matrix * frustum.up;
}

void ModuleCamera::BackToZero()
{
	FocusAt((float3::zero - frustum.pos).Normalized());
	frustum.pos = initial_position;
}

void ModuleCamera::SetImgui()
{
	if (ImGui::Checkbox("Ground", &flag_ground)) {

	}
	if (ImGui::Checkbox("Axis", &flag_axis)) {

	}
	float fov = frustum.verticalFov;
	if (ImGui::SliderFloat("Vertical FOV", &fov, 0.01f, math::pi-0.1, "%.3f", 0.9f))
	{
		SetFOV(fov);
	}
	ImGui::Text("Position: X = %.3f, Y = %.3f, Z = %.3f", frustum.pos[0], frustum.pos[1], frustum.pos[2]);
}
