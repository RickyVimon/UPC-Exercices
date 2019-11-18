#pragma once
#include "Module.h"
#include "Libraries/MathGeoLib/include/Geometry/Frustum.h"
#include "GL/glew.h"
#include "Libraries/MathGeoLib/include/Math/float4x4.h"
#include "Libraries/MathGeoLib/include/Math/float3.h"

enum Axis {
	X,
	Y,
	Z
};

class ModuleCamera :
	public Module
{
public:
	ModuleCamera();
	virtual ~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	void ShowGrid();
	void ShowAxis();
	float4x4 LookAt(float3 eye, float3 target, float3 up);
	void SetFOV(float fov);

	void AdjustFOV();

	void Move(Axis axis, float movement);

	void Rotate(Axis axis, float movement);

	bool Boost();

public:
	float mov_speed = 0.1f;
	float rot_speed = 0.015f;
	bool flag_ground = false;
	bool flag_axis = false;
	Frustum frustum;
	float4x4 proj, view, model;
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
};

